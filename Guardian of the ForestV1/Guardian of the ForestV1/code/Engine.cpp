#include "Engine.h"


Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View resolution.x = 1920 and  resolution.y = 1080;
	Vector2f resolution;
	resolution.x = 1920;
	resolution.y = 1080;
	m_Window.create(VideoMode(resolution.x, resolution.y), "Guardian of the Forest", Style::Fullscreen);
	m_Window.setFramerateLimit(60);

	/*Nicholas -- adding Font to the main Menu*/
	m_MenuFont.loadFromFile("fonts/Cinzel.ttf");

	// Initialize the full screen view
	m_MainView.setSize(resolution);
	m_MainView.setCenter(resolution.x / 2.f, resolution.y / 2.f);

	m_HudView.reset(FloatRect(0, 0, resolution.x, resolution.y));

	// Inititialize the background view
	m_BGMainView.setSize(resolution);
	m_BGMainView.setCenter(resolution.x / 2.f, resolution.y / 2.f);

	// Can this graphics card use shaders?
	if (!sf::Shader::isAvailable())
	{
		m_Window.close();
	}
}

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

		init();
		handleInput();
		update(dtAsSeconds);
		draw();
	}
}

void Engine::init()
{
	// Associate the sprite with the texture
	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	// Load the texture for the background vertex array
	m_TextureTiles = TextureHolder::GetTexture("graphics/tiles_sheet.png");

	// Setting up the background for the healthbar
	m_HealthBarBackground.setFillColor(Color::Red);
	m_HealthBarBackground.setPosition(55, 55);
	m_HealthBarBackground.setSize(Vector2f(m_Player.getFullHealth() * m_HealthBarWidthMultiplier, 70));

	// Setting up the dynamic part of the healthbar
	m_HealthBar.setFillColor(Color::Green);
	m_HealthBar.setPosition(55, 55);
	m_HealthBar.setSize(Vector2f(m_Player.getHealth() * m_HealthBarWidthMultiplier, 70));

	// Setting up the border for the healthbar
	m_HealthBarBorder.setFillColor(Color(139, 69, 19)); // light brown
	m_HealthBarBorder.setPosition(55 - m_HealthBarBorderWidth, 55 - m_HealthBarBorderWidth);
	m_HealthBarBorder.setSize(Vector2f((m_Player.getFullHealth() * m_HealthBarWidthMultiplier) +
		m_HealthBarBorderWidth * 2, 70 + (m_HealthBarBorderWidth * 2)));
}

// Function to check if there is ground for the enemy
bool Engine::hasGroundAhead()
{
	// Get the enemy's current position
	sf::Vector2f enemyPos = m_Enemy.getPosition();

	float checkX;

	// Determine the direction the enemy moving
	if (m_Enemy.getMovementDirection() > 0)
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