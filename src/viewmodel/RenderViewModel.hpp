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
  CSL::RefPtr<std::string> GetImageName() noexcept;
  CSL::RefPtr<std::string> GetRenderErrorInfo() noexcept;

  // commands
  std::function<bool(const std::string&)> GetRenderCommand() noexcept;

  // methods
  void AttachModel(const CSL::RefPtr<RenderModel>& render_model) noexcept;
  CSL::RefPtr<RenderModel> DetachModel() noexcept;

  // notifications
  CSL::PropertyNotification GetNotification() noexcept;

 private:
  CSL::RefPtr<RenderModel> render_model_ref_;
};
