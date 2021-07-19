
#include "app/RenderingApp.h"
#include "precomp.hpp"

////////////////////////////////////////////////////////////////////////////////
// #define DEBUG
#ifndef DEBUG
CSL_UI_MAIN_ENTRY() {
#else
int main(int argc, char* argv[]) {
#undef DEBUG
#endif
  auto upApp(std::make_unique<RenderingApp>());
  bool t = upApp->Init();
  return upApp->Run();
}
