#include "RenderModel.hpp"

#include <memory>

#include "Bmp.hpp"
#include "Property.hpp"
#include "precomp.hpp"

RenderModel::RenderModel() { img_ptr_ = nullptr; }

RenderModel::~RenderModel() {}

CSL::RefPtr<Image *> RenderModel::GetImagePtr() noexcept {
  return CSL::RefPtr<Image *>(&img_ptr_);
}

CSL::RefPtr<int> RenderModel::GetProgress() noexcept {
  return CSL::RefPtr<int>(&progress_);
}

CSL::RefPtr<std::future<void>> RenderModel::GetFuture() noexcept {
  return r_.GetFuture();
}

CSL::RefPtr<std::string> RenderModel::GetRenderErrorInfo() noexcept {
  return CSL::RefPtr<std::string>(&render_error_info_);
}

bool RenderModel::Render(const std::string &serialized_scene) noexcept {
  return r_.Render(
      serialized_scene, &img_ptr_, img_buf_,
      [this] { this->Fire(kRenderModelImagePtr); }, render_error_info_,
      progress_);
}

void RenderModel::Abort() noexcept { r_.Abort(); }

bool RenderModel::Save(const std::wstring &image_path) noexcept {
  if (!img_ptr_) return false;
  WriteBmp(image_path, img_ptr_->h, img_ptr_->w, img_ptr_->buf.get());
  return true;
}
