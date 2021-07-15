//#include <FL/Fl.H>
//#include <FL/Fl_Box.H>
//#include <FL/Fl_Window.H>
//
//int main(int argc, char **argv) {
//  Fl_Window *window = new Fl_Window(340, 180);
//  Fl_Box *box = new Fl_Box(20, 40, 300, 100, "Hello, World!");
//  box->box(FL_UP_BOX);
//  box->labelfont(FL_BOLD + FL_ITALIC);
//  box->labelsize(36);
//  box->labeltype(FL_SHADOW_LABEL);
//  window->end();
//  window->show(argc, argv);
//  return Fl::run();
//}


#include "precomp.hpp"
#include "app/RenderingApp.h"

////////////////////////////////////////////////////////////////////////////////
#define DEBUG
#ifndef DEBUG
CSL_UI_MAIN_ENTRY() {
#else
int main(int argc,char* argv[]){
#undef DEBUG
#endif
  auto upApp(std::make_unique<RenderingApp>());
  std::cout << "hello" << std::endl;
  bool t = upApp->Init();
  return upApp->Run();
}
