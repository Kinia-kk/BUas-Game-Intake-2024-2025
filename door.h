#pragma once
#include "surface.h"
#include "template.h"
#include "animator.h"
#include "player.h"
#include "item.h"
class Door : public Item
{
	struct Coordinates {
		int x;
		int y;
	};
	Coordinates entering_player_position;

	enum DoorState {
		Close,
		Opening
	};
	DoorState state;

	enum DoorType {
		TopD,
		RightD,
		DownD,
		LeftD
	};
	DoorType type;

	Animator* DoorAnimation;

public:
	Door(int dtype, int dx, int dy) {
		state = Close;
		type = DoorType(dtype);
		x = dx;
		y = dy;
		switch (type)
		{
		case Door::TopD:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/doors/TDoor.png"), 5);
			entering_player_position.y = y; 
			entering_player_position.x = x;
			break;
		case Door::RightD:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/doors/RDoor.png"), 4);
			entering_player_position.y = y - 16; 
			entering_player_position.x = x - ItemSprite->GetWidth() / 2;
			break;
		case Door::DownD:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/doors/BDoor.png"), 5);
			entering_player_position.y = y - ItemSprite->GetHeight() / 2;
			entering_player_position.x = x;
			break;
		case Door::LeftD:
			ItemSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/doors/LDoor.png"), 4);
			entering_player_position.y = y - 16; 
			entering_player_position.x = x + ItemSprite->GetWidth()/2;
			break;
		}
		DoorAnimation = new Animator(ItemSprite, 15.0f);
		x2 = x + (ItemSprite->GetWidth());
		y2 = y + ItemSprite->GetHeight();
	}
	~Door() {
		delete DoorAnimation;
		DoorAnimation = nullptr;
		delete ItemSprite;
		ItemSprite = nullptr;
	}
	bool Manage(Tmpl8::Surface* screen, Player& player, int click, float deltaTime, int mousex, int mousey);
	int OpenAnimation(Tmpl8::Surface* screen, float deltaTime);
	void SetEnteringPosition(Player& player);
	void ResetDraw() const;
	int GetType();
};

