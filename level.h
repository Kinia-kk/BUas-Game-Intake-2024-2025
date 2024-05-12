#pragma once
#include "template.h"
#include "surface.h"
#include <string>
#include <vector>
#include <array>
#include <random>
#include "door.h"
#include "player.h"
#include "healthbar.h"
#include "food.h"
#include "chest.h"
#include "stairs.h"
#include "map.h"
#include "artifact.h"

	class Level {
	private:
		int number_of_rooms; //number of additional rooms (without default first room)
		struct Coordinates {
			int x;
			int y;
		};
		Coordinates lastroom;
		Coordinates player_position; //current player positon on map
		Coordinates starting_position; // default room position on map
		Tmpl8::Surface tiles;
		int level_number;
		Healthbar player_healthbar;
		Artifact* artifact = nullptr;
		int direction_mask[2][4] = { 0,1,0,-1,-1,0,1,0 };
		//int dungeon[4][4] = { 0 }; // temporary dungeon map
		Map map;
		enum {
			Top,
			Right,
			Bottom,
			Left
		};
		int inverted_directions[4] = { Bottom,Left,Top,Right };
		//array of Tiles for map devided into directions
		std::array<int, 5> backwallnormal = { 0,1,2, 1, 2 };
		std::array<int, 2> frontwallnormal = { 1,2 };
		std::array<int, 4> backwallspecial = { 3,4,5,6 };
		std::array<int, 5> bfloor = { 7, 8, 9, 10, 18 };
		std::random_device rd;
		struct Room {
			std::vector<std::vector<Coordinates>> Tilemap;
			int x;
			int y;
			int w;
			int h;
			bool RoomState = false;
			Stairs* stairs = nullptr;
			std::vector<Door*> doors;
			std::vector<Food*> foods;
			std::vector<Chest*> chests;
		};
		Room DungeonRooms[4][4]; // Dungeon map data


	public:
		Level(int l_number) : tiles("assets/TileMap.png") {
			level_number = l_number;
		}
		~Level() {
			for (auto room : DungeonRooms) {
				room->doors.clear();
				room->foods.clear();
				room->chests.clear();
				if (room->stairs != nullptr) {
					delete room->stairs;
					room->stairs = nullptr;
				}
			}
		}

		void RandomRoomSize(Room& room);
		void RoomsLocation(Player& player);
		void DrawRoom(Tmpl8::Surface* screen);
		void DrawFrontWall(Tmpl8::Surface* screen, Room& room);
		void ModifyMap(Coordinates roompos);
		void SetDoor(int type, Coordinates pos);
		int Manage(Tmpl8::Surface* screen, Player& player, int& click, float deltaTime, int mousex, int mousey);
		std::array<int, 4> GetRoomCollider(Room room);
		void ShowUI(Tmpl8::Surface* screen, Player& player);
		void GenerateFood(Room& room);
		void GenerateChests(Room& room);
		int DoorInteract(Door& door, Tmpl8::Surface* screen, Player& player, int& click, float deltaTime, int mousex, int mousey);
		void AddStairs(Room& room);
		void BossLevelGenerator(Player& player);
		void WholeRoomGenerator(int direction, Coordinates& nextroom);
	};
