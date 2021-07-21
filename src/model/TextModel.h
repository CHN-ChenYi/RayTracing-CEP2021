
#ifndef __TEXT_MODEL_H__
#define __TEXT_MODEL_H__

#include <string>

class TextModel : public CSL::PropertyTrigger {
 public:
  TextModel();
  TextModel(const TextModel&) = delete;
  TextModel& operator=(const TextModel&) = delete;
  ~TextModel() noexcept;

  // properties
  CSL::RefPtr<Fl_Text_Buffer> get_TextBuf() noexcept;

  // methods
  bool Load(const std::string& str);
  bool Save(const std::string& str);

 private:
  Fl_Text_Buffer m_textBuffer;
};

#endif
