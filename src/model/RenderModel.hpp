#pragma once

#include <string>

#include "Renderer.hpp"
#include "Scene.hpp"

class RenderModel : public CSL::PropertyTrigger {
 public:
  RenderModel();
  RenderModel(const RenderModel&) = delete;
  RenderModel& operator=(const RenderModel&) = delete;
  ~RenderModel() noexcept;

  // properties
  CSL::RefPtr<std::string> GetImageName() noexcept;
  CSL::RefPtr<std::string> GetRenderErrorInfo() noexcept;

  // methods
  bool Render(const std::string& serialized_scene) noexcept;

 private:
  std::string image_name_;
  std::string render_error_info_;
  Renderer r_;
};
