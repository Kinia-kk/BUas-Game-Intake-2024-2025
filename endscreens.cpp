#include "endscreens.h"
#include <string>
int EndScreens::ShowTwoButtons(Tmpl8::Surface* screen, int mousex, int mousey, int &click) {
	if(PlayAgainButton.ShowandClick(screen, mousex, mousey, click)) return 1;
	if(MenuButton.ShowandClick(screen, mousex, mousey, click)) return 2;
	return 0;
}
int EndScreens::ShowLoseScreen(Tmpl8::Surface* screen, int mousex, int mousey, int& click) {
	screen->Print("You lost!", 150, 150, 0xff0000, 10);
	return ShowTwoButtons(screen, mousex, mousey, click);
}
int EndScreens::ShowWinScreen(Tmpl8::Surface* screen, int mousex, int mousey, int& click, int finalscore) {
	background.CopyTo(screen, 0, 0);
	screen->Print("You won!", 200, 150, 0x00ff00, 10);
	screen->Print("Your score", 300, 250, 0xffffff, 5);
	screen->Print(std::to_string(finalscore).c_str(), 380, 300, 0xffffff, 7);
	return ShowTwoButtons(screen, mousex, mousey, click);
}