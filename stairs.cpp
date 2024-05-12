#include "stairs.h"
bool Stairs::PrintOrEnter(Tmpl8::Surface* screen, Player& player, int click, int mousex, int mousey) {
	Draw(screen);
	if (Collision(player) == 1 && click && MouseInteraction(mousex, mousey)) {
		player.SetEnteringState(0);
		return 1;
	}
	return 0;
}