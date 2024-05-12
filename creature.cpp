#include "creature.h"
int Creature::Attack() {
	std::minstd_rand r(rd());
	std::uniform_int_distribution<> rattack(attack_min, attack_max);
	return rattack(r);
}
int Creature::Attack_anim(Tmpl8::Surface* screen, float deltaTime)
{
	AttackAnimation->Update(deltaTime);
	return AttackAnimation->Draw(screen, attack_pos_x, attack_pos_y);

}
int Creature::Death_anim(Tmpl8::Surface* screen, float deltaTime)
{
	DeathAnimation->Update(deltaTime);
	return DeathAnimation->Draw(screen, attack_pos_x, attack_pos_y);

}
int Creature::Hit_anim(Tmpl8::Surface* screen, float deltaTime)
{
	HitAnimation->Update(deltaTime);
	return HitAnimation->Draw(screen, attack_pos_x, attack_pos_y);

}
void Creature::Idle_anim(Tmpl8::Surface* screen, float deltaTime)
{
	IdleAnimation->Update(deltaTime);
	IdleAnimation->Draw(screen, attack_pos_x, attack_pos_y);
}

void Creature::Reset_idle_anim()
{
	IdleAnimation->ResetAnimation();
}

int Creature::Special_anim(Tmpl8::Surface* screen, float deltaTime)
{
	if (SpecialAnimation == nullptr) return 0;
	SpecialAnimation->Update(deltaTime);
	return SpecialAnimation->Draw(screen, attack_pos_x, attack_pos_y);

}
void Creature::Damage(int damage) {
	std::minstd_rand r(rd());
	std::uniform_int_distribution<> rendurance(0, endurance);
	int obtained_damge = damage - rendurance(r);
	if (obtained_damge > 0)
	{
		health = health - obtained_damge;
	}
	else health = health - 1;
}

int Creature::GetHealth() const{
	return health;
}

void Creature::SetSprites(Tmpl8::Sprite& AttackSprite, Tmpl8::Sprite& IdleSprite, Tmpl8::Sprite& DeathSprite, Tmpl8::Sprite& HitSprite, float attackspeed, float idlespeed, float deathspeed, float hitspeed) {
	AttackAnimation = new Animator(&AttackSprite, attackspeed);
	IdleAnimation = new Animator(&IdleSprite, idlespeed);
	DeathAnimation = new Animator(&DeathSprite, deathspeed);
	HitAnimation = new Animator(&HitSprite, hitspeed);
}

void Creature::SetSpecialSprite(Tmpl8::Sprite& SpecialSprite,float specialspeed) {
	SpecialAnimation = new Animator(&SpecialSprite, specialspeed);
}

bool Creature::RandomEvent() {
	std::bernoulli_distribution b(chance);
	std::minstd_rand r(rd());
	bool luck = b(r);
	if (luck == true)
	{
		return 1;
	}
	return 0;
}