#include "instructionscreen.h"

bool InstructionScreen::Show(Tmpl8::Surface* screen, int mousex, int mousey, int& click) {
	
	switch (page) {
	case 1:
		page1.CopyTo(screen, 0, 0);
		if (Next.ShowandClick(screen, mousex, mousey, click)) page = 2;
		break;
	case 2:
		page2.CopyTo(screen, 0, 0);
		if (Previous.ShowandClick(screen, mousex, mousey, click)) page = 1;
		break;
	}
	if (Close.ShowandClick(screen, mousex, mousey, click)) return 1;
	return 0;
}