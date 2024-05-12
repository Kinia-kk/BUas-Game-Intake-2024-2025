#pragma once
#include "surface.h"
#include "player.h"
class Item
{
protected:
	int x;
	int y;
	int x2;
	int y2;
	Tmpl8::Sprite* ItemSprite;
public:
	bool Collision(Player&player);
	bool WhileGeneratingCollision(int ix, int iy, int ix2, int iy2);
	void Draw(Tmpl8::Surface* screen);
	int GetX();
	int GetY();
	int GetX2();
	int GetY2();
	bool MouseInteraction(int mousex, int mousey);
};

