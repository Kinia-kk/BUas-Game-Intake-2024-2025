#pragma once
#include "surface.h"
#include "button.h"
class InstructionScreen
{
	Tmpl8::Surface page1;
	Tmpl8::Surface page2;
	Button Close;
	Button Next;
	Button Previous;
	int page = 1;

public:
	InstructionScreen():
		page1("assets/instruction/instruction1.png"),
		page2("assets/instruction/instruction2.png"),
		Close(710,430, "assets/buttons/exit.png",3),
		Next(670, 430, "assets/buttons/nextpage.png", 3),
		Previous(670, 430, "assets/buttons/beforepage.png", 3)
	{
	}
	bool Show(Tmpl8::Surface* screen, int mousex, int mousey, int& click);
};

