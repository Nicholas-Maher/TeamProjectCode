#pragma once
#include "Screen.h"

class GameOverScreen : public Screen
{

private:
	Text m_MainText;

	Button m_RetryButton;
	Button m_MainMenuButton;

public:
	GameOverScreen();

	FloatRect getRetryButton() const;
	FloatRect getMainMenuButton() const;
	void setMainText(String text);

	void draw(sf::RenderWindow& window) override;
};