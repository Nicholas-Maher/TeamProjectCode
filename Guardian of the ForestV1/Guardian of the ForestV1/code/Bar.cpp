#include "Bar.h"

Bar::Bar()
{
	// Load the font
	m_Font.loadFromFile("fonts/Cinzel.ttf");
}

void Bar::spawn(Color mainColour, Color BGColour, Color borderColour, float xPosition, float yPosition, int statWidth, int width,
	int height, int borderWidth, int widthMultiplier)
{
	xPos = xPosition;
	yPos = yPosition;
	m_StatWidth = statWidth;
	m_Width = width;
	m_Height = height;
	m_BarBorderWidth = borderWidth;

	// the full bar width is determined by the max value of the stat it represents (e.g. 100% player health) 
	// but this is what this multiplier is for
	m_BarWidthMultiplier = widthMultiplier;

	/******* bar initialisation *******/
	

	// Setting up the background for the bar with a default width
	m_BarBackground.setFillColor(BGColour);
	m_BarBackground.setSize(Vector2f(m_Width * m_BarWidthMultiplier, m_Height));
	// sets the origin to the centre of the rectangle and uses that point for positioning
	FloatRect barBounds = m_BarBackground.getLocalBounds();
	m_BarBackground.setOrigin(barBounds.left + barBounds.width / 2.f, barBounds.top + barBounds.height / 2.f);
	m_BarBackground.setPosition(xPos, yPos);

	// Setting up the dynamic part of the bar with a default width
	m_Bar.setFillColor(mainColour);
	m_Bar.setSize(Vector2f(m_StatWidth * m_BarWidthMultiplier, m_Height));
	// uses the same bounds as the bar background so its left side always aligns with the background's left side so the bar drains from the right
	m_Bar.setOrigin(barBounds.left + barBounds.width / 2.f, barBounds.top + barBounds.height / 2.f);
	m_Bar.setPosition(xPos, yPos);


	// Setting up the border for the bar with a default width
	m_BarBorder.setFillColor(Color(17, 17, 132)); // dark blue
	m_BarBorder.setSize(Vector2f((m_Width * m_BarWidthMultiplier) + m_BarBorderWidth * 2, m_Height + (m_BarBorderWidth * 2)));
	barBounds = m_BarBorder.getLocalBounds();
	m_BarBorder.setOrigin(barBounds.left + barBounds.width / 2.f, barBounds.top + barBounds.height / 2.f);
	m_BarBorder.setPosition(xPos, yPos);
	/******* End of bar initialisation *******/
}

void Bar::setBar(int currentHealth, int maxHealth)
{
	m_BarBackground.setSize(Vector2f(maxHealth * m_BarWidthMultiplier, m_Height));
	// sets the origin to the centre of the rectangle and uses that point for positioning
	FloatRect barBounds = m_BarBackground.getLocalBounds();
	m_BarBackground.setOrigin(barBounds.left + barBounds.width / 2.f, barBounds.top + barBounds.height / 2.f);
	m_BarBackground.setPosition(xPos, yPos);

	m_Bar.setSize(Vector2f(currentHealth * m_BarWidthMultiplier, m_Height));
	// uses the same bounds as the bar background so its left side always aligns with the background's left side so the bar always starts at the left side of the background bar
	m_Bar.setOrigin(barBounds.left + barBounds.width / 2.f, barBounds.top + barBounds.height / 2.f);
	m_Bar.setPosition(xPos, yPos);

	m_BarBorder.setSize(Vector2f((maxHealth * m_BarWidthMultiplier) + m_BarBorderWidth * 2, m_Height + (m_BarBorderWidth * 2)));
	barBounds = m_BarBorder.getLocalBounds();
	m_BarBorder.setOrigin(barBounds.left + barBounds.width / 2.f, barBounds.top + barBounds.height / 2.f);
	m_BarBorder.setPosition(xPos, yPos);
}

void Bar::draw(sf::RenderWindow& window)
{
	window.draw(m_BarBorder);
	window.draw(m_BarBackground);
	window.draw(m_Bar);

}