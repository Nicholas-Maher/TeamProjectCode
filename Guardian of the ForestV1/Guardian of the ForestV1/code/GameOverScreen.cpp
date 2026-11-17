#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Screen heading text
    m_Title.setFont(m_Font);
    m_Title.setString("The Forest has been felled!");
    m_Title.setCharacterSize(100);
    m_Title.setFillColor(Color(46, 111, 64));

    FloatRect titleBounds = m_Title.getLocalBounds();
    m_Title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    m_Title.setPosition(960, 150);

    // main text
    m_MainText.setFont(m_Font);
    m_MainText.setString("----------------");
    m_MainText.setCharacterSize(100);
    m_MainText.setFillColor(Color(46, 111, 64));

    FloatRect mainTextBounds = m_MainText.getLocalBounds();
    m_MainText.setOrigin(mainTextBounds.left + mainTextBounds.width / 2.f, mainTextBounds.top + mainTextBounds.height / 2.f);
    m_MainText.setPosition(960, 350);

    // Retry button
    m_RetryButton.spawn(Vector2f(810, 500), Color(45, 110, 55), 0, "RETRY", Color::White);

    // Main Menu button
    m_MainMenuButton.spawn(Vector2f(810, 620), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(810, 740), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
}

FloatRect GameOverScreen::getRetryButton() const
{
    return m_RetryButton.getButton();
}

FloatRect GameOverScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getButton();
}

void GameOverScreen::setMainText(String text)
{
    m_MainText.setString(text);
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
    window.draw(m_Title);
    window.draw(m_MainText);
    m_RetryButton.draw(window);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}