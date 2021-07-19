#ifndef __IMAGE_VIEW_H__
#define __IMAGE_VIEW_H__

#include <utility>
#include <memory>

#include <Fl/FL_BMP_Image.h>

#include <Image.hpp>
#include <precomp.hpp>

class ImageShower : Fl_Box {
 public:
  ImageShower(int x, int y, int w, int h);

  ~ImageShower() noexcept;

  void attach_ImagePtr(const CSL::RefPtr<Image*>& refImagePtr) noexcept;
  CSL::RefPtr<Image*> detach_ImagePtr() noexcept;

 public:
  void show();

 private:
  CSL::RefPtr<Image*> m_Image;
  std::unique_ptr<Fl_Image> tmpImage;
};
#endif
