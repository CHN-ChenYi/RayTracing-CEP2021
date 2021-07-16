#include <precomp.hpp>
#include <property.hpp>

#include "MainWindow.h"

CSL::PropertyNotification MainWindow::get_Notification() {
  return [this](uint32_t uID) {
    /*		if (uID == kRenderModelScene) {
                    }
                    else */
    if (uID == kRenderModelImageName) {
      m_ImageShower.show();

      this->redraw();
    }
  };
}
