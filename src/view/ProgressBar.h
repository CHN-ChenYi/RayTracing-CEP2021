
#ifndef __PROGRESS_BAR_H__
#define __PROGRESS_BAR_H__

class ProgressBar : public Fl_Box {
 public:
  ProgressBar(int x, int y, int w, int h) noexcept;
  ~ProgressBar() noexcept;

  // property
  void attach_progress(CSL::RefPtr<int> pg) noexcept;
  CSL::RefPtr<int> detach_progress() noexcept;
  // method
  void show() noexcept;

 private:
  const unsigned char kProcessPallet_[3];
  const unsigned char kCancelPallet_[3];
  std::unique_ptr<unsigned char> buf_;
  CSL::RefPtr<int> progress_;
  int last_progress_;
  Fl_RGB_Image img_;
};

#endif  // !__PROGRESS_BAR_H__
