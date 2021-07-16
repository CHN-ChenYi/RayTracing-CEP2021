#ifndef __MESSAGE_DIALOG_H__
#define __MESSAGE_DIALOG_H__

class MessageDialog : public Fl_Window {
 public:
  MessageDialog(int w, int h, const char* title,const char* msg);
  ~MessageDialog() noexcept;

 public:
  // properties

  // commands

  // methods

 private:
  static void ok_cb(Fl_Widget* pW, void* pD);

 private:
  Fl_Box m_box;

  Fl_Button m_btnOK;

  // properties

  // commands
};

////////////////////////////////////////////////////////////////////////////////

#endif
