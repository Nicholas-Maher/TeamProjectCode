#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Bar
{
private:
	Font m_Font;

	// Health bar
	RectangleShape m_Bar;
	RectangleShape m_BarBackground;
	RectangleShape m_BarBorder;
	int m_StatWidth = 100;
	int m_Width = 100;
	int m_Height = 70;
	int m_BarBorderWidth = 10;

	// the full bar width is determined by the max value of the stat it represents (e.g. 100% player health) 
	// but this is what this multiplier is for
	int m_BarWidthMultiplier = 4;

	float xPos = 0;
	float yPos = 0;

public:
	Bar();

	void spawn(Color barColour, Color BGColour, Color borderColour, float xPosition, float yPosition, int statWidth, int width,
		int height, int borderWidth, int widthMultiplier);
	void setBar(int currentHealth, int maxHealth);
	void draw(sf::RenderWindow& window);
};