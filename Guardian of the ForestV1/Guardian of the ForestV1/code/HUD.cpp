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
	m_TimeText.setPosition(m_Resolution.x - 500, 25);
	m_TimeText.setString("------");

	// Level
	m_LevelText.setFont(m_Font);
	m_LevelText.setCharacterSize(75);
	m_LevelText.setFillColor(Color::White);
	m_LevelText.setPosition(25, 25);
	m_LevelText.setString("1");

	// Setting up the background for the healthbar with a default width
	m_HealthBarBackground.setFillColor(Color::Red);
	m_HealthBarBackground.setSize(Vector2f(m_DefaultWidth * m_HealthBarWidthMultiplier, m_Height));
	// sets the origin to the centre of the rectangle and uses that point for positioning
	FloatRect healthBarBounds = m_HealthBarBackground.getLocalBounds();
	m_HealthBarBackground.setOrigin(healthBarBounds.left + healthBarBounds.width / 2.f, healthBarBounds.top + healthBarBounds.height / 2.f);
	m_HealthBarBackground.setPosition((m_Resolution.x / 2), yPos);

	// Setting up the dynamic part of the healthbar with a default width
	m_HealthBar.setFillColor(Color::Green);
	m_HealthBar.setSize(Vector2f(m_DefaultWidth * m_HealthBarWidthMultiplier, m_Height));
	// uses the same bounds as the healthbar background so its left side always aligns with the background's left side so the bar drains from the right
	m_HealthBar.setOrigin(healthBarBounds.left + healthBarBounds.width / 2.f, healthBarBounds.top + healthBarBounds.height / 2.f);
	m_HealthBar.setPosition((m_Resolution.x / 2), yPos);


	// Setting up the border for the healthbar with a default width
	m_HealthBarBorder.setFillColor(Color(17, 17, 132)); // dark blue
	m_HealthBarBorder.setSize(Vector2f((m_DefaultWidth * m_HealthBarWidthMultiplier) + m_HealthBarBorderWidth * 2, m_Height + (m_HealthBarBorderWidth * 2)));
	healthBarBounds = m_HealthBarBorder.getLocalBounds();
	m_HealthBarBorder.setOrigin(healthBarBounds.left + healthBarBounds.width / 2.f, healthBarBounds.top + healthBarBounds.height / 2.f);
	m_HealthBarBorder.setPosition((m_Resolution.x / 2), yPos);

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
	m_HealthBarBackground.setSize(Vector2f(maxHealth * m_HealthBarWidthMultiplier, m_Height));
	// sets the origin to the centre of the rectangle and uses that point for positioning
	FloatRect healthBarBounds = m_HealthBarBackground.getLocalBounds();
	m_HealthBarBackground.setOrigin(healthBarBounds.left + healthBarBounds.width / 2.f, healthBarBounds.top + healthBarBounds.height / 2.f);
	m_HealthBarBackground.setPosition((m_Resolution.x / 2), yPos);

	m_HealthBar.setSize(Vector2f(currentHealth * m_HealthBarWidthMultiplier, m_Height));
	// uses the same bounds as the healthbar background so its left side always aligns with the background's left side so the bar drains from right to left
	m_HealthBar.setOrigin(healthBarBounds.left + healthBarBounds.width / 2.f, healthBarBounds.top + healthBarBounds.height / 2.f);
	m_HealthBar.setPosition((m_Resolution.x / 2), yPos);

	m_HealthBarBorder.setSize(Vector2f((maxHealth * m_HealthBarWidthMultiplier) + m_HealthBarBorderWidth * 2, m_Height + (m_HealthBarBorderWidth * 2)));
	healthBarBounds = m_HealthBarBorder.getLocalBounds();
	m_HealthBarBorder.setOrigin(healthBarBounds.left + healthBarBounds.width / 2.f, healthBarBounds.top + healthBarBounds.height / 2.f);
	m_HealthBarBorder.setPosition((m_Resolution.x / 2), yPos);
}

void Hud::draw(sf::RenderWindow& window)
{
	window.draw(m_HealthBarBorder);
	window.draw(m_HealthBarBackground);
	window.draw(m_HealthBar);

	window.draw(m_TimeText);
	window.draw(m_LevelText);
}