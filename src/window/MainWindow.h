////////////////////////////////////////////////////////////////////////////////
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__
////////////////////////////////////////////////////////////////////////////////

#include <Fl/Fl_Multiline_Input.H>

#include "../view/ImageView.h"
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////

// MainWindow

class MainWindow : public Fl_Double_Window {
 public:
  MainWindow(int w, int h, const char* t);
  MainWindow(const MainWindow&) = delete;
  MainWindow& operator=(const MainWindow&) = delete;
  ~MainWindow() noexcept;

  // widgets
  ImageShower& GetImageShower() noexcept;

  // commands
  void attach_StartRenderingCommand(
      std::function<bool(const std::string&)>&& cf) noexcept;
  std::function<bool(const std::string&)>
  detach_StartRenderingCommand() noexcept;

  void attach_CloseCommand(std::function<void()>&& cf) noexcept;
  std::function<void()> detach_CloseCommand() noexcept;

  // notifications
  CSL::PropertyNotification get_Notification();

  // methods
  void Update();
  void StartRendering();

 private:
  // callback
  static void close_cb(Fl_Window* pW, void* pD);
  static void start_cb(Fl_Widget* pW, void* pD);

 private:
  // commands
  std::function<bool(const std::string&)> m_cmdRender;
  std::function<void()> m_cmdClose;

  // UI
  ImageShower m_ImageShower;
  Fl_Button start;
  Fl_Multiline_Input m_ImageInfo;
  bool IsRendering;
};

#endif
