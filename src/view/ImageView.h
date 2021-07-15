#ifndef __IMAGE_VIEW_H__
#define __IMAGE_VIEW_H__

#include <Fl/FL_BMP_Image.h>
#include <precomp.hpp>

class ImageShower : Fl_Box{
public:
	ImageShower(int x,int y,int w,int h);

	~ImageShower() noexcept;
	
	void attach_ImageName(const CSL::RefPtr<std::string>& refImageName) noexcept;
	CSL::RefPtr<std::string> detach_ImageName() noexcept;
public:
	void show();
private:
    CSL::RefPtr<std::string> m_ImageName;
};
#endif