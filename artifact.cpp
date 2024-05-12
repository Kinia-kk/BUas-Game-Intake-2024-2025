#include "artifact.h"
bool Artifact::Manage(Tmpl8::Surface* screen, Player &player, int &click, float deltaTime, int mousex, int mousey) {
	Animation->Draw(screen,x,y);
	Animation->Update(deltaTime);
	if (Collision(player) && click && MouseInteraction(mousex, mousey)) return 1;
	return 0;
}