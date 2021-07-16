#include "precomp.hpp"
#include "MessageDialog.h"
#include "../RenderingApp.h"

std::function<bool()> RenderingApp::get_CloseCommand()
{
	return [this]()->bool { 
		MessageDialog dlg(200, 140, "Rendering Image Shower",
                      "rendering not done yet");
		dlg.labelfont(FL_COURIER);
		dlg.show();
        while (dlg.shown()) {
			Fl::wait();
		}
		return true;
	};
}

