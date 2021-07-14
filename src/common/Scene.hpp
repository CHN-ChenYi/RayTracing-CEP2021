#pragma once

#include <string>
#include <vector>

#include "Vector.hpp"

const double inf = 1e31;

enum ReflectionType { Specular, Glass, Diffuse };

struct Sphere {
  double r;
  Vector p, e, c;
  ReflectionType t;
  static constexpr double eps = 1e-5;
  Sphere(const double &_radius, const Vector &_position,
         const Vector &_emission, const Vector &_colour,
         const ReflectionType &_refl_type) {
    r = _radius;
    p = _position;
    e = _emission;
    c = _colour;
    t = _refl_type;
  }
  double Intersect(const Ray &ray) const {  // returns distance, inf if nohit
    const Vector po = ray.ori - p;
    const double a = ray.dir / ray.dir;
    const double b = ray.dir / po * 2;
    const double c = po / po - pow(r, 2);
    double delta = pow(b, 2) - a * c * 4;
    if (delta < 0) return inf;
    delta = sqrt(delta);
    const double t_1 = (-b - delta) / (a * 2);
    const double t_2 = (-b + delta) / (a * 2);
    if (t_1 > eps) return t_1;
    if (t_2 > eps) return t_2;
    return inf;
  }
};

struct Scene {
  int samp_num;
  int w, h;

  bool frog;
  double rho;
  Vector frog_c;

  double ipp = 0.07;          // inch per pixel in sensor
  Vector camera_x, camera_y;  // after nomalized
  double lensr, u, v;
  Ray camera;
  Vector lens_centre;
  std::vector<Sphere> spheres;

  Scene(const std::string &serialized_scene) {
    // TODO(TO/GA)
  }
};
