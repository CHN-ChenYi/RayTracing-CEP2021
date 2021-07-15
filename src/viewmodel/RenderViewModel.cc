#include "RenderViewModel.hpp"

#include "Property.hpp"

RenderViewModel::RenderViewModel() noexcept {}

RenderViewModel::~RenderViewModel() noexcept {}

CSL::RefPtr<std::string> RenderViewModel::GetImageName() noexcept {
  return render_model_ref_->GetImageName();
}

CSL::RefPtr<std::string> RenderViewModel::GetRenderErrorInfo() noexcept {
  return render_model_ref_->GetRenderErrorInfo();
}

std::function<bool(const std::string &)> RenderViewModel::GetRenderCommand() noexcept {
  return [this](const std::string &serialized_scene) -> bool {
    return this->render_model_ref_->Render(serialized_scene);
  };
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
    // TODO generate fltk img
    if (uID == kRenderModelImageName) {
      this->Fire(uID);
    }
  };
}
