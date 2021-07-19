

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <algorithm>

#include "Scene.hpp"
#include "Renderer.hpp"

static void median_process(
    unsigned char *buf,
    unsigned char* outbuf,
    unsigned char* mask, 
    const int w, 
    const int h, 
    const int chan, 
    const int x,
    const int y, 
    int window) 
{
  int w_min, w_max, h_min, h_max;
  std::vector<unsigned char> list;
  int i, j;
  while (1) {
    w_min = max(0, x - window / 2);
    w_max = min(w, x + window - window / 2);
    h_min = max(0, y - window / 2);
    h_max = min(h, y + window - window / 2);
    list.clear();

    for (i = h_min; i < h_max; i++) {
      for (j = w_min; j < w_max; j++) {
        if (!mask[(w * i + j) * 3 + chan]) {
          list.push_back(buf[(i * w + j) * 3 + chan]);
        }
      }
    }
    if (list.size()) break;
    window++;
  }
  int sum = 0;
  for (auto it = list.begin(); it != list.end(); it++) {
    sum += *it;
  }
  outbuf[(w * y + x) * 3 + chan] = (unsigned char)(sum / list.size());
  //std::sort(list.begin(),list.end());
  //outbuf[(w * y + x) * 3 + chan] = list[list.size() / 2];
}

static void median_filter(Image &img, int window = 3) {
  int w = img.w;
  int h = img.h;
  int i, j, k;
  unsigned char *tmp_buf = new unsigned char[3 * (int64_t)img.w * img.h];
  unsigned char *mask_buf = new unsigned char[3 * (int64_t)img.w * img.h];
  for (k = 0; k < 3; k++) {
    //#pragma omp parallel for
    for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
        if (img.buf[(w * i + j) * 3 + k] > 250 ||
            img.buf[(w * i + j) * 3 + k] < 5) {
          mask_buf[(w * i + j) * 3 + k] = 1;
        } else {
          mask_buf[(w * i + j) * 3 + k] = 0;
        }
        tmp_buf[(w * i + j) * 3 + k] = img.buf[(w * i + j) * 3 + k];
      }
    }
  }
  for (k = 0; k < 3; k++) {
#pragma omp parallel for
    for (i = 0; i < h; i++) {
      for (j = 0; j < w; j++) {
        if (mask_buf[(w * i + j) * 3 + k]) {
          median_process(img.buf, tmp_buf, mask_buf,w, h, k, j, i, window);
        }
      }
    }
  }
  delete[] img.buf;
  delete[] mask_buf;
  img.buf = tmp_buf;
}

static const double M_PI = acos(-1);

static double erand() {
  static std::default_random_engine e;
  static std::uniform_real_distribution<double> u(0, 1);
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
  int id = -1;
  t = inf;
  for (int i = scene_.spheres.size() - 1; i >= 0; i--) {
    double tmp = scene_.spheres[i].Intersect(r);
    if (tmp < t) {
      id = i;
      t = tmp;
    }
  }
  if (t >= inf) return -1;
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
  Vector o_n = n.DotProduct(r.dir) < 0 ? n : n * -1;   // orinted normal
  double p = std::max(col.x, std::max(col.y, col.z));  // max reflection
  const bool in = n.DotProduct(r.dir) < 0;
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
             col.HadamardProduct(Radiance(
                 Ray(point, r.dir - n * (2 * n.DotProduct(r.dir))), depth)) *
                 p_frog +
             scene_.frog_c * (1 - p_frog);
    }
    return obj.e +
           col.HadamardProduct(Radiance(
               Ray(point, r.dir - n * (2 * n.DotProduct(r.dir))), depth));
  } else if (obj.t == Diffuse) {
    const double ang_ = 2 * M_PI * erand();  // random angle
    const double dis_ = erand(),
                 dis_i_ = sqrt(dis_);  // random distance
    const Vector u =
        ((fabs(o_n.x) > .1 ? Vector(0, 1) : Vector(1)).CrossProduct(o_n))
            .normalize();                  // u $\perp$ o_n
    const Vector v = o_n.CrossProduct(u);  // v $\perp$ u && v $\perp$ o_n
    const Vector dir = (u * (cos(ang_) * dis_i_) + v * (sin(ang_) * dis_i_) +
                        o_n * sqrt(1 - dis_))
                           .normalize();
    if (scene_.frog) {
      const double p_frog = f_atmo(t);
      return obj.e +
             col.HadamardProduct(Radiance(Ray(point, dir), depth) * p_frog +
                                 scene_.frog_c * (1 - p_frog));
    }
    return obj.e + col.HadamardProduct(Radiance(Ray(point, dir), depth));
  } else if (obj.t == Glass) {
    const Ray refl_ray(point, r.dir - n * (2 * n.DotProduct(r.dir)));
    const double n_air = 1, n_obj = 1.5,
                 n_relative = in ? n_air / n_obj : n_obj / n_air;
    const double d_d_n = r.dir.DotProduct(o_n);
    const double cosr_2 = 1 - pow(n_relative, 2) * (1 - pow(d_d_n, 2));
    if (cosr_2 < 0) {  // total internal reflection
      if (scene_.frog && in) {
        const double p_frog = f_atmo(t);
        return obj.e + col.HadamardProduct(Radiance(refl_ray, depth)) * p_frog +
               scene_.frog_c * (1 - p_frog);
      }
      return obj.e + col.HadamardProduct(Radiance(refl_ray, depth));
    } else {
      const Vector t_dir =
          (r.dir * n_relative -
           n * ((in ? 1 : -1) * (d_d_n * n_relative + sqrt(cosr_2))))
              .normalize();
      double a = n_relative - 1, b = n_relative + 1,
             F_0 = pow(a, 2) / pow(b, 2);
      double Re = F_0 +
                  (1 - F_0) * pow(1 - (in ? -d_d_n : t_dir.DotProduct(n)), 5),
             Tr = 1 - Re, P = .25 + .5 * Re;  // Fresnel Reflectance
      const Vector radiance =
          (depth > 2 ? (erand() < P ? Radiance(refl_ray, depth) * (Re / P)
                                    : Radiance(Ray(point, t_dir), depth) *
                                          (Tr / (1 - P)))
                     : Radiance(refl_ray, depth) * Re +
                           Radiance(Ray(point, t_dir), depth) * Tr);
      if (scene_.frog && in) {
        const double p_frog = f_atmo(t);
        return obj.e + col.HadamardProduct(radiance) * p_frog +
               scene_.frog_c * (1 - p_frog);
      }
      return obj.e + col.HadamardProduct(radiance);
    }
  }
  return Vector();
}

