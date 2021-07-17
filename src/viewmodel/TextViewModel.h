#ifndef __TEXT_VIEW_MODEL_H__
#define __TEXT_VIEW_MODEL_H__

#include "../model/TextModel.h"

class TextViewModel : public CSL::PropertyTrigger
{
public:
	TextViewModel() noexcept;
	TextViewModel(const TextViewModel&) = delete;
	TextViewModel& operator=(const TextViewModel&) = delete;
	~TextViewModel() noexcept;

//properties
        CSL::RefPtr<Fl_Text_Buffer> get_TextBuf() noexcept;

//commands
	std::function<bool(const std::string&)> get_LoadCommand();
	std::function<bool(const std::string&)> get_SaveCommand();

//methods
        void attach_Model(const CSL::RefPtr<TextModel>& refModel) noexcept;
        CSL::RefPtr<TextModel> detach_Model() noexcept;

public:
        CSL::PropertyNotification get_Notification();

private:
        CSL::RefPtr<TextModel> m_refModel;
};

#endif
