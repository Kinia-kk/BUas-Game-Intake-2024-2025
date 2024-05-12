#pragma once
#include <string>
#include "animator.h"
#include "surface.h"
#include "creature.h"

	class Player : public Creature{
		Tmpl8::Sprite PlayerSprite;
		Tmpl8::Sprite PlayerSpriteAttack;
		Tmpl8::Sprite PlayerSpriteIdle;
		Tmpl8::Sprite PlayerSpriteDeath;
		Tmpl8::Sprite PlayerSpriteHit;
		int framehelp;
		int x;
		int y;
		int stealth;
		bool entering_door = false;
		int runaway;
		int gold = 0;
		bool boss_defeated = false;
		enum Stats {
			AttackS,
			EnduranceS,
			RunawayS,
			StealthS
		};
		enum {
			Top,
			Right,
			Bottom,
			Left
		};
	public:
		
		void Move(Tmpl8::Surface* screen, std::array<int, 4> mapcollider, float deltaTime);
		Player(int xx, int yy, int firstframe) : PlayerSprite(Tmpl8::Sprite(new Tmpl8::Surface("assets/player/move.png"), 24)), 
			PlayerSpriteAttack(Tmpl8::Sprite(new Tmpl8::Surface("assets/player/Attack.png"), 10)),
			PlayerSpriteIdle(Tmpl8::Sprite(new Tmpl8::Surface("assets/player/Idle.png"), 10)), 
			PlayerSpriteDeath(Tmpl8::Sprite(new Tmpl8::Surface("assets/player/Death.png"), 10)), 
			PlayerSpriteHit(Tmpl8::Sprite(new Tmpl8::Surface("assets/player/Hit.png"), 12))
		{
			SetSprites(PlayerSpriteAttack, PlayerSpriteIdle, PlayerSpriteDeath, PlayerSpriteHit, 10.0f, 15.0f, 10.0f, 10.0f);
			x = xx;
			y = yy;
			attack_pos_x = 10;
			attack_pos_y = 150;
			framehelp = firstframe;
			health = 50;
			attack_max = 20;
			attack_min = 10;
			endurance = 1;
			runaway = 1;
			stealth = 1;
			chance = 0.4f + runaway / 100.0f;
		}
		
		void UpdateStats(std::array<int,4> new_stats);
		int GetStealth();
		int GetX() const;
		int GetY() const;
		int GetX2();
		int GetY2();
		void SetX(int xx);
		void SetY(int yy);
		int GetGold();
		void GainHealth(int more);
		void UpdateGold(int moregold);
		void SetEnteringState(bool state);
		bool GetEnteringState();
		std::array<int, 4> CreateStatsArray();
		void SetBossState();
		bool GetBossState();
	};
