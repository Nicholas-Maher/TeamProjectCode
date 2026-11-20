#include "PauseMenu.h"

PauseMenu::PauseMenu()
{
    // Load font
    m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Pause title
    m_Title.setFont(m_Font);
    m_Title.setString("PAUSED");
    m_Title.setCharacterSize(100);
    m_Title.setFillColor(Color::Red);

    FloatRect titleBounds = m_Title.getLocalBounds();

    m_Title.setOrigin(
        titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f
    );

    m_Title.setPosition(m_Resolution.x / 2.0f, 350);

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
    window.draw(m_Title);

    m_ResumeButton.draw(window);
    m_MainMenuButton.draw(window);
    m_QuitButton.draw(window);
}