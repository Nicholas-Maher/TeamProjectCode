#include "LevelCompleteScreen.h"

/// <summary>
/// This screen appears upon completing levels 1 and 2
/// </summary>
LevelCompleteScreen::LevelCompleteScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Screen heading text
    m_Title.spawn("You Won! You saved the Forest!", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 150));

    // time text
    m_TimeText.spawn("", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 350));

    // Next Level button
    m_NextLevelButton.spawn(Vector2f(m_Resolution.x / 2.0f, 500), Color(45, 110, 55), 0, "NEXT LEVEL", Color::White);

    // Main Menu button
    m_MainMenuButton.spawn(Vector2f(m_Resolution.x / 2.0f, 620), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 740), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
}

FloatRect LevelCompleteScreen::getNextLevelButton() const
{
    return m_NextLevelButton.getButton();
}

FloatRect LevelCompleteScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getButton();
}

void LevelCompleteScreen::setTitleText(String text)
{
    m_Title.setString(text);
}

void LevelCompleteScreen::setTimeText(String text)
{
    m_TimeText.setString(text);
}

void LevelCompleteScreen::draw(sf::RenderWindow& window)
{
    m_Title.draw(window);
    m_TimeText.draw(window);
    m_NextLevelButton.draw(window);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}