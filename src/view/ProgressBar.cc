
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
  unsigned char pallet[]{119,119,119};
  unsigned char* buf = buf_.get();
  int i,j;
  for (i = 0; i < h; i++) {
    for (j = 0;j<w; j++) {
      buf[3*j] = pallet[0];
      buf[3*j + 1] = pallet[1];
      buf[3*j + 2] = pallet[2];
    }
  }
  image(img_);
}

ProgressBar::~ProgressBar()noexcept {}

void ProgressBar::show()noexcept { 
  int i, j;
  int progress = *(progress_.Get());
  unsigned char pallet[]{24, 237, 51};
  unsigned char cancel_pallet[]{119,119,119};
  if (progress >100 || progress < 0) return;
  unsigned char* buf = buf_.get();

  if(progress>=last_progress_){
    for (i = 0; i < h(); i++) {
      for (j = last_progress_*w()/100+i*w(); j < progress*w()/100+i*w(); j++) {
        buf[3*j] = pallet[0];
        buf[3*j + 1] = pallet[1];
        buf[3*j + 2] = pallet[2];
      }
    }
  }
  else{
    for (i = 0; i < h(); i++) {
      for (j = progress*w()/100+i*w(); j < last_progress_*w()/100+i*w(); j++) {
        buf[3*j] = cancel_pallet[0];
        buf[3*j + 1] = cancel_pallet[1];
        buf[3*j + 2] = cancel_pallet[2];
      }
    }    
  }

  last_progress_ = progress;
  img_.uncache();
  redraw();
}

void ProgressBar::attach_progress(CSL::RefPtr<int> pg) noexcept {
  progress_ = pg;
}

CSL::RefPtr<int> ProgressBar::detach_progress() noexcept { return progress_; }