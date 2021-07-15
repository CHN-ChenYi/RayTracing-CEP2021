// Zhu Lizhen
// 7.14

#ifndef __RENDERING_APP_H__
#define __RENDERING_APP_H__

#include "ImagePart.h"

class RenderingApp
{
public:
	RenderingApp();
	RenderingApp(const RenderingApp&) = delete;
	RenderingApp& operator=(const RenderingApp&) = delete;
	~RenderingApp() noexcept;
	//methods
	bool Init();
	int Run();

private:
	std::function<void()> get_CloseCommand();

private:
	ImagePart m_imgPart;
};

#endif // !

