#pragma once
#include "surface.h"
#include "item.h"
class Food: public Item
{
	enum
	{
		Cookie,
		Honey,
		Apple,
		Avocado
	};
	int health;
public:
	Food(int type, int fx, int fy) {
		x = fx;
		y = fy;

		switch (type) {
		case Cookie:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/food/cookie.png"), 1);
			health = 15;
			break;
		case Honey:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/food/honey.png"), 1);
			health = 30;
			break;
		case Apple:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/food/apple.png"), 1);
			health = 60;
			break;
		case Avocado:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/food/avocado.png"), 1);
			health = 120;
			break;
		}
		x2 = ItemSprite->GetWidth() + x;
		y2 = ItemSprite->GetHeight() + y;
	}
	~Food() {
		delete ItemSprite;
		ItemSprite = nullptr;
	}

	bool Update(Tmpl8::Surface*screen, Player&player);
};

