﻿#pragma once

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
  int samp_num = 20;
  int w = 1024, h = 768;

  bool frog = false;
  double rho = 0.007;
  Vector frog_c = Vector(0.7, 0.7, 0.7);

  double ipp = 0.07;  // inch per pixel in sensor
  Vector camera_x = Vector(1, 0, 0),
         camera_y = Vector(0, 1, 0);  // after nomalized
  double lensr = 0.1, u = 80, v = u / 2.5;
  Ray camera = Ray(Vector(50, 40, 150), Vector(0, 0, -1).normalize());
  std::vector<Sphere> spheres;

  Scene(const std::string &serialized_scene = "") {
    spheres.push_back(Sphere(1e5, Vector(1e5 + 1, 40.8, 81.6), Vector(),
                             Vector(.75, .25, .25), Diffuse));  // Left
    spheres.push_back(Sphere(1e5, Vector(-1e5 + 99, 40.8, 81.6), Vector(),
                             Vector(.25, .25, .75), Diffuse));  // Rght
    spheres.push_back(Sphere(1e5, Vector(50, 40.8, 1e5), Vector(),
                             Vector(.75, .75, .75), Specular));  // Back
    spheres.push_back(Sphere(1e5, Vector(50, 40.8, -1e5 + 170), Vector(),
                             Vector(), Diffuse));  // Frnt
    spheres.push_back(Sphere(1e5, Vector(50, 1e5, 81.6), Vector(),
                             Vector(.75, .75, .75), Diffuse));  // Botm
    spheres.push_back(Sphere(1e5, Vector(50, -1e5 + 81.6, 81.6),
                             Vector(.8, .8, .8), Vector(.75, .75, .75),
                             Diffuse));  // Top
    spheres.push_back(Sphere(10, Vector(73, 59, 10), Vector(),
                             Vector(0, .9, .9), Diffuse));  // Ball
    spheres.push_back(Sphere(10, Vector(40, 45, 22), Vector(),
                             Vector(.4, .8, 0), Diffuse));  // Ball
    spheres.push_back(Sphere(10, Vector(27, 30, 37), Vector(),
                             Vector(.8, .8, .1), Diffuse));  // Ball
    spheres.push_back(Sphere(10, Vector(50, 15, 50), Vector(),
                             Vector(1, 1, 1) * 0.999, Glass));  // Ball
    spheres.push_back(Sphere(10, Vector(77, 16.5, 68), Vector(),
                             Vector(.9, .45, .15), Diffuse));  // Ball
    // TODO(TO/GA): deserialize
  }
};
