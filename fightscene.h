#pragma once
#include "surface.h"
#include "player.h"
#include "enemy.h"
#include "healthbar.h"
#include "timer.h"
#include "statswindow.h"

namespace Tmpl8 {
	class Fightscene
	{
		Enemy enemy;
		Sprite attackback;
		Healthbar player_healthbar;
		Healthbar enemy_healthbar;
		Button attack;
		Button escape;
		StatsWindow statswindow;
		Timer TextTimer;
		
		int points;
		bool guard_try;
		int enemytype;
		bool escape_try;
		int GameState;
		enum
		{
			PLAYERTURN,
			ENEMYTURN,
			PLAYERATTACK,
			ENEMYATTACK,
			WIN,
			LOSE,
			ENEMYHIT,
			PLAYERHIT,
			ENEMYDIE,
			PLAYERDIE,
			PLAYERESCAPE,
			ENEMYESCAPE,
			SHOWINFO
		};
		enum {
			EnemyAttacked,
			PlayerAttacked,
			GoblinEscaped,
			SkeletonBlockedAttack
		};
		enum {
			Goblin = 1,
			Skeleton = 3
		};
		int textevent;
	public:
		Fightscene(std::array<int,4> arr, int levelnumber):enemy(levelnumber), attackback(Sprite(new Surface("assets/attack_back.png"), 1)), attack(300, 395, "assets/buttons/fight_buttons_attack.png", 3), 
		escape(400, 395, "assets/buttons/fight_buttons_escape.png", 3), statswindow(arr), enemytype(enemy.GetEnemyType())
		{
			guard_try = 0;
			GameState = PLAYERTURN;
		}
		int ManageFight(Surface* screen, Player& player, int mousex, int mousey, int& click, float deltaTime);
		void Disabled_buttons(Surface* screen);
		void ShowFightUI(Surface* screen, Player& player);
		
	};

};
