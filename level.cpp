#include "level.h"
#include <iostream>
#include<vector>
#include <algorithm>
#include <random>


	
	void Level::RoomsLocation(Player& player) {
		//declering all random generators and distributions
		
		std::uniform_int_distribution<int> rrn(4, 12);
		std::uniform_int_distribution<int> rdirection(0, 3);
		std::uniform_int_distribution<int> rchanging(0, 3);
		std::minstd_rand r(rd());
		number_of_rooms = rrn(r);

		int direction;
		bool valid = true;
		Coordinates firstroom;
		Coordinates nextroom;
		Coordinates beforeroom;
		
		std::vector<int> first_surroundings = { Top,Right,Bottom,Left }; //possible directions from first room
		firstroom.x = rdirection(r);
		firstroom.y = rdirection(r);
		player_position = firstroom;
		map.MarkAsKnown(player_position.y, player_position.x);

		
		ModifyMap(firstroom); // Creating first room and setting player coordinates on map
		player.SetX((DungeonRooms[player_position.y][player_position.x].x + ((DungeonRooms[player_position.y][player_position.x].w) * 32) / 2) - 32);
		player.SetY((DungeonRooms[player_position.y][player_position.x].y + ((DungeonRooms[player_position.y][player_position.x].h) * 32) / 2) - 32);

		// Generating other rooms
		while (number_of_rooms) {

			if (first_surroundings.size() == 0) break;
			rchanging.param(std::uniform_int_distribution<int>::param_type(0, first_surroundings.size() - 1)); // adjusting available directions from first room
			direction = rchanging(r);

			nextroom.x = firstroom.x + direction_mask[0][first_surroundings[direction]];
			nextroom.y = firstroom.y + direction_mask[1][first_surroundings[direction]];
			if (nextroom.x >= 0 && nextroom.x < 4 && nextroom.y >= 0 && nextroom.y < 4 && DungeonRooms[nextroom.y][nextroom.x].RoomState != 1) {

				
				SetDoor(first_surroundings[direction], firstroom);
				WholeRoomGenerator(first_surroundings[direction], nextroom);
				
				first_surroundings.erase(first_surroundings.begin() + direction);

				
				valid = true;
				while (valid && number_of_rooms) {
					beforeroom = nextroom;
					direction = rdirection(r);
					nextroom.x = nextroom.x + direction_mask[0][direction];
					nextroom.y = nextroom.y + direction_mask[1][direction];
					if (nextroom.x >= 0 && nextroom.x < 4 && nextroom.y >= 0 && nextroom.y < 4 && DungeonRooms[nextroom.y][nextroom.x].RoomState != 1) {
						
						
						WholeRoomGenerator(direction, nextroom);
						
						SetDoor(direction, beforeroom);
						
					}
					else {
						valid = false;
					}
				}
			}
			else {
				first_surroundings.erase(first_surroundings.begin() + direction);
			}
		}
		AddStairs(DungeonRooms[lastroom.y][lastroom.x]);

	}
	void Level::WholeRoomGenerator(int direction, Coordinates& nextroom){
		std::bernoulli_distribution chestpresents(0.4f);
		std::minstd_rand r(rd());
		ModifyMap(nextroom);
		switch (direction)
		{
		case Top:
			SetDoor(Bottom, nextroom);
			break;
		case Right:
			SetDoor(Left, nextroom);
			break;
		case Bottom:
			SetDoor(Top, nextroom);
			break;
		case Left:
			SetDoor(Right, nextroom);
			break;
		}
		if (chestpresents(r)) GenerateChests(DungeonRooms[nextroom.y][nextroom.x]);
		else GenerateFood(DungeonRooms[nextroom.y][nextroom.x]);
		lastroom = nextroom;
		number_of_rooms--;
	}
	void Level::SetDoor(int type, Coordinates pos) {
		std::minstd_rand r(rd());
		int x = pos.x;
		int y = pos.y;
		int doorpos;
		std::uniform_int_distribution<> xrdoorpos(2, DungeonRooms[y][x].w - 4);
		std::uniform_int_distribution<> yrdoorpos(2, DungeonRooms[y][x].h - 4);
		Door* door;
		switch (type)
		{
		case Top:

			doorpos = xrdoorpos(r);
			DungeonRooms[y][x].Tilemap[0][doorpos] = { 19,0 };
			DungeonRooms[y][x].Tilemap[1][doorpos] = { 19,0 };
			DungeonRooms[y][x].Tilemap[0][doorpos + 1] = { 19,0 };
			DungeonRooms[y][x].Tilemap[1][doorpos + 1] = { 19,0 };

			door = new Door(type, DungeonRooms[y][x].x + 32 * doorpos, DungeonRooms[y][x].y);
			//Door door(type, DungeonRooms[y][x].x + 32 * doorpos, DungeonRooms[y][x].y);
			DungeonRooms[y][x].doors.push_back(door);
			break;
		case Right:

			doorpos = yrdoorpos(r);
			DungeonRooms[y][x].Tilemap[doorpos][DungeonRooms[y][x].w - 1] = { 19,0 };
			DungeonRooms[y][x].Tilemap[doorpos + 1][DungeonRooms[y][x].w - 1] = { 19,0 };


			door = new Door(type, DungeonRooms[y][x].x + 32 * (DungeonRooms[y][x].w - 2), DungeonRooms[y][x].y + doorpos * 32);
			DungeonRooms[y][x].doors.push_back(door);
			break;
		case Bottom:

			doorpos = xrdoorpos(r);
			DungeonRooms[y][x].Tilemap[DungeonRooms[y][x].h - 1][doorpos] = { 10,0 };
			DungeonRooms[y][x].Tilemap[DungeonRooms[y][x].h - 1][doorpos + 1] = { 10,0 };

			door = new Door(type, DungeonRooms[y][x].x + 32 * doorpos, DungeonRooms[y][x].y + (DungeonRooms[y][x].h - 2) * 32);
			DungeonRooms[y][x].doors.push_back(door);
			break;
		case Left:

			doorpos = yrdoorpos(r);
			DungeonRooms[y][x].Tilemap[doorpos][0] = { 19,0 };
			DungeonRooms[y][x].Tilemap[doorpos + 1][0] = { 19,0 };

			door = new Door(type, DungeonRooms[y][x].x, DungeonRooms[y][x].y + doorpos * 32);
			DungeonRooms[y][x].doors.push_back(door);
			break;
		}
		//delete door;
		//door = nullptr;
	}
	void Level::DrawRoom(Tmpl8::Surface* screen)
	{

		for (int y = 0; y < DungeonRooms[player_position.y][player_position.x].h - 1; y++)
		{
			for (int x = 0; x < DungeonRooms[player_position.y][player_position.x].w; x++)
			{
				int tx = DungeonRooms[player_position.y][player_position.x].Tilemap[y][x].x;
				int ty = DungeonRooms[player_position.y][player_position.x].Tilemap[y][x].y;
				Tmpl8::Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 640;
				Tmpl8::Pixel* dst = screen->GetBuffer() + DungeonRooms[player_position.y][player_position.x].x + x * 32 + DungeonRooms[player_position.y][player_position.x].y * 800 + y * 32 * 800;
				for (int i = 0; i < 32; i++, src += 640, dst += 800)
					for (int j = 0; j < 32; j++)
						dst[j] = src[j];
			}
		}

	}
	void Level::DrawFrontWall(Tmpl8::Surface* screen, Room& room) {
		for (int x = 0; x < room.w; x++) {
			int tx = room.Tilemap[room.h - 1][x].x;
			int ty = room.Tilemap[room.h - 1][x].y;
			Tmpl8::Pixel* src = tiles.GetBuffer() + tx * 32 + (ty * 32) * 640;
			Tmpl8::Pixel* dst = screen->GetBuffer() + room.x + x * 32 + room.y * 800 + (room.h - 1) * 32 * 800;
			for (int i = 0; i < 32; i++, src += 640, dst += 800)
				for (int j = 0; j < 32; j++)
					dst[j] = src[j];
		}
	}
	int Level::Manage(Tmpl8::Surface* screen, Player& player, int& click, float deltaTime, int mousex, int mousey) {
		DrawRoom(screen);
		//background doors
		for (auto door : DungeonRooms[player_position.y][player_position.x].doors) {
			if (door->GetType() == 2)continue;
			if (DoorInteract(*door, screen, player, click, deltaTime, mousex, mousey) == 1) return 1;
		}
		
		//chest
		std::vector<Chest*> afterplayer;
		for (auto chest : DungeonRooms[player_position.y][player_position.x].chests) {
			if (chest->GetY2() > player.GetY2()) afterplayer.push_back(chest);
			else chest->Update(screen, player, deltaTime, click, mousex, mousey);
		}
		//stairs
		if (DungeonRooms[player_position.y][player_position.x].stairs != nullptr) {

			if (DungeonRooms[player_position.y][player_position.x].stairs->PrintOrEnter(screen, player, click, mousex, mousey) == true)
				return 2;
		}
		//artifact
		if (artifact != nullptr && player.GetBossState()) {
			if (artifact->Manage(screen, player, click, deltaTime, mousex, mousey)) {
				delete artifact;
				artifact = nullptr;
				return 3;
			}
		}
		//foods items
		if (DungeonRooms[player_position.y][player_position.x].foods.size()) {
			for (int i = 0; i < DungeonRooms[player_position.y][player_position.x].foods.size(); ) {
				if (DungeonRooms[player_position.y][player_position.x].foods[i]->Update(screen, player))
				{
					DungeonRooms[player_position.y][player_position.x].foods.erase(DungeonRooms[player_position.y][player_position.x].foods.begin() + i);
				}
				else i++;
			}
		}
		//player movement
		player.Move(screen, GetRoomCollider(DungeonRooms[player_position.y][player_position.x]), deltaTime);
		//chests drawn on the player
		for (auto chest : afterplayer) {
			chest->Update(screen, player, deltaTime, click, mousex, mousey);
		}
		afterplayer.clear();
		//frontwall
		DrawFrontWall(screen, DungeonRooms[player_position.y][player_position.x]);
		//frontdoor
		for (auto door : DungeonRooms[player_position.y][player_position.x].doors) {
			if (door->GetType() != 2)continue;
			if (DoorInteract(*door, screen, player, click, deltaTime, mousex, mousey) == 1) return 1;
		}
		//UI
		ShowUI(screen, player);
		return 0;
	}
	int Level::DoorInteract(Door&door, Tmpl8::Surface* screen, Player& player, int& click, float deltaTime, int mousex, int mousey) {
		if (door.Manage(screen, player, click, deltaTime, mousex, mousey) == 1) {
			player_position.x += direction_mask[0][door.GetType()];
			player_position.y += direction_mask[1][door.GetType()];
			for (auto seconddoor : DungeonRooms[player_position.y][player_position.x].doors) {
				if (seconddoor->GetType() == inverted_directions[door.GetType()]) {
					seconddoor->SetEnteringPosition(player);
					//mark new rooms
					map.MarkAsKnown(player_position.y, player_position.x);
					return 1;
				}
			}

		}
		return 0;
	}
	void Level::ModifyMap(Coordinates roompos) {
		Room room1;
		room1.RoomState = true;
		if(level_number!=12)RandomRoomSize(room1);
		else {
			room1.w = 20;
			room1.h = 12;
			room1.x = 50;
			room1.y = 50;

		}
		Coordinates tile;
		int firstcoordinate;
		std::vector<Coordinates> line;
		std::vector<Coordinates> secondline;

		std::discrete_distribution<> rfloor({ 20, 20, 30, 30, 10 });
		std::discrete_distribution<> rfwall({ 50, 50 });
		std::discrete_distribution<> rbwall({ 10, 30,30 });
		std::minstd_rand r(rd());
		std::bernoulli_distribution b(0.1f);
		std::bernoulli_distribution rfloorsecondcoordinate(0.5f);
		//leftborder-------------------------
		tile = { 15,0 };
		line.push_back(tile);
		tile = { 15,1 };
		secondline.push_back(tile);
		//------------------------------
		//backwall creation-----------------------
		for (int i = 0; i < room1.w - 2; i++) {
			if (b(r))
			{
				tile = { backwallspecial[level_number / 4],0 };
			}
			else
			{
				firstcoordinate = rbwall(r);
				tile = { backwallnormal[firstcoordinate],0 };
			}

			line.push_back(tile);
			tile.y = 1;
			secondline.push_back(tile);
		}
		//rightborder-------------------------
		tile = { 14,0 };
		tile = { 14,1 };
		line.push_back(tile);
		secondline.push_back(tile);
		//------------------------------
		room1.Tilemap.push_back(line);
		room1.Tilemap.push_back(secondline);
		//----------------------------------------
		line.clear();

		//floor creation--------------------------
		for (int j = 0; j < room1.h - 3; j++) {
			//leftborder----------
			tile = { 15,1 };
			line.push_back(tile);
			//--------------------
			for (int i = 0; i < room1.w - 2; i++) {
				int firstcoordinate = rfloor(r);
				tile = { bfloor[firstcoordinate],rfloorsecondcoordinate(r) };
				line.push_back(tile);
			}
			//rightborder--------
			tile = { 14,1 };
			line.push_back(tile);
			//-------------------
			room1.Tilemap.push_back(line);
			line.clear();
		}
		line.clear();
		secondline.clear();
		//leftborder-------------------------
		tile = { 16,1 };
		//tile = { 16,1 };
		line.push_back(tile);
		//secondline.push_back(tile);
		//------------------------------
		//frontwall creation-----------------------
		for (int i = 0; i < room1.w - 2; i++) {
			int firstcoordinate = rfwall(r);
			tile = { frontwallnormal[firstcoordinate],0 };
			line.push_back(tile);
			//tile.y = 1;
			//secondline.push_back(tile);
		}
		//rightborder-------------------------
		tile = { 17,1 };
		//tile = { 17,1 };
		line.push_back(tile);
		//secondline.push_back(tile);
		//------------------------------
		room1.Tilemap.push_back(line);
		//room1.Tilemap.push_back(secondline);
		//----------------------------------------
		DungeonRooms[roompos.y][roompos.x] = room1;
	}

	void Level::RandomRoomSize(Room& room) {

		std::minstd_rand r(rd());
		std::uniform_int_distribution<> rw(9, 20);
		std::uniform_int_distribution<> rh(9, 12);

		room.w = rw(r);
		room.h = rh(r);
		int maxx = ScreenWidth - (room.w * 32) - 50;
		std::uniform_int_distribution<> rx(50, maxx);
		room.x = rx(r);
		int maxy = ScreenHeight - (room.h * 32) - 50;
		std::uniform_int_distribution<> ry(50, maxy);
		room.y = ry(r);
	}

	std::array<int, 4> Level::GetRoomCollider(Room room) {
		std::array<int, 4> collider;
		collider[Top] = room.y + 32;
		collider[Left] = room.x + 32;
		collider[Right] = room.x + 32 * (room.w - 2);
		collider[Bottom] = room.y + 32 * (room.h - 2);
		return collider;
	}

	void Level::ShowUI(Tmpl8::Surface* screen, Player& player) {
		player_healthbar.ShowHealth(player.GetHealth(), screen, 70, 10, 10);
		screen->Print(std::to_string(player.GetHealth()).c_str(), 12, 8, 0xffffff, 3);
		screen->Print("Gold: ", 12, 38, 0xffffff, 3);
		screen->Print(std::to_string(player.GetGold()).c_str(), 100, 38, 0xffffff, 3);
		screen->Print("Level: ", 655, 10, 0xffffff, 3);
		screen->Print(std::to_string(level_number).c_str(), 760, 10, 0xffffff, 3);
		map.DrawMap(screen, player_position.x, player_position.y);
	}

	void Level::GenerateFood(Room& room) {
		std::discrete_distribution<> rfood({ 30, 15, 10, 5, 50 });
		std::uniform_int_distribution<int> rx(room.x + 64, room.x + room.w * 32 - 64);
		std::uniform_int_distribution<int> ry(room.y + 96, room.y + room.h * 32 - 64);
		std::minstd_rand r(rd());
		Food* food_item;
		int max_number = 2;
		int food_type;
		int x;
		int y;
		bool invalid;
		do {
			food_type = rfood(r);
			if (food_type == 4) break;
			do {
				invalid = false;
				x = rx(r);
				y = ry(r);
				food_item = new Food(food_type, x, y);
				for (auto food : room.foods) {
					if (food->WhileGeneratingCollision(food_item->GetX(), food_item->GetY(), food_item->GetX2(), food_item->GetY2())) {
						delete food_item;
						food_item = nullptr;
						invalid = true;
						break;
					}
				}
			} while (invalid);
			room.foods.push_back(food_item);
			max_number--;
		} while (max_number);
	}

	void Level::GenerateChests(Room& room) {
		int chests_number = 0;
		std::discrete_distribution<> rchest({ 120, static_cast<double>(50 + 2*(level_number/4)), static_cast<double>(25 + 3 * (level_number / 4)), static_cast<double>(10 + 4 * (level_number / 4)) });
		std::minstd_rand r(rd());
		Chest* chest_item;


		if (room.w > 17 && room.h > 9) {
			chests_number = 3;
			chest_item = new Chest(room.x - 160 + ((room.w - 2) * 32) / 2, room.y + ((room.h - 2) * 32) / 2, rchest(r));
			room.chests.push_back(chest_item);
			chest_item = new Chest(room.x + ((room.w - 2) * 32) / 2, room.y + ((room.h - 2) * 32) / 2, rchest(r));
			room.chests.push_back(chest_item);
			chest_item = new Chest(room.x + 160 + ((room.w - 2) * 32) / 2, room.y + ((room.h - 2) * 32) / 2, rchest(r));
			room.chests.push_back(chest_item);
		}
		else
		{


			if (room.w > 14) {
				chests_number = 2;
				chest_item = new Chest(room.x - 64 + ((room.w - 2) * 32) / 2, room.y + ((room.h - 2) * 32) / 2, rchest(r));
				room.chests.push_back(chest_item);
				chest_item = new Chest(room.x + 64 + ((room.w - 2) * 32) / 2, room.y + ((room.h - 2) * 32) / 2, rchest(r));
				room.chests.push_back(chest_item);
			}
			else
			{
				if (room.w > 8) {
					chests_number = 1;
					chest_item = new Chest(room.x + ((room.w - 2) * 32) / 2, room.y + ((room.h - 2) * 32) / 2, rchest(r));
					room.chests.push_back(chest_item);
				}
			}
		}

		/*for (int i = 0; i < chests_number; i++) {
			chest_item = new Chest(room.x + i * 96 + ((room.w - 2)*32) / 2, room.y + ((room.h - 2)*32) / 2, rchest(r));
			room.chests.push_back(chest_item);
		}*/
	}

	void Level::AddStairs(Room& room) {
		std::minstd_rand r(rd());
		std::uniform_int_distribution<int> rx(4, room.w - 4);
		std::uniform_int_distribution<int> ry(4, room.h - 4);
		room.stairs = new Stairs(room.x + rx(r) * 32, room.y + ry(r) * 32);
		room.chests.clear();
	}

	void Level::BossLevelGenerator(Player& player) {
		Coordinates room;
		Chest* chest;
		//roombeforeboss
		room.x = 1;
		room.y = 1;
		player_position = room;
		map.MarkAsKnown(player_position.y, player_position.x);
		//RandomRoomSize(DungeonRooms[room.y][room.x]);
		ModifyMap(room);
		SetDoor(Bottom, room);
		GenerateFood(DungeonRooms[room.y][room.x]);
		//bossroom
		room.x = 1;
		room.y = 2;
		ModifyMap(room);
		SetDoor(Top, room);
		chest = new Chest(132, 200, 3);
		DungeonRooms[room.y][room.x].chests.push_back(chest);
		chest = new Chest(532, 200, 3);
		DungeonRooms[room.y][room.x].chests.push_back(chest);
		chest = new Chest(332, 325, 3);
		DungeonRooms[room.y][room.x].chests.push_back(chest);
		//artefact
		artifact = new Artifact(332, 160);
	}

	
	