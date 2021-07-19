#include<Input.h>
Input::Input(int x, int y, int w, int h) :
samp_num(x+115,y+10,50,30,"sampling number"),
w(x+220, y + 10, 50, 30,"width"),
h(x+320, y + 10, 50, 30,"height"),
frog_i(x, y + 50, 50, 30,"frog"),
frog_c_x(x+115, y + 50, 50, 30,"x"),
frog_c_y(x+220, y + 50, 50, 30,"y"),
frog_c_z(x+320, y + 50, 50, 30,"z"),
camera_x_x(x+115, y + 90, 50, 30,"camera x x"),
camera_x_y(x+220, y + 90, 50, 30,"y"),
camera_x_z(x+320, y + 90, 50, 30,"z"),
camera_y_x(x+115, y + 130, 50, 30,"camera y x"),
camera_y_y(x+220, y + 130, 50, 30,"y"),
camera_y_z(x+320, y + 130, 50, 30,"z"),
lensr(x+115, y + 170, 50, 30,"lensr"),
camera_ori_x(x+115, y + 210, 50, 30,"camera ori x"),
camera_ori_y(x+220, y + 210, 50, 30,"y"),
camera_ori_z(x+320, y + 210, 50, 30,"z"),
camera_dir_x(x+115, y + 250, 50, 30,"camera dir x"),
camera_dir_y(x+220, y + 250, 50, 30,"y"),
camera_dir_z(x+320, y + 250, 50, 30,"z"),
sphere(x, y + 290, w, h-290)
{

}
Input::~Input(){}
void Input::show() {
    samp_num.show();
    w.show();
    h.show();
    frog_i.show();
    frog_c_x.show();
    frog_c_y.show();
    frog_c_z.show();
    camera_x_x.show();
    camera_x_y.show();
    camera_x_z.show();
    camera_y_x.show();
    camera_y_y.show();
    camera_y_z.show();
    lensr.show();
    camera_ori_x.show();
    camera_ori_y.show();
    camera_ori_z.show();
    camera_dir_x.show();
    camera_dir_y.show();
    camera_dir_z.show();
    sphere.show();
}
void Input::hide() {
    samp_num.hide();
    w.hide();
    h.hide();
    frog_i.hide();
    frog_c_x.hide();
    frog_c_y.hide();
    frog_c_z.hide();
    camera_x_x.hide();
    camera_x_y.hide();
    camera_x_z.hide();
    camera_y_x.hide();
    camera_y_y.hide();
    camera_y_z.hide();
    lensr.hide();
    camera_ori_x.hide();
    camera_ori_y.hide();
    camera_ori_z.hide();
    camera_dir_x.hide();
    camera_dir_y.hide();
    camera_dir_z.hide();
    sphere.hide();
}
std::string Input::GetInput() {
    std::string tmp;
    tmp += samp_num.value();
    tmp += " ";
    tmp += w.value();
    tmp += " ";
    tmp += h.value();
    tmp += "\n";
    if (frog_i.value()) {
        tmp += "1\n";
        tmp += frog_c_x.value();
        tmp += " ";
        tmp += frog_c_y.value();
        tmp += " ";
        tmp += frog_c_z.value();
        tmp += "\n";
    } else {
        tmp += "0\n";
    }
    tmp += camera_x_x.value();
    tmp += " ";
    tmp += camera_x_y.value();
    tmp += " ";
    tmp += camera_x_z.value();
    tmp += " ";
    tmp += camera_y_x.value();
    tmp += " ";
    tmp += camera_y_y.value();
    tmp += " ";
    tmp += camera_y_z.value();
    tmp += "\n";
    tmp += lensr.value();
    tmp += "\n";
    tmp += camera_ori_x.value();
    tmp += " ";
    tmp += camera_ori_y.value();
    tmp += " ";
    tmp += camera_ori_z.value();
    tmp += " ";
    tmp += camera_dir_x.value();
    tmp += " ";
    tmp += camera_dir_y.value();
    tmp += " ";
    tmp += camera_dir_z.value();
    tmp += "\n";
    tmp += sphere.value();
    return tmp;
}