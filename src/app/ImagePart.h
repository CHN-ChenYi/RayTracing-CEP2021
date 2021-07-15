// Zhu Lizhen
// 7.14

#ifndef __IMAGE_PART_H__
#define __IMAGE_PART_H__

#include "../model/RenderModel.hpp"
#include "../viewmodel/RenderViewModel.hpp"
#include "../window/MainWindow.h"

class ImagePart {
 public:
  ImagePart();
  ImagePart(const ImagePart&) = delete;
  ImagePart& operator=(const ImagePart&) = delete;
  ~ImagePart() noexcept;

 public:
  MainWindow& GetMainWindow() noexcept;

 private:
  RenderModel m_model;
  RenderViewModel m_renderVM;
  MainWindow m_wndMain;
};

#endif  // !__IMAGE_PART_H__
