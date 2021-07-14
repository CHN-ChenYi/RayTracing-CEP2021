#include "precomp.hpp"

#include "ImagePart.h"

ImagePart::ImagePart() : m_wndMain(500, 500, "Renderred Image Shower")
{
	//binding
	m_renderVM.AttachModel(CSL::RefPtr<RenderModel>(m_model));
	m_model.AddNotification(m_renderVM.GetNotification());

	//properties
	m_wndMain.GetImageShower().attach_ImageName(m_renderVM.GetImageName());

	//commands
	m_wndMain.attach_StartRenderingCommand(m_renderVM.GetRenderCommand());

	//notifications
	m_renderVM.AddNotification(m_wndMain.get_Notification());
}

ImagePart::~ImagePart() noexcept
{
}

MainWindow& ImagePart::GetMainWindow() noexcept
{
	return m_wndMain;
}