#pragma once

#include <string>

#include "Scene.hpp"
#include "precomp.hpp"

class RenderModel : public CSL::PropertyTrigger {
 public:
  RenderModel();
  RenderModel(const RenderModel&) = delete;
  RenderModel& operator=(const RenderModel&) = delete;
  ~RenderModel() noexcept;

  // properties
  CSL::RefPtr<Scene> GetScene() noexcept;
  CSL::RefPtr<std::string> GetImageName() noexcept;
  CSL::RefPtr<std::string> GetRenderErrorInfo() noexcept;

  // methods
  bool Render(const std::string& serialized_scene) noexcept;

 private:
  Scene scene_;
  std::string image_name_;
  std::string render_error_info_;
};
