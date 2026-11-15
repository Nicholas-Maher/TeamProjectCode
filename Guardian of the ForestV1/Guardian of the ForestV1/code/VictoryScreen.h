#pragma once
#include "Screen.h"

class VictoryScreen : public Screen
{

private:
	Text m_Title;

	Text m_TimeText;

	RectangleShape m_MainMenuButton;
	Text m_MainMenuText;

public:
	VictoryScreen();

	FloatRect getMainMenuButton() const;

	void setTimeText(String text);
	void draw(sf::RenderWindow& window) override;
};