#pragma once

#include <string>

#include "RenderModel.hpp"

class RenderViewModel : public CSL::PropertyTrigger {
 public:
  RenderViewModel() noexcept;
  RenderViewModel(const RenderViewModel&) = delete;
  RenderViewModel& operator=(const RenderViewModel&) = delete;
  ~RenderViewModel() noexcept;

  // properties
  CSL::RefPtr<Image*> GetImagePtr() noexcept;
  CSL::RefPtr<int> GetProgress() noexcept;
  CSL::RefPtr<std::future<void>> GetFuture() noexcept;
  CSL::RefPtr<std::string> GetRenderErrorInfo() noexcept;

  // commands
  std::function<bool(const std::string&)> GetRenderCommand() noexcept;
  std::function<void()> GetAbortCommand() noexcept;
  std::function<bool(const std::wstring&)> GetSaveCommand() noexcept;

  // methods
  void AttachModel(const CSL::RefPtr<RenderModel>& render_model) noexcept;
  CSL::RefPtr<RenderModel> DetachModel() noexcept;

  // notifications
  CSL::PropertyNotification GetNotification() noexcept;

 private:
  CSL::RefPtr<RenderModel> render_model_ref_;
};
