
#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include <cstring>
#include <memory>

#include <Fl/Fl_Multiline_Input.H>
#include <TextView.h>
#include <Input.h>
#include "../view/ImageView.h"
#include "../view/ProgressBar.h"



// MainWindow

class MainWindow : public Fl_Double_Window {
 public:
  MainWindow(int w, int h, const char* t);
  MainWindow(const MainWindow&) = delete;
  MainWindow& operator=(const MainWindow&) = delete;
  ~MainWindow() noexcept;

  // widgets
  ImageShower& GetImageShower() noexcept;
  ProgressBar& GetProgressBar() noexcept;
  TextEditor& GetTextEditor() noexcept;
  // propertys
  void attach_task_future(const CSL::RefPtr<std::future<void>>&) noexcept;
  CSL::RefPtr<std::future<void>> detach_task_future() noexcept;

  CSL::RefPtr<std::string> get_ErrorInfo() noexcept;

  // commands
  void attach_StartRenderingCommand(
      std::function<bool(const std::string&)>&& cf) noexcept;
  std::function<bool(const std::string&)>
  detach_StartRenderingCommand() noexcept;

  void attach_AbortCommand(std::function<void()>&& cf) noexcept;
  std::function<void()> detach_AbortCommand() noexcept;
  void attach_CloseCommand(std::function<bool()>&& cf) noexcept;
  std::function<bool()> detach_CloseCommand() noexcept;

  void attach_ErrorHandling(std::function<void()>&& cf) noexcept;
  std::function<void()> detach_ErrorHandling() noexcept;

  void attach_ErrorInfo(CSL::RefPtr<std::string> s) noexcept;
  CSL::RefPtr<std::string> detach_ErrorInfo() noexcept;

  void attach_SaveCommand(
      std::function<bool(const std::wstring&)>&& cf) noexcept;
  std::function<bool(const std::wstring&)> detach_SaveCommand() noexcept;

  void attach_LoadCommand(
      std::function<bool(const std::string&)>&& cf) noexcept;
  std::function<bool(const std::string&)> detach_LoadCommand() noexcept;
  // notifications
  CSL::PropertyNotification get_Notification();

  // methods
  void StartRendering();
  void abort();

 private:
  // callback
  void SwitchMode();

  static void close_cb(Fl_Window* pW, void* pD);
  static void start_cb(Fl_Widget* pW, void* pD);
  static void load_cb(Fl_Widget* pW, void* v);
  static void save_cb(Fl_Widget*, void* v);
  static void abort_cb(Fl_Widget*, void* v);
  static void mode_cb(Fl_Widget* pW, void* pD);

 private:
  bool mode;
  // commands
  std::function<bool(const std::string&)> m_cmdRender;
  std::function<bool()> m_cmdClose;
  std::function<void()> m_cmdErrorHandling;
  std::function<void()> m_cmdAbort;
  std::function<bool(const std::wstring&)> m_cmdSave;
  std::function<bool(const std::string&)> m_cmdLoad;
  // UI
  ImageShower m_ImageShower;
  std::unique_ptr<Fl_Image> m_pic;
  std::unique_ptr<Fl_RGB_Image> m_icons[2];
  Fl_RGB_Image* m_picons[2];
  void set_icons();
  // Fl_Button start;
  Fl_Menu_Bar menu;
  TextEditor m_ImageInfo;
  ProgressBar m_ProgressBar;
  Input input;

  // properties
  CSL::RefPtr<std::future<void>> ref_future;
  CSL::RefPtr<std::string> m_ErrorInfo;
  // bool IsRendering;
};

#endif
