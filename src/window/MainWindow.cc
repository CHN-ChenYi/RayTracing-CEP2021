
#include <future>
#include "precomp.hpp"
#include "MainWindow.h"

MainWindow::MainWindow(int w, int h, const char* t)
    : Fl_Double_Window(w, h, t),
      m_ImageShower(400, 0,800,600),
      //start(100, 0, 100, 30, "start"),
      menu(0, 0, 100, 30),
	  m_ImageInfo(0, 30, 400, h - 30)
{
	end();

	m_ImageInfo.color(fl_rgb_color(65,65,65));
    m_ImageInfo.textcolor(fl_rgb_color(29, 221, 226));

	//start.callback(&start_cb, this);
    menu.add("start", 0, &start_cb, this);
	callback((Fl_Callback*)&close_cb, &m_cmdClose);
    //this->resizable(m_ImageInfo);
}
MainWindow::~MainWindow() noexcept {

}
ImageShower& MainWindow::GetImageShower() noexcept {
	return m_ImageShower;
}

void MainWindow::attach_task_future(const CSL::RefPtr<std::future<void>>& ref_future) noexcept {
  this->ref_future = ref_future;
}

CSL::RefPtr<std::future<void>> MainWindow::detach_task_future() noexcept {
  return ref_future;
}

void MainWindow::attach_StartRenderingCommand(std::function<bool(const std::string&)>&& cf) noexcept {
	m_cmdRender = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_StartRenderingCommand() noexcept {
	return std::function<bool(const std::string&)>(std::move(m_cmdRender));
}
void MainWindow::attach_CloseCommand(std::function<bool()>&& cf) noexcept {
	m_cmdClose = std::move(cf);
}
std::function<bool()> MainWindow::detach_CloseCommand() noexcept {
	return std::function<bool()>(std::move(m_cmdClose));
}
void MainWindow::close_cb(Fl_Window* pW, void* pD)
{
	std::function<bool()>& cf = *((std::function<bool()>*)pD);
	MainWindow* pThis = (MainWindow*)pW;
	//if (pThis->IsRendering) { pThis->IsRendering = 0;return; }
        
    if (pThis->ref_future.Get()->valid()&&
            pThis->ref_future.Get()->wait_for(std::chrono::milliseconds(1)) !=
            std::future_status::ready) 
	{
      if (cf != nullptr) {
            cf();
      }
          return;    
	}

	default_callback(pW, pD);
}

void MainWindow::StartRendering() {
	//IsRendering = 1;
	m_cmdRender(m_ImageInfo.value());

}
void MainWindow::start_cb(Fl_Widget* pW, void* pD)
{
	MainWindow* pThis = (MainWindow*)pD;
	pThis->StartRendering();

}