
#include <memory>
#include <cstring>
#include "precomp.hpp"
#include "ProgressBar.h"

ProgressBar::ProgressBar(int x, int y, int w, int h)noexcept
    : Fl_Box(x, y, w, h),
    last_progress_(0), 
    buf_(new unsigned char[(int64_t)w*h*3]),
    img_((const unsigned char*)(buf_.get()),w,h) 
{
  memset(buf_.get(), 119, 3*(int64_t)w * h*sizeof(unsigned char));
  image(img_);
}

ProgressBar::~ProgressBar()noexcept {}

void ProgressBar::show()noexcept { 
  int i, j;
  int progress = *(progress_.Get());
  unsigned char pallet[]{24, 237, 51};
  if (progress >100 || progress < last_progress_) return;
  unsigned char* buf = buf_.get();
  for (i = 0; i < h(); i++) {
    for (j = last_progress_*w()/100+i*w(); j < progress*w()/100+i*w(); j++) {
      buf[3*j] = pallet[0];
      buf[3*j + 1] = pallet[1];
      buf[3*j + 2] = pallet[2];
    }
  }
  last_progress_ = progress;
  img_.uncache();
  redraw();
}

void ProgressBar::attach_progress(CSL::RefPtr<int>& pg) noexcept {
  progress_ = pg;
}

CSL::RefPtr<int> ProgressBar::detach_progress() noexcept { return progress_; }