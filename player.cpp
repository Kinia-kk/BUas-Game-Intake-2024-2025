#include "surface.h"
#include "player.h"
#include "template.h"
#include "array"

#define WIN32_LEAN_AND_MEAN
#include "windows.h"

	void Player::Move(Tmpl8::Surface* screen, std::array<int, 4> mapcollider, float deltaTime) {
		//character movement || else are included to prevent from going two directions at the same time
		framehelp++;
		if (GetKeyState('W')<0) { //solution for implementing wsad keys found on https://stackoverflow.com/a/37117560
			y = static_cast<int>(round(y - 100 * deltaTime));
			if (y + PlayerSprite.GetHeight() / 2 < mapcollider[Top])y = mapcollider[Top] - PlayerSprite.GetHeight() / 2;
			if (framehelp >= 60) framehelp = 10;
		}else
			if (GetAsyncKeyState('S')<0) {
			y = static_cast<int>(round(y + 100 * deltaTime));
			if (y + PlayerSprite.GetHeight()/2> mapcollider[Bottom])y = mapcollider[Bottom] - PlayerSprite.GetHeight() / 2;
			if (framehelp <=69 || framehelp >= 120) framehelp = 69;
		}else
		if (GetKeyState('A')<0) {
			x = static_cast<int>(round(x - 100 * deltaTime));
			if (x+16 < mapcollider[Left])x = mapcollider[Left] - 16;
			if (framehelp <= 129 || framehelp >= 180) framehelp = 129;
		}
		else
			if (GetKeyState('D')<0) {
				x = static_cast<int>(round(x + 100 * deltaTime));
				if (x+16 > mapcollider[Right])x = mapcollider[Right]-16;
				if (framehelp <= 189 || framehelp >= 240) framehelp = 189;
			}
			else framehelp = 110;
		int frame = (int)(framehelp / 10);
		PlayerSprite.SetFrame(frame);
		PlayerSprite.Draw(screen, x, y);
	}

	void Player::UpdateStats(std::array<int, 4> new_stats) {
		attack_max += new_stats[AttackS];
		attack_min += new_stats[AttackS];
		endurance += new_stats[EnduranceS];
		runaway += new_stats[RunawayS];
		stealth += new_stats[StealthS];
	}

	std::array<int, 4> Player::CreateStatsArray() {
		std::array<int, 4> stats;
		stats[AttackS] = attack_min;
		stats[EnduranceS] = endurance;
		stats[RunawayS] = runaway;
		stats[StealthS] = stealth;

		return stats;
	}

	int Player::GetX() const {
		return x;
	}

	int Player::GetY() const {
		return y;
	}
	int Player::GetX2() {
		return x + PlayerSprite.GetWidth();
	}
	int Player::GetY2() {
		return y + PlayerSprite.GetHeight();
	}
	void Player::SetX(int xx)  {
		x = xx;
	}

	void Player::SetY(int yy)  {
		y = yy;
	}

	int Player::GetStealth() {
		return stealth;
	}
	void Player::SetEnteringState(bool state) {
		entering_door = state;
	}

	bool Player::GetEnteringState() {
		return entering_door;
	}
	int Player::GetGold() {
		return gold;
	}
	void Player::UpdateGold(int moregold) {
		gold += moregold;
	}
	void Player::GainHealth(int more) {
		health += more;
	}

	void Player::SetBossState() {
		boss_defeated = true;
	}
	bool Player::GetBossState() {
		return boss_defeated;
	}