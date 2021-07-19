#include "MainWindow.h"
#include <future>

#include "FL/Fl_Shared_Image.H"
#include "precomp.hpp"



MainWindow::MainWindow(int w, int h, const char* t)
    : Fl_Double_Window(w, h, t),
      m_ImageShower(400, 0, 800, 600),
      // start(100, 0, 100, 30, "start"),
      menu(0, 0, 400, 25),
      m_ImageInfo(0, 30, 400, h - 30),
      m_ProgressBar(0, 25, 400, 5), 
      input(0, 30, 400, h-30) {
  end();

  set_icons();
  color(fl_rgb_color(100));
  // start.callback(&start_cb, this);
  menu.color(fl_rgb_color(36, 36, 36));
  menu.textcolor(fl_rgb_color(255, 134, 13));
  // menu.textfont(FL_HELVETICA_BOLD);
  menu.box(Fl_Boxtype::FL_FLAT_BOX);
  menu.add("start", 0, &start_cb, this);
  menu.add("abort", 0, &abort_cb, this);
  menu.add("save", 0, &save_cb, &m_cmdSave);
  menu.add("load", 0, &load_cb, this);
  menu.add("mode", 0, &mode_cb, this);
  callback((Fl_Callback*)&close_cb, &m_cmdClose);
  mode = 0;
  input.hide();
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

void MainWindow::attach_AbortCommand(std::function<void()>&& cf) noexcept {
  m_cmdAbort = std::move(cf);
}

std::function<void()> MainWindow::detach_AbortCommand() noexcept {
  return std::function<void()>(std::move(m_cmdAbort));
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
void MainWindow::attach_SaveCommand(
    std::function<bool(const std::wstring&)>&& cf) noexcept {
  m_cmdSave = std::move(cf);
}
std::function<bool(const std::wstring&)>
MainWindow::detach_SaveCommand() noexcept {
  return std::function<bool(const std::wstring&)>(std::move(m_cmdSave));
}
void MainWindow::attach_LoadCommand(
    std::function<bool(const std::string&)>&& cf) noexcept {
  m_cmdLoad = std::move(cf);
}
std::function<bool(const std::string&)>
MainWindow::detach_LoadCommand() noexcept {
  return std::function<bool(const std::string&)>(std::move(m_cmdLoad));
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
std::wstring to_wide_string(const std::string& input) {
  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  return converter.from_bytes(input);
}
void MainWindow::save_cb(Fl_Widget*, void* v) {
  Fl_Native_File_Chooser fc;
  fc.title("Save file");
  fc.filter("BMP Image\t*.bmp\n");
  fc.options(Fl_Native_File_Chooser::USE_FILTER_EXT);
  fc.type(Fl_Native_File_Chooser::BROWSE_SAVE_FILE);
  fc.filter("bmp\t*.bmp\n");
  fc.options(Fl_Native_File_Chooser::USE_FILTER_EXT);
  if (fc.show() == 0) {
    std::function<bool(const std::wstring&)>& cmdFunc =
        *((std::function<bool(const std::wstring&)>*)v);
    if (cmdFunc != nullptr &&
        !cmdFunc(to_wide_string(std::string(fc.filename())))) {
      fl_alert("Error in saving file!");
    }
  }
  return;
}
void MainWindow::load_cb(Fl_Widget* pW, void* v) {
  MainWindow* pThis = (MainWindow*)v;
  Fl_Native_File_Chooser fc;
  fc.title("Choose file");
  fc.type(Fl_Native_File_Chooser::BROWSE_FILE);
  if (fc.show() == 0) {
    // std::function<bool(const std::wstring&)>& cmdFunc =
    // *((std::function<bool(const std::wstring&)>*)v);
      pThis->mode = 0;
        pThis->SwitchMode();
        std::function<bool(const std::string&)>& cmdFunc =
            pThis->m_cmdLoad;
    // if (cmdFunc != nullptr &&
    // !cmdFunc(to_wide_string((std::string(fc.filename()))))) {
    if (cmdFunc != nullptr && !cmdFunc(std::string(fc.filename()))) {
        fl_alert("Error in opening file!");
    }
  }
  return;
}
void MainWindow::StartRendering() {
  // IsRendering = 1;
    if (!mode) {
        if (!m_cmdRender(m_ImageInfo.buffer()->text())) {
        m_cmdErrorHandling();
        }
    } else {
        std::string tmp = input.GetInput();
        if (!m_cmdRender(tmp)) {
            m_cmdErrorHandling();
        }
    }
}
void MainWindow::start_cb(Fl_Widget* pW, void* pD) {
  MainWindow* pThis = (MainWindow*)pD;
  pThis->StartRendering();
}
void MainWindow::abort() { m_cmdAbort(); }
void MainWindow::abort_cb(Fl_Widget* pW, void* pD) {
  MainWindow* pThis = (MainWindow*)pD;
  pThis->abort();
}
void MainWindow::SwitchMode() {
    if (mode) {
        input.show();
        m_ImageInfo.hide();
    } else {
        input.hide();
        m_ImageInfo.show();
    }
    redraw();
}
void MainWindow::mode_cb(Fl_Widget* pW, void* pD) {
    MainWindow* pThis = (MainWindow*)pD;
    pThis->mode = pThis->mode ^ 1;
    pThis->SwitchMode();
}
ProgressBar& MainWindow::GetProgressBar() noexcept { return m_ProgressBar; }

TextEditor& MainWindow::GetTextEditor() noexcept { return m_ImageInfo; }

void MainWindow::set_icons() {
  Fl_Shared_Image* tmp_img = Fl_Shared_Image::get("G:/adv_c++/ray/RayTracing-CEP2021/pics/icon.jpg");
  m_pic.reset(tmp_img);
  if (tmp_img) {
    const char*const* buf = tmp_img->data();
    int w = tmp_img->w();
    int h = tmp_img->h();
    m_icons[0] =
        std::make_unique<Fl_RGB_Image>((const unsigned char*)*buf, w, h);//add <memory>
    m_icons[1] =
        std::make_unique<Fl_RGB_Image>((const unsigned char*)*buf, w, h);
    m_picons[0] = m_icons[0].get();
    m_picons[1] = m_icons[1].get();
    icons((const Fl_RGB_Image**)m_picons, 2);
  }
}
