
#include "RenderingApp.h"

#include "precomp.hpp"

RenderingApp::RenderingApp() {}

RenderingApp::~RenderingApp() noexcept {}

// methods
bool RenderingApp::Init() {
  // properties
  m_imgPart.GetMainWindow().attach_task_future(
      m_imgPart.GetViewModel().GetFuture());

  m_imgPart.GetMainWindow().attach_ErrorInfo(
      m_imgPart.GetViewModel().GetRenderErrorInfo());

  // commands
  m_imgPart.GetMainWindow().attach_SaveCommand(
      m_imgPart.GetViewModel().GetSaveCommand());
  m_imgPart.GetMainWindow().attach_CloseCommand(get_CloseCommand());
  m_imgPart.GetMainWindow().attach_ErrorHandling(get_ErrorHandlingCommand());

  m_imgPart.GetMainWindow().attach_AbortCommand(
      m_imgPart.GetViewModel().GetAbortCommand());

  // notifications
  return true;
}

int RenderingApp::Run() {
  Fl::visual(FL_DOUBLE | FL_RGB);
  // m_imgPart.GetMainWindow().StartRendering();
  m_imgPart.GetMainWindow().show();
  return Fl::run();
}
