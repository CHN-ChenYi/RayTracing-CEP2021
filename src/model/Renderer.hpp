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
           const CSL::RefPtr<std::string> &image_name);
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  ~Renderer() noexcept;

  bool Render(std::function<void(void)> fire) noexcept;

 private:
  std::thread task_;
  Scene scene_;
  CSL::RefPtr<std::string> image_name_;

  double f_atmo(const double &dis) const noexcept;
  int Intersect(const Ray &r, double &t) const noexcept;
  Vector Radiance(const Ray &r, int depth) const noexcept;
};
