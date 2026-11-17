#pragma once
#include <SFML/Graphics.hpp>
#include "Bar.h"

using namespace sf;

class Hud
{
private:
	Vector2u m_Resolution;
	Font m_Font;
	Text m_TimeText;
	Text m_LevelText;

	// Health bar
	Bar m_HealthBar;

	// Power meter
	Bar m_PowerBar;

public:
	Hud();
	Text getLevel();
	Text getTime();

	void setLevel(String text);
	void setTime(String text);

	void setHealthBar(int currentHealth, int maxHealth);
	void setPowerBar(int currentPower, int maxPower);

	void draw(sf::RenderWindow& window);
};