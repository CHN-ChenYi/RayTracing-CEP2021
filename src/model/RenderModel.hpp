#pragma once

#include <string>

#include "Image.hpp"
#include "Renderer.hpp"
#include "Scene.hpp"

class RenderModel : public CSL::PropertyTrigger {
 public:
  RenderModel();
  RenderModel(const RenderModel&) = delete;
  RenderModel& operator=(const RenderModel&) = delete;
  ~RenderModel() noexcept;

  // properties
  CSL::RefPtr<Image*> GetImagePtr() noexcept;
  CSL::RefPtr<std::future<void>> GetFuture() noexcept;
  CSL::RefPtr<std::string> GetRenderErrorInfo() noexcept;

  // methods
  bool Render(const std::string& serialized_scene) noexcept;
  bool Save(const std::wstring& image_path) noexcept;

 private:
  Renderer r_;
  std::string render_error_info_;
  Image img_buf_[2];
  Image* img_ptr_;
};
