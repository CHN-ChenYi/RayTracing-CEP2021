#pragma once

#include <string>

#include "Scene.hpp"
#include "precomp.hpp"

class RenderModel : public CSL::PropertyTrigger {
 public:
  RenderModel();
  RenderModel(const RenderModel&) = delete;
  RenderModel& operator=(const RenderModel&) = delete;
  ~RenderModel() noexcept;

  // properties
  CSL::RefPtr<Scene> GetScene() noexcept;
  CSL::RefPtr<std::string> GetImageName() noexcept;

  // methods
  bool Render() noexcept;

 private:
  Scene scene_;
  std::string image_name_;
};
