#pragma once
#include"surface.h"
//basic button class
class Button
{
		int x;
		int y;
		int width;
		int height;
		Tmpl8::Sprite ButtonSprite;
	public:
		Button(int xx, int yy, char* sourceimage, int framesnumber) :ButtonSprite(Tmpl8::Sprite(new Tmpl8::Surface(sourceimage), framesnumber))
		{
			x = xx;
			y = yy;
			width = ButtonSprite.GetWidth();
			height = ButtonSprite.GetHeight();
		}
		bool ShowandClick(Tmpl8::Surface* screen, int mousex, int mousey, int& isclick);
		void ShowDisabled(Tmpl8::Surface* screen);

};

