#pragma once
#include "Screen.h"

class MainMenu : public Screen
{

private:
	Text m_Title;

	Button m_StartButton;
	Button m_TopTimesButton;

public:
	MainMenu();

	FloatRect getStartButton() const;
	FloatRect getTopTimesButton() const;

	void draw(sf::RenderWindow& window) override;
};