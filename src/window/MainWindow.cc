﻿
#include "MainWindow.h"

#include <future>

#include "precomp.hpp"

MainWindow::MainWindow(int w, int h, const char* t)
    : Fl_Double_Window(w, h, t),
      m_ImageShower(400, 0, 800, 600),
      // start(100, 0, 100, 30, "start"),
      menu(0, 0, 50, 30),
      m_ImageInfo(0, 30, 400, h - 30) {
  end();

  m_ImageInfo.color(fl_rgb_color(65, 65, 65));
  m_ImageInfo.textcolor(fl_rgb_color(29, 221, 226));
  m_ImageInfo.textfont(FL_COURIER);

  // start.callback(&start_cb, this);
  menu.add("start", 0, &start_cb, this);
  menu.add("save", 0, &save_cb, &m_cmdSave);
  callback((Fl_Callback*)&close_cb, &m_cmdClose);
  // this->resizable(m_ImageInfo);
}
MainWindow::~MainWindow() noexcept {}
ImageShower& MainWindow::GetImageShower() noexcept { return m_ImageShower; }

void MainWindow::attach_task_future(
    const CSL::RefPtr<std::future<void>>& ref_future) noexcept {
  this->ref_future = ref_future;
}

CSL::RefPtr<std::future<void>> MainWindow::detach_task_future() noexcept {
  return ref_future;
}

void MainWindow::attach_StartRenderingCommand(
    std::function<bool(const std::string&)>&& cf) noexcept {
  m_cmdRender = std::move(cf);
}
std::function<bool(const std::string&)>
MainWindow::detach_StartRenderingCommand() noexcept {
  return std::function<bool(const std::string&)>(std::move(m_cmdRender));
}
void MainWindow::attach_CloseCommand(std::function<bool()>&& cf) noexcept {
  m_cmdClose = std::move(cf);
}
void MainWindow::attach_ErrorHandling(std::function<void()>&& cf) noexcept {
  m_cmdErrorHandling = std::move(cf);
}
std::function<void()> MainWindow::detach_ErrorHandling() noexcept {
  return std::function<void()>(std::move(m_cmdErrorHandling));
}
void MainWindow::attach_SaveCommand(std::function<bool(const std::string&)>&& cf) noexcept
{
    m_cmdSave = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_SaveCommand() noexcept
{
    return std::function<bool(const std::string&)>(std::move(m_cmdSave));
}

void MainWindow::attach_ErrorInfo(CSL::RefPtr<std::string> s) noexcept {
  m_ErrorInfo = s;
}

CSL::RefPtr<std::string> MainWindow::detach_ErrorInfo() noexcept {
  return m_ErrorInfo;
}

CSL::RefPtr<std::string> MainWindow::get_ErrorInfo() noexcept {
  return m_ErrorInfo;
}

std::function<bool()> MainWindow::detach_CloseCommand() noexcept {
  return std::function<bool()>(std::move(m_cmdClose));
}
void MainWindow::close_cb(Fl_Window* pW, void* pD) {
  std::function<bool()>& cf = *((std::function<bool()>*)pD);
  MainWindow* pThis = (MainWindow*)pW;
  // if (pThis->IsRendering) { pThis->IsRendering = 0;return; }

  if (pThis->ref_future.Get()->valid() &&
      pThis->ref_future.Get()->wait_for(std::chrono::milliseconds(1)) !=
          std::future_status::ready) {
    if (cf != nullptr) {
      cf();
    }
    return;
  }

  default_callback(pW, pD);
}

void MainWindow::save_cb(Fl_Widget*, void* v) {
  Fl_Native_File_Chooser fc;
  fc.title("Save file");
  fc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
  if (fc.show() == 0) {
    std::function<bool(const std::string&)>& cmdFunc =
        *((std::function<bool(const std::string&)>*)v);
    if (cmdFunc != nullptr && !cmdFunc(std::string(fc.filename()))) {
      fl_alert("Error in saving file!");
    }
  }
  return;
}

void MainWindow::StartRendering() {
  // IsRendering = 1;
  if (!m_cmdRender(m_ImageInfo.value())) {
    m_cmdErrorHandling();
  }
}
void MainWindow::start_cb(Fl_Widget* pW, void* pD) {
  MainWindow* pThis = (MainWindow*)pD;
  pThis->StartRendering();
}