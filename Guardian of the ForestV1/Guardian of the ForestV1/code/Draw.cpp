#include "Engine.h"

void Engine::draw()
{
	// Rub out the last frame
	m_Window.clear(Color::White);

	// Switch to background view
	m_Window.setView(m_BGMainView);
	// Draw the background
	m_Window.draw(m_BackgroundSprite);
	// Switch to m_MainView
	m_Window.setView(m_MainView);

	// Draw the Level
	m_Window.draw(m_VALevel, &m_TextureTiles);

	/*Nicholas Drwing the LevelBorder*/
	m_Window.draw(m_LevelBorder);

	// Draw the player
	m_Window.draw(m_Player.getSprite());

	// Draw the enemy
	m_Enemy.draw(m_Window);

	// Draw the HUD
	// Switch to m_HudView
	m_Window.setView(m_HudView);
	m_Window.draw(m_HealthBarBorder);
	m_Window.draw(m_HealthBarBackground);
	m_Window.draw(m_HealthBar);
	
	// Show everything we have just drawn
	m_Window.display();
}