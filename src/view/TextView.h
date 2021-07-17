#ifndef __TEXT_EDITOR_H__
#define __TEXT_EDITOR_H__

class TextEditor : public Fl_Text_Editor {
 public:
  TextEditor(int x, int y, int w, int h, const char* l = 0);
  TextEditor(const TextEditor&) = delete;
  TextEditor& operator=(const TextEditor&) = delete;
  ~TextEditor() noexcept;

  // properties
  void attach_TextBuffer(const CSL::RefPtr<Fl_Text_Buffer>& refBuffer) noexcept;
  CSL::RefPtr<Fl_Text_Buffer> detach_TextBuffer() noexcept;

 public:
  void UpdateBuffer();

 private:
  CSL::RefPtr<Fl_Text_Buffer> m_refBuffer;
};

#endif
