#include <FL/Fl_Input.H>
#include <FL/Fl_Multiline_Input.H>
#include <FL/Fl_Round_Button.H>

#include <precomp.hpp>
#include <string>

class Input {
 private:
  Fl_Input samp_num;
  Fl_Input w;
  Fl_Input h;
  Fl_Round_Button frog_i;
  Fl_Input frog_c_x;
  Fl_Input frog_c_y;
  Fl_Input frog_c_z;
  Fl_Input camera_x_x;
  Fl_Input camera_x_y;
  Fl_Input camera_x_z;
  Fl_Input camera_y_x;
  Fl_Input camera_y_y;
  Fl_Input camera_y_z;
  Fl_Input lensr;
  Fl_Input camera_ori_x;
  Fl_Input camera_ori_y;
  Fl_Input camera_ori_z;
  Fl_Input camera_dir_x;
  Fl_Input camera_dir_y;
  Fl_Input camera_dir_z;
  Fl_Multiline_Input sphere;

 public:
  Input(int x, int y, int w, int h);
  ~Input();
  void show();
  void hide();
  std::string GetInput();
};
