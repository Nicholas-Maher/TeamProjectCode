#pragma once
#include <SFML/Graphics.hpp>
#include "Button.h"
#include <sstream>

using namespace sf;

class Screen
{
protected:
	Font m_Font;
	Vector2f m_Resolution;

	Text m_Title;

	Button m_QuitButton;

public:
	Screen();

	FloatRect getQuitButton() const;

	// Draws the enemy on the window
	virtual void draw(sf::RenderWindow& window) = 0;
};