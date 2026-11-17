#include "Engine.h"

Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;

	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Guardian of the Forest", Style::Fullscreen);
	//m_Window.setFramerateLimit(60); // the cause of the character jitters!!!!!!!!!!

	/*
	/*Nicholas -- adding Font to the main Menu*/
	//m_MenuFont.loadFromFile("fonts/Cinzel.ttf");
	
	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_MainView.setCenter(resolution.x / 2.f, resolution.y / 2.f);

	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		// Time to get a new PC
		m_Window.close();
	}
	else
	{
		// Load two shaders (1 vertex, 1 fragment)
		m_RippleShader.loadFromFile("shaders/vertShader.vert",
			"shaders/rippleShader.frag");
	}

	m_BackgroundTexture = TextureHolder::GetTexture(
		"graphics/background.png");

	// Associate the sprite with the texture
	m_BackgroundSprite.setTexture(m_BackgroundTexture);


	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture(
		"graphics/tiles_sheet.png");

	// Initialize the particle system
	m_PS.init(1000);

}// End Engine constructor

void Engine::run()
{
	// Timing 	
	Clock clock;

	while (m_Window.isOpen())
	{
		Time dt = clock.restart();
		// Update the total game time

		m_GameTimeTotal += dt;

		// Make a decimal fraction from the delta time
		float dtAsSeconds = dt.asSeconds();

		/********************init();*/
		handleInput();
		update(dtAsSeconds);
		draw();
	}
}

// Function to check if there is ground for the enemy
bool Engine::hasGroundAhead()
{
	// Get the enemy's current position
	sf::Vector2f enemyPos = m_Enemy.getPosition();

	float checkX;

	// Determine the direction the enemy is moving and set the checkX accordingly
	if (m_Enemy.getSpeed() > 0)
	{
		checkX = enemyPos.x + 51.f; // Moving right

	}
	// If the enemy is moving left, check the tile to the left of the enemy
	else
	{
		checkX = enemyPos.x - 1.f; // Moving left
	}

	float checkY = enemyPos.y + 101.f; // Check below the enemy

	// Convert the world coordinates to tile coordinates
	int tileX = static_cast<int>(checkX / TILE_SIZE);
	int tileY = static_cast<int>(checkY / TILE_SIZE);

	if (tileX < 0 || tileX >= m_LM.getLevelSize().x || tileY < 0 || tileY >= m_LM.getLevelSize().y)
	{
		return false; // Out of bounds, treat as no ground
	}

	return m_ArrayLevel[tileY][tileX] == 1; // Only tile type 1 is ground
}