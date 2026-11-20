#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Screen heading text
    m_Title.spawn("The Forest has been felled!", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 150));

    // main text
    m_Title.spawn("-----------------", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 350));

    // Retry button
    m_RetryButton.spawn(Vector2f(m_Resolution.x / 2.0f, 500), Color(45, 110, 55), 0, "RETRY", Color::White);

    // Main Menu button
    m_MainMenuButton.spawn(Vector2f(m_Resolution.x / 2.0f, 620), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 740), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
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
    m_Title.draw(window);
    m_MainText.draw(window);
    m_RetryButton.draw(window);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}