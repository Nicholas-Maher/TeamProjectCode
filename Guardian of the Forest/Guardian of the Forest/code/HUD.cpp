#include "Hud.h"

Hud::Hud()
{
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;

	// Load the font
	m_Font.loadFromFile("fonts/Cinzel.ttf");

	// Time
	m_TimeText.setFont(m_Font);
	m_TimeText.setCharacterSize(75);
	m_TimeText.setFillColor(Color::White);
	m_TimeText.setPosition(m_Resolution.x - 200, 25);
	m_TimeText.setString("------");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(Color::White);
	m_LevelText.setPosition(25, 25);
	m_LevelText.setString("1");

	// health bar
	m_HealthBar.spawn(Color::Green, Color::Red, Color(17, 17, 132) /*dark blue*/, (m_Resolution.x / 2) - 300, 80, 100, 100, 50, 10, 4);

	// power bar
	m_PowerBar.spawn(Color::Red, Color(17, 17, 132),  Color(17, 17, 132) /*dark blue*/, (m_Resolution.x / 2) + 300, 80, 0, 100, 50, 10, 4);
}


Text Hud::getLevel()
{
	return m_LevelText;
}

Text Hud::getTime()
{
	return m_TimeText;
}

void Hud::setLevel(String text)
{
	m_LevelText.setString(text);
}

void Hud::setTime(String text)
{
	m_TimeText.setString(text);
}

void Hud::setHealthBar(int currentHealth, int maxHealth)
{
	m_HealthBar.setBar(currentHealth, maxHealth);
}

void Hud::setPowerBar(int currentPower, int maxPower)
{
	m_PowerBar.setBar(currentPower, maxPower);
}

void Hud::draw(sf::RenderWindow& window)
{
	m_HealthBar.draw(window);
	m_PowerBar.draw(window);

	window.draw(m_TimeText);
	window.draw(m_LevelText);
}