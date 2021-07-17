#include "precomp.hpp"

#include "TextModel.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// TextModel

TextModel::TextModel()
{
}
TextModel::~TextModel() noexcept
{
}

//properties
RefPtr<Fl_Text_Buffer> TextModel::get_TextBuf() noexcept
{
	return RefPtr<Fl_Text_Buffer>(m_textBuffer);
}

//methods
bool TextModel::Load(const std::string& str)
{
	if (m_textBuffer.loadfile(str.c_str()) == 0) {		
		return true;
	}
	return false;
}

bool TextModel::Save(const std::string& str)
{
	if (m_textBuffer.savefile(str.c_str()) == 0) {
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////
}