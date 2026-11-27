#include "Engine.h"
#include <Vector>
#include <iostream>

void Engine::handleInput()
{
	Event event;

    while (m_Window.pollEvent(event))
    {
        if (event.type == Event::KeyPressed)
        {
            if (event.key.code == Keyboard::Escape)
            {
                if (state == State::PLAYING)
                {
                    state = State::PAUSED;
                }
                else if (state == State::PAUSED)
                {
                    state = State::PLAYING;
                }
            }
        }
        // for handling when the player has pressed a button to set a key bind for an action in the controls screen
        if (event.type == Event::KeyPressed)
        {
            if (state == State::CONTROLS)
            {
                if (settingJump)
                {
                    m_Player.setJumpButton(event.key.code);
                    //string key = Keyboard::getDescription(event.key.scancode).toAnsiString();
                    //cout << key << endl;
                    m_ControlsScreen.setJumpButtonText(Keyboard::getDescription(event.key.scancode));
                    settingJump = false;
                }
                else if (settingMoveLeft)
                {
                    m_Player.setMoveLeftButton(event.key.code);
                    m_ControlsScreen.setMoveLeftButtonText(Keyboard::getDescription(event.key.scancode));
                    settingMoveLeft = false;
                }
                else if (settingMoveRight)
                {
                    m_Player.setMoveRightButton(event.key.code);
                    m_ControlsScreen.setMoveRightButtonText(Keyboard::getDescription(event.key.scancode));
                    settingMoveRight = false;
                }
                else if (settingRun)
                {
                    m_Player.setRunButton(event.key.code);
                    m_ControlsScreen.setRunButtonText(Keyboard::getDescription(event.key.scancode));
                    settingRun = false;
                }
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

                // resets the player's power
                m_Player.setFullPower(m_Player.getStartFullPower());
                m_Player.setPower(m_Player.getStartPower());

                m_LM.setCurrentLevel(0); // resets the level to 0 so when load level is called, it increments it to 1
                //loadLevel();
                m_NewLevelRequired = true;

                state = State::PLAYING;
            }
            // Control menu Button
            else if (m_MainMenu.getControlsButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::CONTROLS;
            }
            // Top Scores Button
            else if (m_MainMenu.getTopTimesButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::TOP_TIMES;
            }
            // Quit the Game Button
            else if (m_MainMenu.getQuitButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Window.close();
            }
        }

        else if (state == State::PAUSED && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // Resume button
            if (m_PauseMenu.getResumeButton().contains(mousePosition.x, mousePosition.y))
            {
                state = State::PLAYING;
            }
            // Main Menu button
            else if (m_PauseMenu.getMainMenuButton().contains(mousePosition.x, mousePosition.y))
            {
                state = State::MAIN_MENU;
            }
            // Quit Game button
            else if (m_PauseMenu.getQuitButton().contains(mousePosition.x, static_cast<float>(mousePosition.y)))
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

        // Handle mouse clicks on the controls screen
        else if (state == State::CONTROLS && event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left)
        {
            // Get the mouse position
            Vector2i mousePosition(event.mouseButton.x, event.mouseButton.y);

            // set jump Button
            if (m_ControlsScreen.getJumpButton().contains((mousePosition.x), (mousePosition.y)))
            {
                settingJump = true;
                settingMoveLeft = false;
                settingMoveRight = false;
                settingRun = false;
                m_ControlsScreen.setJumpButtonText("Enter key...");
            }
            // set left Button
            else if (m_ControlsScreen.getMoveLeftButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                settingJump = false;
                settingMoveLeft = true;
                settingMoveRight = false;
                settingRun = false;
                m_ControlsScreen.setMoveLeftButtonText("Enter key...");
            }

            // set right Button
            else if (m_ControlsScreen.getMoveRightButton().contains((mousePosition.x), (mousePosition.y)))
            {
                settingJump = false;
                settingMoveLeft = false;
                settingMoveRight = true;
                settingRun = false;
                m_ControlsScreen.setMoveRightButtonText("Enter key...");
            }
            // set run Button
            else if (m_ControlsScreen.getRunButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                settingJump = false;
                settingMoveLeft = false;
                settingMoveRight = false;
                settingRun = true;
                m_ControlsScreen.setRunButtonText("Enter key...");
            }
            // set reset Button
            else if (m_ControlsScreen.getResetButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
            {
                m_Player.restoreDefaultButtons();
                // how to get the scan code from a key - https://www.sfml-dev.org/documentation/3.1.0/namespacesf_1_1Keyboard.html#a765ce72191e25b42281063405c40b4b8
                m_ControlsScreen.setJumpButtonText(Keyboard::getDescription(Keyboard::delocalize(m_Player.getJumpButton())));
                m_ControlsScreen.setMoveLeftButtonText(Keyboard::getDescription(Keyboard::delocalize(m_Player.getMoveLeftButton())));
                m_ControlsScreen.setMoveRightButtonText(Keyboard::getDescription(Keyboard::delocalize(m_Player.getMoveRightButton())));
                m_ControlsScreen.setRunButtonText(Keyboard::getDescription(Keyboard::delocalize(m_Player.getRunButton())));
            }
            // Main Menu Button
            else if (m_ControlsScreen.getMainMenuButton().contains((mousePosition.x), (mousePosition.y)))
            {
                state = State::MAIN_MENU;
            }
            // Quit the Game Button
            else if (m_ControlsScreen.getQuitButton().contains((mousePosition.x), static_cast<float>(mousePosition.y)))
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
                m_Player.setHealth(m_Player.getFullHealth());

                // resets the player's power
                m_Player.setPower(m_Player.getStartPower());

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
