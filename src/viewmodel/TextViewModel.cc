#include "TextViewModel.h"

#include "precomp.hpp"

TextViewModel::TextViewModel() noexcept {}
TextViewModel::~TextViewModel() noexcept {}

// properties
CSL::RefPtr<Fl_Text_Buffer> TextViewModel::get_TextBuf() noexcept {
  return m_refModel->get_TextBuf();
}

// methods
void TextViewModel::attach_Model(
    const CSL::RefPtr<TextModel>& refModel) noexcept {
  m_refModel = refModel;
}

CSL::RefPtr<TextModel> TextViewModel::detach_Model() noexcept {
  return CSL::RefPtr<TextModel>(std::move(m_refModel));
}

std::function<bool(const std::string&)> TextViewModel::get_SaveCommand() {
  return [this](const std::string& strFile) -> bool {
    return this->m_refModel->Save(strFile);
  };
}

std::function<bool(const std::string&)> TextViewModel::get_LoadCommand() {
  return [this](const std::string& strFile) -> bool {
    return this->m_refModel->Load(strFile);
  };
}
