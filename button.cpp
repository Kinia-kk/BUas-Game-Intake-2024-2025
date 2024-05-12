#include "button.h"

bool Button::ShowandClick(Tmpl8::Surface* screen, int mousex, int mousey, int& isclick) {
	if (mousex >= x && mousex <= x + width && mousey >= y && mousey <= y + height) {
		ButtonSprite.SetFrame(1);
		ButtonSprite.Draw(screen, x, y);
		if (isclick == 1)
		{
			isclick = 0;
			return 1;
		}
		else return 0;
	}
	else {
		ButtonSprite.SetFrame(0);
		ButtonSprite.Draw(screen, x, y);
		return 0;
	}
}
void Button::ShowDisabled(Tmpl8::Surface* screen) {
	ButtonSprite.SetFrame(2);
	ButtonSprite.Draw(screen, x, y);
}