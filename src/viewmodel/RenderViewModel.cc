#include "RenderViewModel.hpp"

RenderViewModel::RenderViewModel() noexcept {}

RenderViewModel::~RenderViewModel() noexcept {}

CSL::RefPtr<Scene> RenderViewModel::GetScene() noexcept {
  return render_model_ref_->GetScene();
}

CSL::RefPtr<std::string> RenderViewModel::GetImageName() noexcept {
  return render_model_ref_->GetImageName();
}

std::function<bool(void)> RenderViewModel::GetRenderCommand() {
  return [this]() -> bool { return this->render_model_ref_->Render(); };
}

void RenderViewModel::AttachModel(
    const CSL::RefPtr<RenderModel>& render_model) noexcept {
  render_model_ref_ = render_model;
}

CSL::RefPtr<RenderModel> RenderViewModel::DetachModel() noexcept {
  return std::move(render_model_ref_);
}

CSL::PropertyNotification RenderViewModel::GetNotification() {
  return [this](uint32_t uID) {
    if (uID == 0) {  // TODO: set uID
      this->Fire(uID);
    }
  };
}
