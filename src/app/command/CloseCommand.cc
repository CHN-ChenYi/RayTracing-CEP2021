#include "precomp.hpp"
#include "../RenderingApp.h"

std::function<bool()> RenderingApp::get_CloseCommand()
{
	return [this]()->bool { return true;};
}

