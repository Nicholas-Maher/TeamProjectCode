#pragma once
#include "Screen.h"

class MainMenu : public Screen
{

private:
	TextBlock m_Title;

	Button m_StartButton;
	Button m_TopTimesButton;
	Button m_ControlsButton;

public:
	MainMenu();

	FloatRect getStartButton() const;
	FloatRect getControlsButton() const;
	FloatRect getTopTimesButton() const;

	void draw(sf::RenderWindow& window) override;
};