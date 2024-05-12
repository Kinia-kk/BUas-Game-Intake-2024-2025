#include "food.h"


bool Food::Update(Tmpl8::Surface* screen, Player& player) {
	Draw(screen);
	if (Collision(player) == 1) {
		player.GainHealth(health);
		return 1;
		//delete this;
	}
	return 0;
}
