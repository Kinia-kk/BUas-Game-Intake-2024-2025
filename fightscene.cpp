#include "fightscene.h"
#include <iostream>


namespace Tmpl8 {
	int Fightscene::ManageFight(Surface* screen, Player& player, int mousex, int mousey, int& click, float deltaTime)
	{
		//Main body operating on actions during fight
		switch (GameState)
		{
		case PLAYERTURN: //Player decides what he/she wants to do
			ShowFightUI(screen, player);
			player.Idle_anim(screen, deltaTime);
			enemy.Idle_anim(screen, deltaTime);

			if (attack.ShowandClick(screen, mousex, mousey, click) == 1)
			{
				GameState = SHOWINFO;
				player.Reset_idle_anim();
				textevent = PlayerAttacked;
				
			}
			if (enemytype == Skeleton) escape.ShowDisabled(screen);
			else{
				if (escape.ShowandClick(screen, mousex, mousey, click) == 1)
				{
					escape_try = player.RandomEvent();
					GameState = PLAYERESCAPE;
				}
			}
			break;
		case ENEMYTURN: 
			ShowFightUI(screen, player);
			Disabled_buttons(screen);
			player.Idle_anim(screen, deltaTime);
			enemy.Idle_anim(screen, deltaTime);
			if (enemytype == Goblin && enemy.GetHealth() < 50 && enemy.RandomEvent())
			{
				GameState = SHOWINFO;
				textevent = GoblinEscaped;
				//Disabled_buttons(screen);
			}
			else {
				GameState = SHOWINFO;
				textevent = EnemyAttacked;
				//Disabled_buttons(screen);
			}
			break;
		case PLAYERATTACK: //Player decided to attack
			ShowFightUI(screen, player);
			Disabled_buttons(screen);
			
			if (player.Attack_anim(screen, deltaTime))
			{
				if (guard_try) GameState = ENEMYTURN;
				else {
					enemy.Damage(player.Attack());
					GameState = ENEMYHIT;
					enemy.Reset_idle_anim();
				}
			}
			if (guard_try)
			{
				enemy.Special_anim(screen, deltaTime);
			}
			else {
				enemy.Idle_anim(screen, deltaTime);
			}
			break;
		case ENEMYATTACK: //Enemy is attacking
			ShowFightUI(screen, player);
			Disabled_buttons(screen);
			player.Idle_anim(screen, deltaTime);

			if (enemy.Attack_anim(screen, deltaTime))
			{
				player.Damage(enemy.Attack());
				GameState = PLAYERHIT;
				player.Reset_idle_anim();
			}
			break;
		case WIN: //Player won the fight
			if (statswindow.Show(points, screen, mousex, mousey, click) == 1) {
				player.UpdateStats(statswindow.GetModifiedStats());
				if(enemytype == Skeleton) player.SetBossState();
				return 1;
			}
			break;
		case LOSE: //Player lost the game
			return 3;
			break;
		case ENEMYHIT:
			player.Idle_anim(screen, deltaTime);
			if (enemy.Hit_anim(screen, deltaTime))
			{
				if (enemy.GetHealth() <= 0)
					GameState = ENEMYDIE;
				else
					GameState = ENEMYTURN;
			}
			break;

		case PLAYERHIT:
			enemy.Idle_anim(screen, deltaTime);
			if (player.Hit_anim(screen, deltaTime))
			{
				if (player.GetHealth() <= 0)
					GameState = PLAYERDIE;
				else
					GameState = PLAYERTURN;
			}
			break;

		case ENEMYDIE:
			player.Idle_anim(screen, deltaTime);
			if (enemy.Death_anim(screen, deltaTime))
			{
					if(statswindow.MaxStats()) return 1; //check if player has already all max stats
					GameState = WIN;
					points = enemy.GivePoints();
			}
			break;

		case PLAYERDIE:
			enemy.Idle_anim(screen, deltaTime);
			if (player.Death_anim(screen, deltaTime))
			{
				GameState = LOSE;
			}
			break;
		case PLAYERESCAPE: //Player is trying to escape the battle
			ShowFightUI(screen, player);
			player.Idle_anim(screen, deltaTime);
			enemy.Idle_anim(screen, deltaTime);
			Disabled_buttons(screen);
			TextTimer.Update(deltaTime);
			if (escape_try == true)
			{
				screen->Print("Player escaped", 300, 335, 0xffffff, 2);
				if (TextTimer.CheckTime(1.5f) == true)
				{
					GameState = PLAYERTURN;
					TextTimer.Reset();
					return 1;
				}
			}
			else {
				screen->Print("Player failed to escape", 300, 335, 0xffffff, 2);
				if (TextTimer.CheckTime(1.5f) == true)
				{
					GameState = ENEMYTURN;
					TextTimer.Reset();
				}
			}
			break;

		case ENEMYESCAPE:
			player.Idle_anim(screen, deltaTime);
			if (enemy.Special_anim(screen, deltaTime))
			{
				return 1;
			}
			break;

		case SHOWINFO:
			ShowFightUI(screen, player);
			player.Idle_anim(screen, deltaTime);
			enemy.Idle_anim(screen, deltaTime);
			Disabled_buttons(screen);
			TextTimer.Update(deltaTime);
			switch (textevent)
			{
			case EnemyAttacked:
				screen->Print("Enemy attacked", 300, 335, 0xffffff, 2);
				if (TextTimer.CheckTime(1.0f) == true)
				{
					GameState = ENEMYATTACK;
					TextTimer.Reset();
				}
				break;
			case PlayerAttacked:
				screen->Print("Player attacked", 300, 335, 0xffffff, 2);
				if (TextTimer.CheckTime(1.0f) == true)
				{
					if (enemytype == Skeleton) {
						guard_try = enemy.RandomEvent();
						if (guard_try == 1) textevent = SkeletonBlockedAttack;
						else {
							GameState = PLAYERATTACK;
							TextTimer.Reset();
						}
					}else{
						GameState = PLAYERATTACK;
						TextTimer.Reset();
					}
				}
				break;
			case GoblinEscaped:
				screen->Print("Enemy escaped", 300, 335, 0xffffff, 2);
				if (TextTimer.CheckTime(1.5f) == true)
				{
					GameState = ENEMYESCAPE;
					TextTimer.Reset();
				}
				break;
			case SkeletonBlockedAttack:
				screen->Print("Enemy blocked your attack", 300, 335, 0xffffff, 2);
				if (TextTimer.CheckTime(1.0f) == true)
				{
					GameState = PLAYERATTACK;
					TextTimer.Reset();
				}
				break;
			}
			break;
		}
		return 0;
	}

	void Fightscene::Disabled_buttons(Surface* screen) 
	{
		attack.ShowDisabled(screen);
		escape.ShowDisabled(screen);
	}

	void Fightscene::ShowFightUI(Surface* screen, Player& player)
	{
		player_healthbar.ShowHealth(player.GetHealth(), screen, 75, 30, 10);
		enemy_healthbar.ShowHealth(enemy.GetHealth(), screen, 725 - enemy.GetHealth(), 30, 10);
		attackback.Draw(screen, 250, 347);
		screen->Print(std::to_string(player.GetHealth()).c_str(), 17, 28, 0xffffff, 3);
		screen->Print(std::to_string(enemy.GetHealth()).c_str(), 735, 28, 0xffffff, 3);
	}

};