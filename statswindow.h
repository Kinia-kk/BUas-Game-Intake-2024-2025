#pragma once
#include"template.h"
#include "button.h"
#include <array>
class StatsWindow
{
		std::array<int, 4> stats;
		std::array<int, 4> temporarily_stats = { 0 };
		std::array<int, 4> max_stats = { 120, 90, 60, 30 };
		Button* up_buttons[4];
		Button* down_buttons[4];
		Button* AcceptButton;
		Tmpl8::Sprite statswindowSprite;


	public:
		StatsWindow(std::array<int, 4> arr) : statswindowSprite(Tmpl8::Sprite(new Tmpl8::Surface("assets/stats_window.png"), 1))
		{
			stats = arr;
			AcceptButton = new Button(460, 400, "assets/buttons/accept_button_1.png", 3);
			for (int i = 0; i < 4; i++)
			{
				up_buttons[i] = new Button(470, 155 + 50 * i, "assets/buttons/up_buttons.png", 3);
				down_buttons[i] = new Button(470, 175 + 50 * i, "assets/buttons/down_buttons.png", 3);
			}
		}
		~StatsWindow() {
			for (int i = 0; i < 4; i++)
			{
				delete up_buttons[i];
				up_buttons[i] = nullptr;
				delete down_buttons[i];
				down_buttons[i] = nullptr;
			}
			delete AcceptButton;
			AcceptButton = nullptr;
		}
		bool Show(int& remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click);
		std::array<int, 4> GetModifiedStats();
		bool MaxStats();
	private:
		void ShowUpButtons(int& remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click);
		void ShowDownButtons(int& remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click);
		void ShowBackground(Tmpl8::Surface* screen);
		void ShowPointsRemaining(int remaining_points, Tmpl8::Surface* screen) const;
		void ShowStats(Tmpl8::Surface* screen);
		bool ShowAcceptButton(int remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click);
};

