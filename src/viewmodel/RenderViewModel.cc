
#include "RenderViewModel.hpp"

#include "Property.hpp"
#include "precomp.hpp"

RenderViewModel::RenderViewModel() noexcept {}

RenderViewModel::~RenderViewModel() noexcept {}

CSL::RefPtr<Image *> RenderViewModel::GetImagePtr() noexcept {
  return render_model_ref_->GetImagePtr();
}

CSL::RefPtr<int> RenderViewModel::GetProgress() noexcept {
  return render_model_ref_->GetProgress();
}

CSL::RefPtr<std::string> RenderViewModel::GetRenderErrorInfo() noexcept {
  return render_model_ref_->GetRenderErrorInfo();
}

std::function<bool(const std::string &)>
RenderViewModel::GetRenderCommand() noexcept {
  return [this](const std::string &serialized_scene) -> bool {
    return this->render_model_ref_->Render(serialized_scene);
  };
}

std::function<bool(const std::wstring &)>
RenderViewModel::GetSaveCommand() noexcept {
  return [this](const std::wstring &image_path) -> bool {
    return this->render_model_ref_->Save(image_path);
  };
}

CSL::RefPtr<std::future<void>> RenderViewModel::GetFuture() noexcept {
  return render_model_ref_->GetFuture();
}

void RenderViewModel::AttachModel(
    const CSL::RefPtr<RenderModel> &render_model) noexcept {
  render_model_ref_ = render_model;
}

CSL::RefPtr<RenderModel> RenderViewModel::DetachModel() noexcept {
  return std::move(render_model_ref_);
}

CSL::PropertyNotification RenderViewModel::GetNotification() noexcept {
  return [this](uint32_t uID) {
    if (uID == kRenderModelImagePtr) {
      this->Fire(uID);
    }
  };
}
