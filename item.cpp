#include "item.h"
void Item::Draw(Tmpl8::Surface* screen) {
	ItemSprite->Draw(screen, x, y);
}

bool Item::Collision(Player& player) {
	if (!(player.GetX() > x2) && !(player.GetX2() < x) && !(player.GetY() > y2) && !(player.GetY2()<y))
	{
		return 1;
	}
	return 0;
}

int Item::GetX(){
	return x;
}
int Item::GetY() {
	return y;
}
int Item::GetX2() {
	return x2;
}
int Item::GetY2() {
	return y2;
}

bool Item::WhileGeneratingCollision(int ix, int iy, int ix2, int iy2) {
	if (!(ix > x2) && !(ix2 < x) && !(iy > y2) && !(iy2 < y))
	{
		return 1;
	}
	return 0;
}

bool Item::MouseInteraction(int mousex, int mousey) {
	if (mousex >= x && mousex <= x2 && mousey >= y && mousey <= y2) return 1;
	return 0;
}
