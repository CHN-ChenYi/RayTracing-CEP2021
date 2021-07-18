#include <precomp.hpp>
#include <property.hpp>

#include "MainWindow.h"

CSL::PropertyNotification MainWindow::get_Notification() {
  return [this](uint32_t uID) {
    /*		if (uID == kRenderModelScene) {
                    }
                    else */
    if (uID == kRenderModelImagePtr) {
      m_ImageShower.show();
      m_ProgressBar.show();
      //this->redraw();
    }
  };
}
