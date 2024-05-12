#include "enemy.h"
int Enemy::DefineEnemy(int levelnumber) { //Define enemy type
	std::random_device rd;
	std::minstd_rand r(rd());
	int condition = levelnumber / 4;
	if(!condition) return 0;
	if (condition == 1) {
		std::bernoulli_distribution b(0.4 + (levelnumber * 2)/100);
		if (b(rd)) return 1;
		else return 0;
	}
	if (condition == 2) {
		std::bernoulli_distribution b1(0.4 + (levelnumber * 2) / 100);
		std::bernoulli_distribution b2(0.5 + (levelnumber * 2) / 100);
		if (b1(rd)) return 1;
		else {
			if (b2(rd)) return 2;
			else return 0;
		}
	}
	if (condition == 3) {
		return 3;
	}
	return 0;
}
int Enemy::GetEnemyType() const{
	return EnemyType;
}
int Enemy::GivePoints() const {
	return points;
}