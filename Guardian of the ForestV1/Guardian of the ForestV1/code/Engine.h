#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "LevelManager.h"
#include "Enemy.h"

using namespace sf;

class Engine
{
private:
	// The texture holder
	TextureHolder th;

	// The player
	Player m_Player;

	// A class to manage all the levels
	LevelManager m_LM;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down - Change the gravity for the player
	const int GRAVITY = 200;

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main Views
	View m_MainView;
	View m_BGMainView;
	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;

	// Is the game currently playing?
	bool m_Playing = false;

	// How much time is left in the current level

	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;



	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VALevel;

	/*Nicholas -- Level Border*/
	sf::RectangleShape m_LevelBorder;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;

	// Health bar
	RectangleShape m_HealthBar;
	RectangleShape m_HealthBarBackground;
	RectangleShape m_HealthBarBorder;
	int m_HealthBarBorderWidth = 20;
	int m_HealthBarWidthMultiplier = 4;

	//Creating Enemy
	Enemy m_Enemy{ sf::Vector2f(500.f, 400.f) };


	// Private functions for internal use only
	void init();
	void handleInput();
	void update(float dtAsSeconds);
	void draw();

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(Player& character);

public:
	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};