#include "chest.h"
void Chest::Update(Tmpl8::Surface* screen, Player& player, float deltaTime, int click, int mousex, int mousey) {
	switch (chest_state)
	{
	case Chest::Close:
		Draw(screen);
		if (Collision(player) == 1 && click && MouseInteraction(mousex,mousey)) {
			chest_state = Opening;
		}
		break;
	case Chest::Opening:
		if (Open_anim(screen, deltaTime)) {
			player.UpdateGold(gold);
			chest_state = Open;
		}
		break;
	case Chest::Open:
		Draw(screen);
		break;
	}
}
int Chest::Open_anim(Tmpl8::Surface* screen, float deltaTime)
{
	ChestAnim->Update(deltaTime);
	return ChestAnim->Draw(screen, x, y);

}