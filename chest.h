#pragma once
#include "item.h"
#include "animator.h"
class Chest :public Item
{
	Animator* ChestAnim;
	enum state {
		Close,
		Opening,
		Open
	};
	state chest_state;
	int gold;
public:
	Chest(int chx, int chy, int type) {
		chest_state = Close;
		x = chx;
		y = chy;
		switch (type)
		{
		case 0:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/chest/chest1.png"), 10);
			gold = 50;
			break;
		case 1:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/chest/chest2.png"), 10);
			gold = 100;
			break;
		case 2:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/chest/chest3.png"), 10);
			gold = 200;
			break;
		case 3:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/chest/chest4.png"), 10);
			gold = 400;
			break;
		}
		x2 = ItemSprite->GetWidth() + x;
		y2 = ItemSprite->GetHeight() + y;
		ChestAnim = new Animator(ItemSprite);
	}
	~Chest() {
		delete ItemSprite;
		ItemSprite = nullptr;
		delete ChestAnim;
		ChestAnim = nullptr;
	}
	void Update(Tmpl8::Surface* screen, Player& player, float deltaTime, int click, int mousex, int mousey);
	int Open_anim(Tmpl8::Surface* screen, float deltaTime);
};

