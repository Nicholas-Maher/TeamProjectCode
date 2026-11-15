#include "VictoryScreen.h"

VictoryScreen::VictoryScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    /** Patrick - button based on Nicholas' main main button logic **/

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
    m_MainMenuButton.setSize(Vector2f(300, 80));
    m_MainMenuButton.setPosition(810, 500);
    m_MainMenuButton.setFillColor(Color(45, 110, 55));
    m_MainMenuButton.setOutlineColor(Color::White);

    // Main Menu text
    m_MainMenuText.setFont(m_Font);
    m_MainMenuText.setString("MAIN MENU");
    m_MainMenuText.setCharacterSize(30);
    m_MainMenuText.setFillColor(Color::White);

    FloatRect menuBounds = m_MainMenuText.getLocalBounds();
    m_MainMenuText.setOrigin(menuBounds.left + menuBounds.width / 2.f, menuBounds.top + menuBounds.height / 2.f);
    m_MainMenuText.setPosition(960, 540);

    // Quit button
    m_QuitButton.setSize(Vector2f(300, 80));
    m_QuitButton.setPosition(810, 620);
    m_QuitButton.setFillColor(Color(120, 45, 40));
    m_QuitButton.setOutlineColor(Color::White);
    m_QuitButton.setOutlineThickness(3);

    // Quit text
    m_QuitText.setFont(m_Font);
    m_QuitText.setString("QUIT GAME");
    m_QuitText.setCharacterSize(30);
    m_QuitText.setFillColor(Color::White);

    FloatRect quitBounds = m_QuitText.getLocalBounds();
    m_QuitText.setOrigin(quitBounds.left + quitBounds.width / 2.f, quitBounds.top + quitBounds.height / 2.f);
    m_QuitText.setPosition(960, 660);
}

FloatRect VictoryScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getGlobalBounds();
}

void VictoryScreen::setTimeText(String text)
{
    m_TimeText.setString(text);
}

void VictoryScreen::draw(sf::RenderWindow& window)
{
    window.draw(m_Title);
    window.draw(m_TimeText);
    window.draw(m_MainMenuButton);
    window.draw(m_MainMenuText);
    window.draw(m_QuitButton);
    window.draw(m_QuitText);
}