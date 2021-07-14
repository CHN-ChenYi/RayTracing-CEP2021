
#include "precomp.hpp"
#include "RenderingApp.h"

RenderingApp::RenderingApp()
{
}

RenderingApp::~RenderingApp() noexcept
{
}

//methods
bool RenderingApp::Init()
{
	//properties

	//commands

	m_imgPart.GetMainWindow().attach_CloseCommand(get_CloseCommand());
	//notifications
	return true;
}

int RenderingApp::Run()
{
	Fl::visual(FL_DOUBLE | FL_RGB);
	m_imgPart.GetMainWindow().StartRendering("hello");
	m_imgPart.GetMainWindow().show();
	return Fl::run();
}