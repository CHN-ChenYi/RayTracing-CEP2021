#include "ImagePart.h"

#include "precomp.hpp"

ImagePart::ImagePart() : m_wndMain(1200, 600, "Renderred Image Shower") {
  // binding
  m_renderVM.AttachModel(CSL::RefPtr<RenderModel>(m_model));
  m_model.AddNotification(m_renderVM.GetNotification());

  m_textVM.attach_Model(CSL::RefPtr<TextModel>(m_textM));

  // properties
  m_wndMain.GetImageShower().attach_ImagePtr(m_renderVM.GetImagePtr());
  m_wndMain.GetProgressBar().attach_progress(m_renderVM.GetProgress());
  m_wndMain.GetTextEditor().attach_TextBuffer(m_textVM.get_TextBuf());
  m_wndMain.GetTextEditor().UpdateBuffer();
  // commands
  m_wndMain.attach_StartRenderingCommand(m_renderVM.GetRenderCommand());
  m_wndMain.attach_LoadCommand(m_textVM.get_LoadCommand());
  // notifications
  m_renderVM.AddNotification(m_wndMain.get_Notification());
  m_textVM.AddNotification(m_wndMain.get_Notification());
}

ImagePart::~ImagePart() noexcept {}

RenderViewModel& ImagePart::GetViewModel() noexcept { return m_renderVM; }

MainWindow& ImagePart::GetMainWindow() noexcept { return m_wndMain; }
