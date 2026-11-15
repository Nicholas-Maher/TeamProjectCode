#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "LevelManager.h"
#include "Enemy.h"

#include "Screen.h"
#include "MainMenu.h"
#include "VictoryScreen.h"
#include "TopTimesScreen.h"

#include "HUD.h"

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

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 30;

	MainMenu m_MainMenu;
	VictoryScreen m_VictoryScreen;
	TopTimesScreen m_TopTimesScreen;

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

	/*Nicholas - adding a simple main menu to the game */
	bool m_Mainmenu = true;
	Font m_MenuFont;

	// How much time is left in the current level
	float m_TimeRemaining = 10;
	Time m_GameTimeTotal;

	// How much time has passed in the current level
	float m_LevelTimeElapsed = 0;

	// For tracking the total score and will be added to the leaderboard if the player completes the game and the score is fast enough
	float m_TotalTimeElapsed = 0;

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

	//Creating Enemy
	Enemy m_Enemy{ sf::Vector2f(500.f, 400.f) };

	bool hasGroundAhead(); // Function to check if there is ground ahead of the enemy


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

	// the game states - these help allow the game to switch between modes - Patrick
	enum class State { MAIN_MENU, PLAYING, TOP_TIMES, PAUSED, VICTORY, GAME_OVER };

	State state = State::MAIN_MENU;

	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};