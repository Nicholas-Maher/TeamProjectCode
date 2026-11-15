#pragma once
#include "Screen.h"

class MainMenu : public Screen
{

private:
	Text title;

	RectangleShape m_StartButton;
	Text m_StartText;

	RectangleShape m_TopTimesButton;
	Text m_TopTimesText;

public:
	MainMenu();

	FloatRect getStartButton() const;
	FloatRect getTopTimesButton() const;

	void draw(sf::RenderWindow& window) override;
};