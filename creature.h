#pragma once
#include "template.h"
#include "animator.h"
#include "surface.h"
#include <random>

class Creature
{
public:

	Creature(){}
	~Creature() {
		delete AttackAnimation;
		AttackAnimation = nullptr;
		delete IdleAnimation;
		IdleAnimation = nullptr;
		delete DeathAnimation;
		DeathAnimation = nullptr;
		delete HitAnimation;
		HitAnimation = nullptr;
		if (SpecialAnimation != nullptr) {
			delete SpecialAnimation;
			SpecialAnimation = nullptr;
		}
	}
	//Animation functions
	int Attack_anim(Tmpl8::Surface* screen, float deltaTime);
	void Idle_anim(Tmpl8::Surface* screen, float deltaTime);
	int Death_anim(Tmpl8::Surface* screen, float deltaTime);
	int Hit_anim(Tmpl8::Surface* screen, float deltaTime);
	int Special_anim(Tmpl8::Surface* screen, float deltaTime);
	void Reset_idle_anim();

	bool RandomEvent(); // for different events
	void Damage(int damage);
	int Attack();
	int GetHealth() const;

protected:
	Animator* AttackAnimation;
	Animator* IdleAnimation;
	Animator* DeathAnimation;
	Animator* HitAnimation;
	Animator* SpecialAnimation = nullptr; //only for Goblin and Skeleton
	void SetSprites(Tmpl8::Sprite& AttackSprite, Tmpl8::Sprite& IdleSprite, Tmpl8::Sprite& DeathSprite, Tmpl8::Sprite& HitSprite, float attackspeed, float idlespeed, float deathspeed, float hitspeed);
	void Creature::SetSpecialSprite(Tmpl8::Sprite& SpecialSprite, float specialspeed);
	std::random_device rd;
	int attack_min;
	int attack_max;
	int endurance;
	int health;
	float chance; //for escape and block
	int attack_pos_x, attack_pos_y; //for fighting screen
};


