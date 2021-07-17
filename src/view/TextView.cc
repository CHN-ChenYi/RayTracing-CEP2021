#include <TextView.h>

#include "precomp.hpp"
TextEditor::TextEditor(int x, int y, int w, int h, const char* l)
    : Fl_Text_Editor(x, y, w, h, l) {}

TextEditor::~TextEditor() noexcept {}

// properties
void TextEditor::attach_TextBuffer(
    const CSL::RefPtr<Fl_Text_Buffer>& refBuffer) noexcept {
  m_refBuffer = refBuffer;
}
CSL::RefPtr<Fl_Text_Buffer> TextEditor::detach_TextBuffer() noexcept {
  return CSL::RefPtr<Fl_Text_Buffer>(std::move(m_refBuffer));
}

void TextEditor::UpdateBuffer() { this->buffer(m_refBuffer.Get()); }
