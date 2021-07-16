#include "MessageDialog.h"

#include "precomp.hpp"

MessageDialog::MessageDialog(int w, int h, const char* title, const char* msg)
    : Fl_Window(w, h, title),
      m_box(/*FL_FLAT_BOX,*/ 10, 10, 150, 25, msg),
      m_btnOK(10, 100, 60, 25, "OK") {
  end();
  set_modal();

  m_btnOK.callback(&ok_cb, this);
}

MessageDialog::~MessageDialog() noexcept {}

// properties

// commands

// methods

// callbacks

void MessageDialog::ok_cb(Fl_Widget* pW, void* pD) {
  MessageDialog* pThis = (MessageDialog*)pD;
  pThis->hide();
}
