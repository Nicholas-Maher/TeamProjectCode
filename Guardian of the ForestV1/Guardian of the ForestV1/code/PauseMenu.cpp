#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
    // Load font
    m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Pause title
    m_Title.spawn("PAUSED", 100, Color::Red, Vector2f(m_Resolution.x / 2.0f, 350));

    // Resume button
    m_ResumeButton.spawn(
        Vector2f(m_Resolution.x / 2.0f, 500),
        Color(45, 110, 55), 0, "RESUME", Color::White
    );

    // Main Menu button
    m_MainMenuButton.spawn(
        Vector2f(m_Resolution.x / 2.0f, 620),
        Color(45, 110, 55), 0, "MAIN MENU", Color::White
    );

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 740), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
}

FloatRect PauseMenu::getResumeButton() const
{
    return m_ResumeButton.getButton();
}

FloatRect PauseMenu::getMainMenuButton() const
{
    return m_MainMenuButton.getButton();
}

void PauseMenu::draw(sf::RenderWindow& window)
{
    m_Title.draw(window);
    m_ResumeButton.draw(window);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}