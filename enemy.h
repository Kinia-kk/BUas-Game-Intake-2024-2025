#pragma once
#include "surface.h"
#include "player.h"
#include "animator.h"
#include <memory>
	class Enemy : public Creature
	{
		Tmpl8::Sprite *EnemyAttackSprite;
		Tmpl8::Sprite *EnemyIdleSprite;
		Tmpl8::Sprite *EnemyDeathSprite;
		Tmpl8::Sprite *EnemyHitSprite;
		Tmpl8::Sprite *EnemySpecialSprite;
		int points;
		int EnemyType;
		enum {
			Eye,
			Goblin,
			Mushroom,
			Skeleton
		};

	public:
		//Enemy statistics and sprite
		int DefineEnemy(int levelnumber);
		int GetEnemyType() const;
		int GivePoints() const;
		Enemy(int levelnumber){
			EnemyType = DefineEnemy(levelnumber); //use defined type to give right statistics
			switch (EnemyType)
			{
			case Eye:
				EnemyAttackSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/En_Attack.png"), 8);
				EnemyIdleSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/En_Idle.png"), 8);
				EnemyDeathSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/E_Death.png"), 4);
				EnemyHitSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/E_Hit.png"), 4);
				EnemySpecialSprite = nullptr;
				SetSprites(*EnemyAttackSprite, *EnemyIdleSprite, *EnemyDeathSprite, *EnemyHitSprite, 10.0f, 15.0f, 10.0f, 10.0f);
				chance = 0.5f;
				health = 50;
				endurance = 5;
				attack_max = 5;
				attack_min = 2;
				attack_pos_x = 500;
				attack_pos_y = 0;
				points = 1;
				break;
			case Goblin:
				EnemyAttackSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EAttack4.png"), 8);
				EnemyIdleSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EIdle4.png"), 4);
				EnemyDeathSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EDeath4.png"), 4);
				EnemyHitSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EHit4.png"), 4);
				EnemySpecialSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/ESpecial4.png"), 8);
				SetSprites(*EnemyAttackSprite, *EnemyIdleSprite, *EnemyDeathSprite, *EnemyHitSprite, 8.0f, 10.0f, 7.0f, 7.0f);
				SetSpecialSprite(*EnemySpecialSprite, 10.0f);
				chance = 0.2f;
				health = 100;
				endurance = 10;
				attack_max = 10;
				attack_min = 5;
				attack_pos_x = 450;
				attack_pos_y = 57;
				points = 2;
				break;
			case Mushroom:
				EnemyAttackSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EAttack3.png"), 8);
				EnemyIdleSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EIdle3.png"), 4);
				EnemyDeathSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EDeath3.png"), 4);
				EnemyHitSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EHit3.png"), 4);
				EnemySpecialSprite = nullptr;
				SetSprites(*EnemyAttackSprite, *EnemyIdleSprite, *EnemyDeathSprite, *EnemyHitSprite, 8.0f, 8.0f, 7.0f, 7.0f);
				chance = 0.5f;
				health = 150;
				endurance = 20;
				attack_max = 30;
				attack_min = 15;
				attack_pos_x = 450;
				attack_pos_y = 57;
				points = 3;
				break;
			case Skeleton:
				EnemyAttackSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EAttack2.png"), 8);
				EnemyIdleSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EIdle2.png"), 4);
				EnemyDeathSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EDeath2.png"), 4);
				EnemyHitSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/EHit2.png"), 4);
				EnemySpecialSprite = new Tmpl8::Sprite(new Tmpl8::Surface("assets/enemy/ESpecial2.png"), 4);
				SetSprites(*EnemyAttackSprite, *EnemyIdleSprite, *EnemyDeathSprite, *EnemyHitSprite, 7.0f, 8.0f, 7.0f, 7.0f);
				SetSpecialSprite(*EnemySpecialSprite, 10.0f);
				chance = 0.4f;
				health = 200;
				endurance = 40;
				attack_max = 40;
				attack_min = 10;
				attack_pos_x = 450;
				attack_pos_y = 57;
				points = 6;
				break;
			}
			
		}

		~Enemy(){
			delete EnemyAttackSprite;
			EnemyAttackSprite = nullptr;
			delete EnemyIdleSprite;
			EnemyIdleSprite = nullptr;
			delete EnemyDeathSprite;
			EnemyDeathSprite = nullptr;
			delete EnemyHitSprite;
			EnemyHitSprite = nullptr;
			if (EnemySpecialSprite != nullptr) { //only for goblin and skeleton
				delete EnemySpecialSprite;
				EnemySpecialSprite = nullptr;
			}
		}
	};


