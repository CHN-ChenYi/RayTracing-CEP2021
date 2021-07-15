
#include "precomp.hpp"

#include<MainWindow.h>

MainWindow::MainWindow(int w, int h, const char* t) : Fl_Double_Window(w, h, t),
													  m_ImageShower(5,5,w/2-5,h-10),
													  start(w/4*3-50,h-70,100,50,"start"),
													  m_ImageInfo(w/2+5, 5, w/2-10, h-80)
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
void MainWindow::attach_StartRenderingCommand(std::function<bool(const std::string&)>&& cf) noexcept {
	m_cmdRender = std::move(cf);
}
std::function<bool(const std::string&)> MainWindow::detach_StartRenderingCommand() noexcept {
	return std::function<bool(const std::string&)>(std::move(m_cmdRender));
}
void MainWindow::attach_CloseCommand(std::function<void()>&& cf) noexcept {
	m_cmdClose = std::move(cf);
}
std::function<void()> MainWindow::detach_CloseCommand() noexcept {
	return std::function<void()>(std::move(m_cmdClose));
}
void MainWindow::close_cb(Fl_Window* pW, void* pD)
{
	std::function<void()>& cf = *((std::function<void()>*)pD);
	MainWindow* pThis = (MainWindow*)pW;
	if (pThis->IsRendering) { pThis->IsRendering = 0;return; }
	if (cf != nullptr)
		cf();
	
	default_callback(pW, pD);
}
void MainWindow::Update() {
}

void MainWindow::StartRendering() {
	IsRendering = 1;
	m_cmdRender(m_ImageInfo.value());
	
}
void MainWindow::start_cb(Fl_Widget* pW, void* pD)
{
	MainWindow* pThis = (MainWindow*)pD;
	pThis->StartRendering();
	
}
