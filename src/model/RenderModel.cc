#include "RenderModel.hpp"

RenderModel::RenderModel() {}

RenderModel::~RenderModel() {}

CSL::RefPtr<Scene> RenderModel::GetScene() noexcept {
  return CSL::RefPtr<Scene>(&scene_);
}

CSL::RefPtr<std::string> RenderModel::GetImageName() noexcept {
  return CSL::RefPtr<std::string>(&image_name_);
}

CSL::RefPtr<std::string> RenderModel::GetRenderErrorInfo() noexcept {
  return CSL::RefPtr<std::string>(&render_error_info_);
}

bool RenderModel::Render(const std::string &serialized_scene) noexcept {
  return false;
}
