#pragma once

#include <functional>
#include <future>
#include <memory>
#include <string>
#include <thread>

#include "Image.hpp"
#include "Scene.hpp"
#include "Vector.hpp"
#include "precomp.hpp"

class Renderer {
 public:
  Renderer();
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;
  ~Renderer() noexcept;

  CSL::RefPtr<std::future<void>> GetFuture() noexcept;

  bool Render(const std::string &serialized_scene, Image **img_ptr,
              Image img_buf[2], std::function<void(void)> fire,
              std::string &error_info) noexcept;

 private:
  Scene scene_;

  double f_atmo(const double &dis) const noexcept;
  int Intersect(const Ray &r, double &t) const noexcept;
  Vector Radiance(const Ray &r, int depth) const noexcept;

  std::future<void> task_future_;
  std::function<void(void)> fire_;
  static void Awake(void *p_this);
};
