
#include "Engine.h"
#include <Vector>

void Engine::handleInput()
{
    Event event;

    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            // Handle the player quitting
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }

            // Handle the player starting the game
            if (Keyboard::isKeyPressed(Keyboard::Return))
            {
                if (m_Mainmenu)
                {
                    if (m_NewLevelRequired)
                    {
                        loadLevel();
                    }

                    m_Mainmenu = false;
                }

                m_Playing = true;
            }
        }

        // Handle mouse clicks on the main menu
        if (m_Mainmenu &&event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Get the mouse position
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // Start Game Button
            if (FloatRect(810, 500, 300, 80).contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                if (m_NewLevelRequired)
                {
                    loadLevel();
                }

                m_Mainmenu = false;
                m_Playing = true;
            }
            // Quit the Game Button
            else if (FloatRect(810, 620, 300, 80).contains(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Window.close();
            }
        }
    }

    // Handle input specific to the player
    if (!m_Mainmenu && m_Player.handleInput())
    {
        // Play a jump sound
    }
}
