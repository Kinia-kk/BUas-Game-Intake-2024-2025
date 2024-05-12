#include "door.h"

int Door::OpenAnimation(Tmpl8::Surface* screen, float deltaTime) {
	DoorAnimation->Update(deltaTime);
	return DoorAnimation->Draw(screen, x, y);
}

void Door::ResetDraw() const {
	ItemSprite->SetFrame(0);
}

bool Door::Manage(Tmpl8::Surface* screen, Player& player, int click, float deltaTime, int mousex, int mousey) {
	switch (state)
	{
	case Door::Close:
		Draw(screen);
		if (player.GetEnteringState() == 0 && Collision(player) == 1 && click && MouseInteraction(mousex, mousey)) { 
			state = Opening; 
			player.SetEnteringState(1);
		}
		break;
	case Door::Opening:
		if (OpenAnimation(screen, deltaTime) == 1) { 
			state = Close; 
			ResetDraw();
			player.SetEnteringState(0);
			return 1;
		}
		break;
	}
	return 0;
}
void Door::SetEnteringPosition(Player &player) {
	player.SetX(entering_player_position.x);
	player.SetY(entering_player_position.y);
}
int Door::GetType() {
	return type;
}