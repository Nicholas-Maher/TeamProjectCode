
#include "Engine.h"

void Engine::draw()
{
    // Rub out the last frame
    m_Window.clear(Color::White);

    // Switch to background view
    m_Window.setView(m_BGMainView);

    // Draw the background
    m_Window.draw(m_BackgroundSprite);

    // Draw the main menu
    if (m_Mainmenu)
    {
        // Switch to HUD view for the menu
        m_Window.setView(m_HudView);

        // Game title
        Text title;
        title.setFont(m_MenuFont);
        title.setString("GUARDIAN OF THE FOREST");
        title.setCharacterSize(60);
        title.setFillColor(Color(220, 240, 180));

        FloatRect titleBounds = title.getLocalBounds();
        title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f );

        title.setPosition(960, 350);
        m_Window.draw(title);

        // Start Game button
        RectangleShape startButton(Vector2f(300, 80));
        startButton.setPosition(810, 500);
        startButton.setFillColor(Color(45, 110, 55));
        startButton.setOutlineColor(Color::White);
        m_Window.draw(startButton);

        // Start Game text
        Text startText;
        startText.setFont(m_MenuFont);
        startText.setString("START GAME");
        startText.setCharacterSize(30);
        startText.setFillColor(Color::White);

        FloatRect startBounds = startText.getLocalBounds();
        startText.setOrigin(startBounds.left + startBounds.width / 2.f, startBounds.top + startBounds.height / 2.f);

        startText.setPosition(960, 540);
        m_Window.draw(startText);

        // Quit button
        RectangleShape quitButton(Vector2f(300, 80));
        quitButton.setPosition(810, 620);
        quitButton.setFillColor(Color(120, 45, 40));
        quitButton.setOutlineColor(Color::White);
        quitButton.setOutlineThickness(3);
        m_Window.draw(quitButton);

        // Quit text
        Text quitText;
        quitText.setFont(m_MenuFont);
        quitText.setString("QUIT GAME");
        quitText.setCharacterSize(30);
        quitText.setFillColor(Color::White);

        FloatRect quitBounds = quitText.getLocalBounds();
        quitText.setOrigin(
            quitBounds.left + quitBounds.width / 2.f,
            quitBounds.top + quitBounds.height / 2.f
        );

        quitText.setPosition(960, 660);
        m_Window.draw(quitText);
    }
    else
    {
        // Switch to m_MainView
        m_Window.setView(m_MainView);

        // Draw the level
        m_Window.draw(m_VALevel, &m_TextureTiles);

        // Draw the LevelBorder
        m_Window.draw(m_LevelBorder);

        // Draw the player
        m_Window.draw(m_Player.getSprite());

        // Draw the HUD
        m_Window.setView(m_HudView);
        m_Window.draw(m_HealthBarBorder);
        m_Window.draw(m_HealthBarBackground);
        m_Window.draw(m_HealthBar);
    }

    // Show everything we have just drawn
    m_Window.display();
}
