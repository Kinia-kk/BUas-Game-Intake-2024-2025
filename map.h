#pragma once
#include "surface.h"

class Map
{
	Tmpl8::Sprite mapframeSprite;
	Tmpl8::Sprite roomtileSprite;
	Tmpl8::Sprite pointerSprite;
	bool map[4][4] = { 0 };

public:
	Map():mapframeSprite(Tmpl8::Sprite(new Tmpl8::Surface("assets/minimap/mapframe.png"), 1)), 
		roomtileSprite(Tmpl8::Sprite(new Tmpl8::Surface("assets/minimap/maproom.png"), 1)), 
		pointerSprite(Tmpl8::Sprite(new Tmpl8::Surface("assets/minimap/dot.png"), 1)){
		
	}
	void DrawMap(Tmpl8::Surface* screen, int player_x, int player_y);
	void MarkAsKnown(int x, int y);
};

