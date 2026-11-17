#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);
	
	// Update the shader parameters
	//////m_RippleShader.setUniform("uTime", m_GameTimeTotal.asSeconds()); // og had this

	// Switch to background view
	m_Window.setView(m_BGMainView);

	// Draw the background
	m_Window.draw(m_BackgroundSprite);

	// Draw the background, complete with shader effect
	////m_Window.draw(m_BackgroundSprite, &m_RippleShader); // og had this
	
	// Draw the main menu
	if (state == State::MAIN_MENU)
	{
		// Switch to HUD view for the menu
		m_Window.setView(m_HudView);

		// Draw the main menu - Patrick - made the main menu class and moved Nicholas's text and button creating and drawing logic into it
		m_MainMenu.draw(m_Window);

	}

	// Draw the victory screen
	if (state == State::VICTORY)
	{
		// Switch to HUD view for the menu
		m_Window.setView(m_HudView);

		m_VictoryScreen.draw(m_Window);
	}

	// Draw the victory screen
	if (state == State::GAME_OVER)
	{
		// Switch to HUD view for the menu
		m_Window.setView(m_HudView);

		m_GameOverScreen.draw(m_Window);
	}

	if (state == State::PLAYING)
	{
		// Switch to m_MainView
		m_Window.setView(m_MainView);

		// Draw the level
		m_Window.draw(m_VALevel, &m_TextureTiles);

		/***********************
		// Draw the LevelBorder
		m_Window.draw(m_LevelBorder);
		*//////////////////

		// Draw the player
		m_Window.draw(m_Player.getSprite());

		// Draw the enemy
		m_Enemy.draw(m_Window);

		// Draw the HUD
		m_Window.setView(m_HudView);
		m_Hud.draw(m_Window);

	}
	
	// Draw the top times screen
	if (state == State::TOP_TIMES)
	{
		// Switch to HUD view for the menu
		m_Window.setView(m_HudView);

		m_TopTimesScreen.draw(m_Window);
	}
	
	// Show everything we have just drawn
	m_Window.display();
}
