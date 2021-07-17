// Zhu Lizhen
// 7.14

#ifndef __IMAGE_PART_H__
#define __IMAGE_PART_H__

#include "../model/RenderModel.hpp"
#include "../viewmodel/RenderViewModel.hpp"
#include "../model/TextModel.h"
#include "../viewmodel/TextViewModel.h"
#include "../window/MainWindow.h"

class ImagePart {
 public:
  ImagePart();
  ImagePart(const ImagePart&) = delete;
  ImagePart& operator=(const ImagePart&) = delete;
  ~ImagePart() noexcept;

 public:
  MainWindow& GetMainWindow() noexcept;
  RenderViewModel& GetViewModel() noexcept;

 private:
  // TODO: export these objects
  RenderModel m_model;
  RenderViewModel m_renderVM;
  MainWindow m_wndMain;

  TextModel m_textM;
  TextViewModel m_textVM;
};

#endif  // !__IMAGE_PART_H__
