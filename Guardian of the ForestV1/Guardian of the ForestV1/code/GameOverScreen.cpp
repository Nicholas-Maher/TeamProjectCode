#include "GameOverScreen.h"

GameOverScreen::GameOverScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    /** Patrick - button based on Nicholas' main main button logic **/

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
    m_RetryButton.setSize(Vector2f(300, 80));
    m_RetryButton.setPosition(810, 500);
    m_RetryButton.setFillColor(Color(45, 110, 55));
    m_RetryButton.setOutlineColor(Color::White);

    // Retry text
    m_RetryText.setFont(m_Font);
    m_RetryText.setString("RETRY");
    m_RetryText.setCharacterSize(30);
    m_RetryText.setFillColor(Color::White);

    FloatRect retryBounds = m_RetryText.getLocalBounds();
    m_RetryText.setOrigin(retryBounds.left + retryBounds.width / 2.f, retryBounds.top + retryBounds.height / 2.f);
    m_RetryText.setPosition(960, 540);

    // Main Menu button
    m_MainMenuButton.setSize(Vector2f(300, 80));
    m_MainMenuButton.setPosition(810, 620);
    m_MainMenuButton.setFillColor(Color(45, 110, 55));
    m_MainMenuButton.setOutlineColor(Color::White);

    // Main Menu text
    m_MainMenuText.setFont(m_Font);
    m_MainMenuText.setString("MAIN MENU");
    m_MainMenuText.setCharacterSize(30);
    m_MainMenuText.setFillColor(Color::White);

    FloatRect menuBounds = m_MainMenuText.getLocalBounds();
    m_MainMenuText.setOrigin(menuBounds.left + menuBounds.width / 2.f, menuBounds.top + menuBounds.height / 2.f);
    m_MainMenuText.setPosition(960, 660);

    // Quit button
    m_QuitButton.setSize(Vector2f(300, 80));
    m_QuitButton.setPosition(810, 740);
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
    m_QuitText.setPosition(960, 780);
}

FloatRect GameOverScreen::getRetryButton() const
{
    return m_RetryButton.getGlobalBounds();
}

FloatRect GameOverScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getGlobalBounds();
}

void GameOverScreen::setMainText(String text)
{
    m_MainText.setString(text);
}

void GameOverScreen::draw(sf::RenderWindow& window)
{
    window.draw(m_Title);
    window.draw(m_MainText);
    window.draw(m_RetryButton);
    window.draw(m_RetryText);
    window.draw(m_MainMenuButton);
    window.draw(m_MainMenuText);
    window.draw(m_QuitButton);
    window.draw(m_QuitText);
}