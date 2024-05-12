#pragma once
#include "surface.h"
#include "menu.h"
#include "player.h"
#include "level.h"
#include "fightscene.h"
#include "door.h"
#include "food.h"
#include "chest.h"
#include "endscreens.h"
#include "instructionscreen.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button) { click = 0; }
	void MouseDown(int button) { click =  1; }
	void MouseMove(int x, int y) { mousex = x; mousey = y; }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
	int mousex, mousey;
	int click;
	Player* player;//(0, 0, 110)
	int enemytype = 3;
	int levelnumber = 0; 
	int fightresult;
	int finalscore;
	
	
	InstructionScreen Instruction;
	Menu menu;
	EndScreens endscreens;
	Level* level;
	Fightscene* fight;
	int levelstate;
	int menufollow;
	enum GameState {
		MenuScreen,
		HowToPlay,
		GeneratingMap,
		ExploringMap,
		CheckingCorridoor,
		Fighting,
		Descending,
		Lose,
		Win,
		PlayAgain
	};
	GameState gameState = MenuScreen;
	std::bernoulli_distribution b;
	using p = std::bernoulli_distribution::param_type;
};

}; // namespace Tmpl8