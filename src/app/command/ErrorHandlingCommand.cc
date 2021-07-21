#include "../RenderingApp.h"
#include "MessageDialog.h"
#include "precomp.hpp"

std::function<void()> RenderingApp::get_ErrorHandlingCommand() {
  return [this]() {
    std::string& err_str = *(m_imgPart.GetMainWindow().get_ErrorInfo().Get());
    MessageDialog dlg(200, 140, "Rendering Image Shower", err_str.c_str());
    dlg.labelfont(FL_COURIER);
    dlg.show();
    while (dlg.shown()) {
      Fl::wait();
    }
  };
}
