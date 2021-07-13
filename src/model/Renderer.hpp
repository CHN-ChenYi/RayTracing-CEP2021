#pragma once

#include <functional>
#include <memory>
#include <string>
#include <thread>

#include "Scene.hpp"
#include "Vector.hpp"
#include "precomp.hpp"

class Renderer {
 public:
  Renderer(const std::string &serialized_scene,
           const CSL::RefPtr<std::string> &image_name,
           const std::function<void(void)> &fire);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  ~Renderer() noexcept;

  bool Render() noexcept;

 private:
  Scene scene_;
  CSL::RefPtr<std::string> image_name_;

  double f_atmo(const double &dis) const noexcept;
  int Intersect(const Ray &r, double &t) const noexcept;
  Vector Radiance(const Ray &r, int depth) const noexcept;

  std::thread task_;
  std::function<void(void)> fire_;
  static void Awake(void *p_this);
};
