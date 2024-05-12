#pragma once
#include "button.h"
	


	class Menu {
	private:
		//Menu Screen button sprites
		Button PlayButton;
		Button InstructionButton;
		Button CreditsButton;
		Tmpl8::Surface background;
	public:
		Menu() :PlayButton(300, 225, "assets/buttons/play_button.png", 3), InstructionButton(300, 300, "assets/buttons/how_to_play_button.png", 3), CreditsButton(300, 375, "assets/buttons/credits_button.png", 3), background("assets/MainDungeon.jpg")
		{
		}
		
		int LoadMenu(int number, Tmpl8::Surface* screen, int mousex, int mousey, int &isclick); //Loading menu screen
	};

