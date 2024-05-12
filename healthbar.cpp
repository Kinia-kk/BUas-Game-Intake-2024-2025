#include "healthbar.h"

	void Healthbar::ShowHealth(int number, Tmpl8::Surface* screen, int x, int y, int h)
	{
		if (number > 400) number = 400;
		screen->Bar(x, y, x + number, y + h, 0x0000ff00);
	}
