#pragma once
#include "surface.h"
#include "button.h"
class EndScreens
{
	Tmpl8::Surface background;
	Button PlayAgainButton;
	Button MenuButton;

public:
	EndScreens():background("assets/win.jpg"), PlayAgainButton(225, 400, "assets/buttons/play_again.png", 3), MenuButton(425, 400, "assets/buttons/menu_button.png", 3) {

	}
	int ShowTwoButtons(Tmpl8::Surface* screen, int mousex, int mousey, int& click);
	int ShowWinScreen(Tmpl8::Surface* screen, int mousex, int mousey, int& click, int finalscore);
	int ShowLoseScreen(Tmpl8::Surface* screen, int mousex, int mousey, int& click);
};

