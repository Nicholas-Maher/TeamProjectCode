#include "VictoryScreen.h"

VictoryScreen::VictoryScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Screen heading text
    m_Title.spawn("You Won! You saved the Forest!", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 150));

    // time text
    m_TimeText.spawn("", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 350));

    // Main Menu button
    m_MainMenuButton.spawn(Vector2f(m_Resolution.x / 2.0f, 500), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 620), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
}

FloatRect VictoryScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getButton();
}

void VictoryScreen::setTimeText(String text)
{
    m_TimeText.setString(text);
}

void VictoryScreen::draw(sf::RenderWindow& window)
{
    m_Title.draw(window);
    m_TimeText.draw(window);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}