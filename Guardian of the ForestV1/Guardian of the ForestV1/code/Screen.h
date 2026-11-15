#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace sf;

class Screen
{
protected:
	Font m_Font;
	Vector2f m_Resolution;

	RectangleShape m_QuitButton;
	Text m_QuitText;

public:
	Screen();

	FloatRect getQuitButton() const;

	// Draws the enemy on the window
	virtual void draw(sf::RenderWindow& window) = 0;
};