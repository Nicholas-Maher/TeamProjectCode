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
		}

        // Handle mouse clicks on the main menu
        if (state == State::MAIN_MENU && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Get the mouse position
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // Start Game Button
            if (m_MainMenu.getStartButton().contains((mousePosition.x), (mousePosition.y)))
            {
                m_TotalTimeElapsed = 0;
                m_LevelTimeElapsed = 0;
                // resets the player's health
                m_Player.setFullHealth(m_Player.getStartHealth());
                m_Player.setHealth(m_Player.getFullHealth());

                m_LM.setCurrentLevel(0); // resets the level to 0 so when load level is called, it increments it to 1
                //loadLevel();
                m_NewLevelRequired = true;

                state = State::PLAYING;
            }

            // Top Scores Button
            if (m_MainMenu.getTopTimesButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::TOP_TIMES;
            }
            // Quit the Game Button
            else if (m_MainMenu.getQuitButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Window.close();
            }
        }

        // Handle mouse clicks on the victory screen
        else if (state == State::VICTORY && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Get the mouse position
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // Main Menu Button
            if (m_VictoryScreen.getMainMenuButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::MAIN_MENU;
            }
            // Quit the Game Button
            else if (m_VictoryScreen.getQuitButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Window.close();
            }
        }

        // Handle mouse clicks on the game over screen
        else if (state == State::GAME_OVER && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Get the mouse position
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // retry Button
            if (m_GameOverScreen.getRetryButton().contains((mousePosition.x), (mousePosition.y)))
            {
                // resets the player's health
                m_Player.setFullHealth(m_Player.getStartHealth());
                m_Player.setHealth(m_Player.getFullHealth());

                // sets the current level to one less that current so when load level is called, it increments it to the level the player was just on
                m_LM.setCurrentLevel(m_LM.getCurrentLevel() - 1); 
                m_NewLevelRequired = true;
                state = State::PLAYING;
            }
            // Main Menu Button
            else if (m_GameOverScreen.getMainMenuButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::MAIN_MENU;
            }
            // Quit the Game Button
            else if (m_GameOverScreen.getQuitButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Window.close();
            }
        }

        // Handle mouse clicks on the top times screen
        else if (state == State::TOP_TIMES && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Get the mouse position
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // Main Menu Button
            if (m_TopTimesScreen.getMainMenuButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::MAIN_MENU;
            }
            // Reset times Button
            if (m_TopTimesScreen.getResetTimesButton().contains((mousePosition.x), (mousePosition.y)))
            {
                m_TopTimesScreen.resetTopTimesToDefaults();
            }
            // Quit the Game Button
            else if (m_TopTimesScreen.getQuitButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Window.close();
            }
        }
	}	

	// Handle input specific to the player
    if (state == State::PLAYING && m_Player.handleInput())
	{
		// Play a jump sound
		m_SM.playJump();
	}
}
