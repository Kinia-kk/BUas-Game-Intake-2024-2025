#include "surface.h"
#include "menu.h"



	//Loading menu screen
	int Menu::LoadMenu(int number, Tmpl8::Surface* screen, int mousex, int mousey, int& isclick) {
		background.CopyTo(screen,0,0); 
		screen->Print("Fallen King's Guard", 50, 100, 0xffffff, 6);
		if (PlayButton.ShowandClick(screen,mousex, mousey, isclick) == 1) {
			return 1;
		}

		if (InstructionButton.ShowandClick(screen, mousex, mousey, isclick) == 1) {
			return 2;
		}
		
		//if (CreditsButton.ShowandClick(screen, mousex, mousey, isclick) == 1) {
			
		//}
		return 0;
	}

	
