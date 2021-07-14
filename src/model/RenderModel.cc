#include "RenderModel.hpp"

#include <random>
#include <filesystem>

#include "Property.hpp"
#include "Renderer.hpp"
#include "uuid.h"

RenderModel::RenderModel() {
  std::random_device rd;
  auto seed_data = std::array<int, std::mt19937::state_size>{};
  std::generate(std::begin(seed_data), std::end(seed_data), std::ref(rd));
  std::seed_seq seq(std::begin(seed_data), std::end(seed_data));
  std::mt19937 generator(seq);
  uuids::uuid_random_generator gen{generator};

  image_name_ = uuids::to_string(gen()) + ".bmp";
}

RenderModel::~RenderModel() {
  std::filesystem::remove(image_name_);
}

CSL::RefPtr<std::string> RenderModel::GetImageName() noexcept {
  return CSL::RefPtr<std::string>(&image_name_);
}

CSL::RefPtr<std::string> RenderModel::GetRenderErrorInfo() noexcept {
  return CSL::RefPtr<std::string>(&render_error_info_);
}

bool RenderModel::Render(const std::string &serialized_scene) noexcept {
  Renderer r(serialized_scene, CSL::RefPtr<std::string>(&image_name_),
             [this] { this->Fire(kRenderModelImageName); });
  // TODO(TO/GA): set error info
  return r.Render();
}
