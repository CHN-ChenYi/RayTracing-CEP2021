#include "RenderModel.hpp"

RenderModel::RenderModel() {}

RenderModel::~RenderModel() {}

CSL::RefPtr<Scene> RenderModel::GetScene() noexcept {
	return CSL::RefPtr<Scene>(&scene_);
}

CSL::RefPtr<std::string> RenderModel::GetImageName() noexcept {
  return CSL::RefPtr<std::string>(&image_name_);
}

bool RenderModel::Render() noexcept {
  return false;
}
