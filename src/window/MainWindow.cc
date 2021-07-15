
#include <future>
#include "precomp.hpp"
#include "MainWindow.h"

MainWindow::MainWindow(int w, int h, const char* t) : Fl_Double_Window(w, h, t),
													m_ImageShower(5, 5, w / 2 - 5, h - 10),
													start(w / 4 * 3 - 50, h - 70, 100, 50, "start"),
													m_ImageInfo(w / 2 + 5, 5, w / 2 - 10, h - 80)
{
	end();

	start.callback(&start_cb, this);
	callback((Fl_Callback*)&close_cb, &m_cmdClose);

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
          return;    
	}

    if (cf != nullptr && !cf()) {
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