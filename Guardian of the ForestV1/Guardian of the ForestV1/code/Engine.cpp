#include "Engine.h"


Engine::Engine()
{
	// Get the screen resolution and create an SFML window and View
	Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

	//resolution.x = 1920;
	//resolution.y = 1080;

	m_Window.create(VideoMode(resolution.x, resolution.y), "Guardian of the Forest", Style::Fullscreen);

	m_Window.setFramerateLimit(60);

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
	m_BackgroundTexture = TextureHolder::GetTexture("graphics/background.png");

	// Associate the sprite with the texture
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