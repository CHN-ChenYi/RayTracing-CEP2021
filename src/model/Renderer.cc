#include "Renderer.hpp"

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <random>
#include <sstream>
#include <string>
#include <tuple>

#include "Bmp.hpp"
#include "Scene.hpp"

static double M_PI = acos(-1);

static double erand() {
  static std::default_random_engine e;
  std::uniform_real_distribution<double> u(0, 1);
  return u(e);
}

double Renderer::f_atmo(const double &dis) const noexcept {
  return exp(-pow(scene_.rho * dis, 2));
}

static inline double clamp(const double &x) {
  if (x < 0) return 0;
  if (x > 1) return 1;
  return x;
}

static inline int Gamma(const double &x) {
  return int(pow(clamp(x), 1 / 2.2) * 255 + .5);  // Gamma Correction
}

int Renderer::Intersect(const Ray &r, double &t) const noexcept {
  int id;
  t = inf;
  double tmp;
  for (auto [it, end, i] =
           std::tuple{scene_.spheres.cbegin(), scene_.spheres.cend(), 0};
       it != end; it++, i++) {
    tmp = it->Intersect(r);
    if (tmp < t) {
      id = i;
      t = tmp;
    }
  }
  if (tmp >= inf) return -1;
  return id;
}

#undef max
Vector Renderer::Radiance(const Ray &r, int depth) const noexcept {
  double t;
  int id = Intersect(r, t);
  if (id < 0) return Vector();
  const Sphere &obj = scene_.spheres[id];  // the hit object
  Vector col = obj.c;
  Vector point = r.ori + r.dir * t;                    // intersect point
  Vector n = (point - obj.p).normalize();              // normal
  Vector o_n = n / r.dir < 0 ? n : n * -1;             // orinted normal
  double p = std::max(col.x, std::max(col.y, col.z));  // max reflection
  const bool in = n / r.dir < 0;
  if (++depth > 5) {  // Russian Roulette
    if (erand() < p)
      col = col * (1 / p);
    else
      return obj.e;
  }
  if (obj.t == Specular) {
    if (scene_.frog) {
      const double p_frog = f_atmo(t);
      return obj.e +
             col % Radiance(Ray(point, r.dir - n * (2 * (n / r.dir))), depth) *
                 p_frog +
             scene_.frog_c * (1 - p_frog);
    }
    return obj.e +
           col % Radiance(Ray(point, r.dir - n * (2 * (n / r.dir))), depth);
  } else if (obj.t == Diffuse) {
    const double ang_ = 2 * M_PI * erand();  // random angle
    const double dis_ = erand(),
                 dis_i_ = sqrt(dis_);  // random distance
    const Vector u = ((fabs(o_n.x) > .1 ? Vector(0, 1) : Vector(1)) * o_n)
                         .normalize();  // u $\perp$ o_n
    const Vector v = o_n * u;           // v $\perp$ u && v $\perp$ o_n
    const Vector dir = (u * (cos(ang_) * dis_i_) + v * (sin(ang_) * dis_i_) +
                        o_n * sqrt(1 - dis_))
                           .normalize();
    if (scene_.frog) {
      const double p_frog = f_atmo(t);
      return obj.e + col % Radiance(Ray(point, dir), depth) * p_frog +
             scene_.frog_c * (1 - p_frog);
    }
    return obj.e + col % Radiance(Ray(point, dir), depth);
  } else if (obj.t == Glass) {
    const Ray refl_ray(point, r.dir - n * (2 * (n / r.dir)));
    const double n_air = 1, n_obj = 1.5,
                 n_relative = in ? n_air / n_obj : n_obj / n_air;
    const double d_d_n = r.dir / o_n;
    const double cosr_2 = 1 - pow(n_relative, 2) * (1 - pow(d_d_n, 2));
    if (cosr_2 < 0) {  // total internal reflection
      if (scene_.frog && in) {
        const double p_frog = f_atmo(t);
        return obj.e + col % Radiance(refl_ray, depth) * p_frog +
               scene_.frog_c * (1 - p_frog);
      }
      return obj.e + col % Radiance(refl_ray, depth);
    } else {
      const Vector t_dir =
          (r.dir * n_relative -
           n * ((in ? 1 : -1) * (d_d_n * n_relative + sqrt(cosr_2))))
              .normalize();
      double a = n_relative - 1, b = n_relative + 1,
             F_0 = pow(a, 2) / pow(b, 2);
      double Re = F_0 + (1 - F_0) * pow(1 - (in ? -d_d_n : t_dir / n), 5),
             Tr = 1 - Re, P = .25 + .5 * Re;  // Fresnel Reflectance
      const Vector radiance =
          (depth > 2 ? (erand() < P ? Radiance(refl_ray, depth) * (Re / P)
                                    : Radiance(Ray(point, t_dir), depth) *
                                          (Tr / (1 - P)))
                     : Radiance(refl_ray, depth) * Re +
                           Radiance(Ray(point, t_dir), depth) * Tr);
      if (scene_.frog && in) {
        const double p_frog = f_atmo(t);
        return obj.e + col % radiance * p_frog + scene_.frog_c * (1 - p_frog);
      }
      return obj.e + col % radiance;
    }
  }
  return Vector();
}

Renderer::Renderer(const std::string &serialized_scene,
                   const CSL::RefPtr<std::string> &image_name,
                   const std::function<void(void)> &fire)
    : scene_(Scene(serialized_scene)), image_name_(image_name), fire_(fire) {}

Renderer::~Renderer() noexcept {
  if (task_.joinable()) task_.join();
}

bool Renderer::Render() noexcept {
  if (task_.joinable()) task_.join();
  auto new_task = std::thread([this] {
    Vector *map = new Vector[scene_.w * scene_.h],
           *colour = new Vector[scene_.w * scene_.h];
    for (int i = 0; i < scene_.samp_num; i++) {
#pragma omp parallel for schedule(dynamic, 1)
      for (int y = 0; y < scene_.h; y++) {
        for (unsigned short x = 0; x < scene_.w; x++) {
          const int id = (scene_.h - y - 1) * scene_.w + x;
          const Vector sensor_point =
              scene_.camera.ori +
              scene_.camera_x * (scene_.w / 2 - x) * scene_.ipp +
              scene_.camera_y * (scene_.h / 2 - y) * scene_.ipp;
          const Vector focus_point =
              scene_.lens_centre +
              (scene_.lens_centre - sensor_point) * (scene_.u / scene_.v);
          const double theta = 2 * M_PI * erand(),
                       radius = scene_.lensr * erand();
          const Vector lens_point = scene_.lens_centre +
                                    scene_.camera_x * (cos(theta) * radius) +
                                    scene_.camera_y * (sin(theta) * radius);
          colour[id] += Radiance(
              Ray(lens_point, (focus_point - lens_point).normalize()), 0);
          map[id] = Vector(Gamma(clamp(colour[id].x / (i + 1))),
                           Gamma(clamp(colour[id].y / (i + 1))),
                           Gamma(clamp(colour[id].z / (i + 1))));
        }
      }
      WriteBmp(*image_name_, scene_.h, scene_.w, map);
      Fl::awake(&Awake, this);
    }
    delete[] map;
    delete[] colour;
  });
  if (!new_task.joinable()) return false;
  task_ = std::move(new_task);
  return true;
}

void Renderer::Awake(void *p_this) { static_cast<Renderer *>(p_this)->fire_(); }
