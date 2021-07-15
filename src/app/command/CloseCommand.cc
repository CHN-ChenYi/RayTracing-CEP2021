#include "precomp.hpp"
#include "MessageDialog.h"
#include "../RenderingApp.h"

std::function<bool()> RenderingApp::get_CloseCommand()
{
	return [this]()->bool { 
		MessageDialog dlg(200, 140, "Rendering Image Shower",
                      "cannot close before rendering is finished");
		dlg.show();
        while (dlg.shown()) {
			Fl::wait();
		}
		return true;
	};
}

