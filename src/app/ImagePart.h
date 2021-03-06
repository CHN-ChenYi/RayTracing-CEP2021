#ifndef __IMAGE_PART_H__
#define __IMAGE_PART_H__

#include "../model/RenderModel.hpp"
#include "../model/TextModel.h"
#include "../viewmodel/RenderViewModel.hpp"
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
  RenderModel m_model;
  RenderViewModel m_renderVM;

  TextModel m_textM;
  TextViewModel m_textVM;

  // must delete in the end
  MainWindow m_wndMain;
};

#endif  // !__IMAGE_PART_H__
