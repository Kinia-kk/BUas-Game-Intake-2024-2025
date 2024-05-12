#include "game.h"


namespace Tmpl8
{
	void Game::Shutdown()
	{
	}
	
	void Game::Init()
	{
	}
	std::random_device rd;
	std::minstd_rand rr(rd());
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0x272736);
		deltaTime = deltaTime / 1000.0f;
		
		switch (gameState) {
		case MenuScreen:
			menufollow = menu.LoadMenu(1, screen, mousex, mousey, click); //Load Menu
			switch (menufollow) {
			case 1:
				gameState = GeneratingMap;
				player = new Player(0, 0, 110);
				levelnumber = 0;
				break;
			case 2:
				gameState = HowToPlay;
			}
			break;
		case HowToPlay:
			if (Instruction.Show(screen, mousex, mousey, click)) gameState = MenuScreen;
			break;
		case GeneratingMap: //generating level map when start and when changing floors
			levelnumber++;
			level = new Level(levelnumber);
			level->RoomsLocation(*player);
			gameState = ExploringMap;
			break;
		case ExploringMap: //when player move on screen
			levelstate = level->Manage(screen, *player, click, deltaTime, mousex, mousey);
			if ( levelstate == 1) 
			{ 
				if (levelnumber == 12) { 
					fight = new Fightscene(player->CreateStatsArray(), levelnumber);
					gameState = Fighting; 
				}
				else gameState = CheckingCorridoor;
			}
			if (levelstate == 2)
				gameState = Descending;
			if (levelstate == 3) {
				gameState = Win;
				finalscore = player->GetGold();
			}
			if (levelstate == 2 && levelnumber == 11) {
				levelnumber++;
				level = new Level(levelnumber);
				level->BossLevelGenerator(*player);
				gameState = ExploringMap;
			}
			break;
		case CheckingCorridoor: //checking if there is an enemy in the corridor
			//optimal change for changing probability (did that way after Jeremiah suggestion during C++ Fast Tract event)
			if (b(rr, p(0.35f - (player->GetStealth() / 100)))) {
				fight = new Fightscene(player->CreateStatsArray(), levelnumber);
				gameState = Fighting; }
			else gameState = ExploringMap;
			
			break;
		case Fighting: //fight
			fightresult = fight->ManageFight(screen, *player, mousex, mousey, click, deltaTime);
			if (fightresult == 1) { 
				delete fight;
				fight = nullptr;
				gameState = ExploringMap; 
			}
			if (fightresult == 3) gameState = Lose;
			break;
		case Descending: //changing levels to go deeper
			delete level;
			level = nullptr;
			gameState = GeneratingMap;
			break;
		case Lose: //lose screen
			delete player;
			player = nullptr;
			fightresult = endscreens.ShowLoseScreen(screen, mousex, mousey, click);
			if (fightresult == 1) gameState = PlayAgain;
			if (fightresult == 2) gameState = MenuScreen;
			break;
		case Win: //win screen
			delete player;
			player = nullptr;
			fightresult = endscreens.ShowWinScreen(screen, mousex, mousey, click, finalscore);
			if (fightresult == 1) gameState = PlayAgain;
			if (fightresult == 2) gameState = MenuScreen;
			break;
		case PlayAgain: //play again
			levelnumber = 0;
			player = new Player(0, 0, 110);
			gameState = GeneratingMap;
			break;
		}
		
		
	}
};