Renderer::Renderer() {}

Renderer::~Renderer() noexcept {
  if (task_future_.valid()) task_future_.wait();
}

CSL::RefPtr<std::future<void>> Renderer::GetFuture() noexcept {
  return CSL::RefPtr<std::future<void>>(&task_future_);
}

bool Renderer::Render(const std::string &serialized_scene, Image **img_ptr,
                      Image img_buf[2], std::function<void(void)> fire,
                      std::string &error_info, int &progress) noexcept {
  if (task_future_.valid()) task_future_.wait();
  try {
    scene_ = Scene(serialized_scene);
  } catch (const std::string &e) {
    error_info = std::move(e);
    return false;
  }
  fire_ = fire;
  img_buf[0].h = img_buf[1].h = scene_.h;
  img_buf[0].w = img_buf[1].w = scene_.w;
  img_buf[0].buf = new unsigned char[scene_.h * scene_.w * 3];
  img_buf[1].buf = new unsigned char[scene_.h * scene_.w * 3];
  cancellation_token_ = false;
  try {
    auto new_task_future = std::async(std::launch::async, [this, img_ptr,
                                                           img_buf, &progress] {
      const Vector lens_centre =
          scene_.camera.ori + scene_.camera.dir * scene_.v;
      Vector *colour =
          new Vector[scene_.w * scene_.h];  // TODO(TO/GA): use unique_ptr
      for (int i = 0; i < scene_.samp_num; i++) {
        progress = i * 100 / scene_.samp_num;
        const int cur = i & 1;
        const int pre = cur ^ 1;
#pragma omp parallel for schedule(dynamic, 1)
        for (int y = 0; y < scene_.h; y++) {
          for (int x = 0; x < scene_.w; x++) {
            const int id = (scene_.h - y - 1) * scene_.w + x;
            const Vector sensor_point =
                scene_.camera.ori +
                scene_.camera_x * (scene_.w / 2 - x) * scene_.ipp +
                scene_.camera_y * (scene_.h / 2 - y) * scene_.ipp;
            const Vector focus_point =
                lens_centre +
                (lens_centre - sensor_point) * (scene_.u / scene_.v);
            const double theta = 2 * M_PI * erand(),
                         radius = scene_.lensr * erand();
            const Vector lens_point = lens_centre +
                                      scene_.camera_x * (cos(theta) * radius) +
                                      scene_.camera_y * (sin(theta) * radius);
            colour[id] += Radiance(
                Ray(lens_point, (focus_point - lens_point).normalize()), 0);
            const int offset = id * 3;
            img_buf[cur].buf[offset] = Gamma(clamp(colour[id].x / (i + 1)));
            img_buf[cur].buf[offset + 1] = Gamma(clamp(colour[id].y / (i + 1)));
            img_buf[cur].buf[offset + 2] = Gamma(clamp(colour[id].z / (i + 1)));
          }
        }
        //
        //median_filter(img_buf[cur]);
        *img_ptr = &img_buf[cur];
        if (cancellation_token_) {
          progress = 100;
          Fl::awake(&Awake, this);
          break;
        }
        Fl::awake(&Awake, this);
      }
      progress = 100;
      delete[] colour;
    });
    task_future_ = std::move(new_task_future);
    return true;
  } catch (...) {
    error_info = "Launch async task failed";
    return false;
  }
}

void Renderer::Abort() noexcept { cancellation_token_ = true; }

void Renderer::Awake(void *p_this) {
  static_cast<Renderer *>(p_this)->fire_();
  std::cout << "finish" << std::endl;
}
