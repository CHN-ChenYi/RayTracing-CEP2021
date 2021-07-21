#include <FL/Fl_Shared_Image.H>
#include <ImageView.h>

#include <precomp.hpp>

ImageShower::ImageShower(int x, int y, int w, int h) : Fl_Box(x, y, w, h) {
  fl_register_images();
}
ImageShower::~ImageShower() noexcept {}

void ImageShower::attach_ImagePtr(
    const CSL::RefPtr<Image*>& refImagePtr) noexcept {
  m_Image = refImagePtr;
}
CSL::RefPtr<Image*> ImageShower::detach_ImagePtr() noexcept {
  return CSL::RefPtr<Image*>(std::move(m_Image));
}
void ImageShower::show() {
  Fl_RGB_Image* rgb_img =
      new Fl_RGB_Image((*(m_Image.Get()))->buf.get(), (*(m_Image.Get()))->w,
                       (*(m_Image.Get()))->h);
  Fl_Image* nrgb_img = rgb_img->copy(800, 600);
  delete rgb_img;
  tmpImage.reset(nrgb_img);
  this->image(nrgb_img);
  redraw();
}
