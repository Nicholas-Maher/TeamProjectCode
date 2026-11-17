#pragma once
#include "Screen.h"

class GameOverScreen : public Screen
{

private:
	Text m_Title;
	Text m_MainText;

	RectangleShape m_RetryButton;
	Text m_RetryText;

	RectangleShape m_MainMenuButton;
	Text m_MainMenuText;

public:
	GameOverScreen();

	FloatRect getRetryButton() const;
	FloatRect getMainMenuButton() const;
	void setMainText(String text);

	void draw(sf::RenderWindow& window) override;
};