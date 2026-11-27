#pragma once
#include "Screen.h"

class LevelCompleteScreen : public Screen
{

private:
	TextBlock m_TimeText;

	Button m_NextLevelButton;
	Button m_MainMenuButton;

public:
	LevelCompleteScreen();

	FloatRect getNextLevelButton() const;
	FloatRect getMainMenuButton() const;

	void setTitleText(String text);
	void setTimeText(String text);
	void draw(sf::RenderWindow& window) override;
};