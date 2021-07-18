

#include <cstring>
#include <memory>

#include "precomp.hpp"
#include "ProgressBar.h"


ProgressBar::ProgressBar(int x, int y, int w, int h) noexcept
    : Fl_Box(x, y, w, h),
      last_progress_(0),
      buf_(new unsigned char[(int64_t)w * h * 3]),
      img_((const unsigned char*)(buf_.get()), w, h),
      kProcessPallet_{255,134,13},
      kCancelPallet_{50,50,50} {
  unsigned char* buf = buf_.get();
  int i, j;
  for (i = 0; i < h; i++) {
    for (j = i*w; j < (i+1)*w; j++) {
      buf[3 * j] = kCancelPallet_[0];
      buf[3 * j + 1] = kCancelPallet_[1];
      buf[3 * j + 2] = kCancelPallet_[2];
    }
  }
  image(img_);
}

ProgressBar::~ProgressBar() noexcept {}

void ProgressBar::show() noexcept {
  int i, j;
  int progress = *(progress_.Get());
  if (progress > 100 || progress < 0) return;
  unsigned char* buf = buf_.get();

  if (progress >= last_progress_) {
    for (i = 0; i < h(); i++) {
      for (j = last_progress_ * w() / 100 + i * w();
           j < progress * w() / 100 + i * w(); j++) {
        buf[3 * j] = kProcessPallet_[0];
        buf[3 * j + 1] = kProcessPallet_[1];
        buf[3 * j + 2] = kProcessPallet_[2];
      }
    }
  } else {
    for (i = 0; i < h(); i++) {
      for (j = progress * w() / 100 + i * w();
           j < last_progress_ * w() / 100 + i * w(); j++) {
        buf[3 * j] = kCancelPallet_[0];
        buf[3 * j + 1] = kCancelPallet_[1];
        buf[3 * j + 2] = kCancelPallet_[2];
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
