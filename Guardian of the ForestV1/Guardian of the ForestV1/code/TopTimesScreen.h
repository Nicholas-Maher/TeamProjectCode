#pragma once
#include "Screen.h"
#include <fstream>
#include <vector>

using namespace std;

class TopTimesScreen : public Screen
{

private:

	string m_FileToLoad;

	Text m_TimesText;

	Button m_MainMenuButton;
	Button m_ResetTimesButton;

	vector<int> m_TopTimes;
	int m_NumTopTimes = 5;

public:
	TopTimesScreen();

	FloatRect getMainMenuButton() const;
	FloatRect getResetTimesButton() const;

	void setTimesText();

	void loadTopTimesFile();
	bool isATopTime(int time);
	void addTimeToLeaderboard(int time);
	void updateTopTimesFile();
	void resetTopTimesToDefaults();
	void draw(sf::RenderWindow& window) override;
};