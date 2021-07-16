#include "RenderModel.hpp"

#include <memory>

#include "Property.hpp"
#include "precomp.hpp"

RenderModel::RenderModel() {}

RenderModel::~RenderModel() {}

CSL::RefPtr<Image *> RenderModel::GetImagePtr() noexcept {
  return CSL::RefPtr<Image *>(&img_ptr_);
}

CSL::RefPtr<std::future<void>> RenderModel::GetFuture() noexcept {
  return r_.GetFuture();
}

CSL::RefPtr<std::string> RenderModel::GetRenderErrorInfo() noexcept {
  return CSL::RefPtr<std::string>(&render_error_info_);
}

bool RenderModel::Render(const std::string &serialized_scene) noexcept {
  // TODO(TO/GA): set error info
  return r_.Render(serialized_scene, &img_ptr_, img_buf_,
                   [this] { this->Fire(kRenderModelImagePtr); });
}
