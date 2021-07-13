#pragma once

#include "RenderModel.hpp"
#include "Scene.hpp"
#include "precomp.hpp"

class RenderViewModel : public CSL::PropertyTrigger {
 public:
  RenderViewModel() noexcept;
  RenderViewModel(const RenderViewModel&) = delete;
  RenderViewModel& operator=(const RenderViewModel&) = delete;
  ~RenderViewModel() noexcept;

  // properties
  CSL::RefPtr<Scene> GetScene() noexcept;
  CSL::RefPtr<std::string> GetImageName() noexcept;

  // commands
  std::function<bool(void)> GetRenderCommand();

  // methods
  void AttachModel(const CSL::RefPtr<RenderModel>& render_model) noexcept;
  CSL::RefPtr<RenderModel> DetachModel() noexcept;

 public:
  CSL::PropertyNotification GetNotification();

 private:
  CSL::RefPtr<RenderModel> render_model_ref_;
};
