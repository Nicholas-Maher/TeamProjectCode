#pragma once
#include "Screen.h"

class VictoryScreen : public Screen
{

private:
	TextBlock m_TimeText;

	Button m_MainMenuButton;

public:
	VictoryScreen();

	FloatRect getMainMenuButton() const;

	void setTimeText(String text);
	void draw(sf::RenderWindow& window) override;
};