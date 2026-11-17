#include "VictoryScreen.h"

VictoryScreen::VictoryScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Screen heading text
    m_Title.setFont(m_Font);
    m_Title.setString("You Won! You saved the Forest!");
    m_Title.setCharacterSize(100);
    m_Title.setFillColor(Color(46, 111, 64));

    FloatRect titleBounds = m_Title.getLocalBounds();
    m_Title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    m_Title.setPosition(960, 150);

    // time text
    m_TimeText.setFont(m_Font);
    m_TimeText.setString("--------------");
    m_TimeText.setCharacterSize(100);
    m_TimeText.setFillColor(Color(46, 111, 64));

    FloatRect timeBounds = m_TimeText.getLocalBounds();
    m_TimeText.setOrigin(timeBounds.left + timeBounds.width / 2.f, timeBounds.top + timeBounds.height / 2.f);
    m_TimeText.setPosition(960, 350);

    // Main Menu button
    m_MainMenuButton.spawn(Vector2f(810, 500), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(810, 620), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
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
    window.draw(m_Title);
    window.draw(m_TimeText);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}