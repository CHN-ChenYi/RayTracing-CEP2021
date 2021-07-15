#include "precomp.hpp"

#include "ImagePart.h"

ImagePart::ImagePart() : m_wndMain(1200, 600, "Renderred Image Shower")
{
	//binding
	m_renderVM.AttachModel(CSL::RefPtr<RenderModel>(m_model));
	m_model.AddNotification(m_renderVM.GetNotification());

	//properties
	m_wndMain.GetImageShower().attach_ImagePtr(m_renderVM.GetImagePtr());

	//commands
	m_wndMain.attach_StartRenderingCommand(m_renderVM.GetRenderCommand());

	//notifications
	m_renderVM.AddNotification(m_wndMain.get_Notification());
}

ImagePart::~ImagePart() noexcept
{
}

RenderViewModel& ImagePart::GetViewModel() noexcept { return m_renderVM; }


MainWindow& ImagePart::GetMainWindow() noexcept
{
	return m_wndMain;
}