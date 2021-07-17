
#ifndef __TEXT_VIEW_MODEL_H__
#define __TEXT_VIEW_MODEL_H__

#include "../model/TextModel.h"

class TextViewModel : public PropertyTrigger
{
public:
	TextViewModel() noexcept;
	TextViewModel(const TextViewModel&) = delete;
	TextViewModel& operator=(const TextViewModel&) = delete;
	~TextViewModel() noexcept;

//properties
	RefPtr<Fl_Text_Buffer> get_TextBuf() noexcept;

//commands
	std::function<bool(const std::string&)> get_LoadCommand();
	std::function<bool(const std::string&)> get_SaveCommand();

//methods
	void attach_Model(const RefPtr<TextModel>& refModel) noexcept;
	RefPtr<TextModel> detach_Model() noexcept;

public:
	PropertyNotification get_Notification();

private:
	RefPtr<TextModel>  m_refModel;
};

#endif