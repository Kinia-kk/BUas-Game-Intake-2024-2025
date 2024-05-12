#include "map.h"
void Map::MarkAsKnown(int x, int y) {
	map[y][x] = 1;
}
void Map::DrawMap(Tmpl8::Surface* screen, int player_x, int player_y){
	mapframeSprite.Draw(screen, 680, 392);
	for (int x = 0; x < 4; x++) {
		for (int y = 0; y < 4; y++) {
			if (map[y][x]) roomtileSprite.Draw(screen, 690 + 25 * y, 400 + 25 * x);
		}
	}
	pointerSprite.Draw(screen, 694 + 25 * player_x, 403 + 25 * player_y);
}