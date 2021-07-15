#include <FL/Fl_Shared_Image.H>
#include <ImageView.h>

#include <precomp.hpp>

ImageShower::ImageShower(int x, int y, int w, int h) : Fl_Box(x, y, w, h) {
  fl_register_images();
}
ImageShower::~ImageShower() noexcept {}

void ImageShower::attach_ImageName(
    const CSL::RefPtr<std::string>& refImageName) noexcept {
  m_ImageName = refImageName;
}
CSL::RefPtr<std::string> ImageShower::detach_ImageName() noexcept {
  return CSL::RefPtr<std::string>(std::move(m_ImageName));
}
void ImageShower::show() {
  auto img = Fl_Shared_Image::get((m_ImageName.Get())->c_str(), w(), h());
  this->image(img);
}
