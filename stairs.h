#pragma once
#include"item.h"
class Stairs: public Item
{
public:
	Stairs(int sx, int sy){
		x = sx;
		y = sy;
		ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/stairs.png"), 1);
		x2 = ItemSprite->GetWidth() + x;
		y2 = ItemSprite->GetHeight() + y;
	}
	~Stairs() {
		delete ItemSprite;
		ItemSprite = nullptr;
	}

	bool PrintOrEnter(Tmpl8::Surface* screen, Player& player, int click, int mousex, int mousey);
};

