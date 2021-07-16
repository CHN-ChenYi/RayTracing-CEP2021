
#include "RenderingApp.h"

#include "precomp.hpp"

RenderingApp::RenderingApp() {}

RenderingApp::~RenderingApp() noexcept {}

// methods
bool RenderingApp::Init() {
  // properties
  m_imgPart.GetMainWindow().attach_task_future(
      m_imgPart.GetViewModel().GetFuture());
  // commands

  m_imgPart.GetMainWindow().attach_CloseCommand(get_CloseCommand());
  // notifications
  return true;
}

int RenderingApp::Run() {
  Fl::visual(FL_DOUBLE | FL_RGB);
  // m_imgPart.GetMainWindow().StartRendering();
  m_imgPart.GetMainWindow().show();
  return Fl::run();
}
