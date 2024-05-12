#include "statswindow.h"
#include <string>
void StatsWindow::ShowUpButtons(int& remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click) {
	if (remaining_points > 0) 
	{
		for (int i = 0; i < 4; i++)
		{
			if(temporarily_stats[i] + stats[i] == max_stats[i]) up_buttons[i]->ShowDisabled(screen);
			else {
				if (up_buttons[i]->ShowandClick(screen, mousex, mousey, click) == true)
				{
					remaining_points--;
					temporarily_stats[i]++;
				}
			}
		}
	}
	else {
		for (int i = 0; i < 4; i++)
		{
			up_buttons[i]->ShowDisabled(screen);
		}
	}
}
void StatsWindow::ShowDownButtons(int& remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click) {
	for (int i = 0; i < 4; i++)
	{
		if (temporarily_stats[i] == 0)
		{
			down_buttons[i]->ShowDisabled(screen);
		}
		else {
			if (down_buttons[i]->ShowandClick(screen, mousex, mousey, click) == true)
			{
				remaining_points++;
				temporarily_stats[i]--;
			}
		}
	}
}
void StatsWindow::ShowBackground(Tmpl8::Surface* screen)
{
	statswindowSprite.Draw(screen, 280, 50);
}
void StatsWindow::ShowPointsRemaining(int remaining_points, Tmpl8::Surface* screen) const {
	screen->Print(std::to_string(remaining_points).c_str(), 490, 365, 0xffffff, 3);
}
void StatsWindow::ShowStats(Tmpl8::Surface* screen) {
	for (int i = 0; i < 4; i++)
	{
		screen->Print(std::to_string(temporarily_stats[i] + stats[i]).c_str(), 430, 170 + 50 * i, 0xffffff, 3);
	}
}
bool StatsWindow::Show(int& remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click) {
	ShowBackground(screen);
	ShowUpButtons(remaining_points, screen, mousex, mousey, click);
	ShowDownButtons(remaining_points, screen, mousex, mousey, click);
	ShowPointsRemaining(remaining_points, screen);
	ShowStats(screen);
	return ShowAcceptButton(remaining_points, screen, mousex, mousey, click);
}
bool StatsWindow::ShowAcceptButton(int remaining_points, Tmpl8::Surface* screen, int mousex, int mousey, int& click) {
	if (remaining_points == 0)
	{
		return AcceptButton->ShowandClick(screen, mousex, mousey, click);
	}
	else {
		AcceptButton->ShowDisabled(screen);
	}
	return 0;
}
std::array<int, 4> StatsWindow::GetModifiedStats() {
	return temporarily_stats;
}

bool StatsWindow::MaxStats() {
	for (int i = 0; i < 4; i++) {
		if (temporarily_stats[i] + stats[i] != max_stats[i]) return false;
	}
	return true;
}