#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Hud
{
private:
	Vector2u m_Resolution;
	Font m_Font;
	Text m_TimeText;
	Text m_LevelText;

	// Health bar
	RectangleShape m_HealthBar;
	RectangleShape m_HealthBarBackground;
	RectangleShape m_HealthBarBorder;
	int m_DefaultWidth = 100;
	int m_Height = 70;
	int m_HealthBarBorderWidth = 10;
	int m_HealthBarWidthMultiplier = 4;

	float yPos = 80;

public:
	Hud();
	Text getLevel();
	Text getTime();

	void setLevel(String text);
	void setTime(String text);

	void setHealthBar(int currentHealth, int maxHealth);

	void draw(sf::RenderWindow& window);
};