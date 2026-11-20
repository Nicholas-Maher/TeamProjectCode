#pragma once
#include <SFML/Graphics.hpp>
#include "TextureHolder.h"
#include "Player.h"
#include "LevelManager.h"
#include "Enemy.h"
#include "SoundManager.h"
#include "ParticleSystem.h"
#include "Screen.h"
#include "MainMenu.h"
#include "ControlsScreen.h"
#include "VictoryScreen.h"
#include "GameOverScreen.h"
#include "TopTimesScreen.h"
#include "HUD.h"

#include "PowerOrb.h"
#include "UtilityFunctions.h"

using namespace sf;

class Engine
{
private:
	// The texture holder
	TextureHolder th;

	// create a particle system
	ParticleSystem m_PS;

	// Player and his friend, Bob
	Player m_Player;

	// A class to manage all the levels
	LevelManager m_LM;

	// Create a SoundManager
	SoundManager m_SM;

	// The Hud
	Hud m_Hud;
	int m_FramesSinceLastHUDUpdate = 0;
	int m_TargetFramesPerHUDUpdate = 250;

	MainMenu m_MainMenu;
	VictoryScreen m_VictoryScreen;
	TopTimesScreen m_TopTimesScreen;
	GameOverScreen m_GameOverScreen;
	ControlsScreen m_ControlsScreen;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 200; // was 300 in og game

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main View
	View m_MainView;

	// the view for the background
	View m_BGMainView;

	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	// Declare a shader for the background
	Shader m_RippleShader;

	// Is the game currently playing?
	bool m_Playing = false;

	// How much time has passed in the current level
	float m_LevelTimeElapsed = 0;
	Time m_GameTimeTotal;

	// For tracking the total score and will be added to the leaderboard if the player completes the game and the score is fast enough
	float m_TotalTimeElapsed = 0;

	// Is it time for a new/first level?
	bool m_NewLevelRequired = true;

	// The vertex array for the level design
	VertexArray m_VALevel;

	/*Nicholas -- Level Border*/
	//sf::RectangleShape m_LevelBorder;

	// The 2d array with the map for the level
	// A pointer to a pointer
	int** m_ArrayLevel = NULL;

	// Texture for the background and the level tiles
	Texture m_TextureTiles;

	//Creating Enemy
	Enemy m_Enemy{ sf::Vector2f(500.f, 400.f) };

	// Making a single power orb for testing
	PowerOrb m_PowerOrb;

	// has the button to set the key for a given button been clicked on in the controls screen and if true a key can be set
	bool settingJump = false;
	bool settingMoveLeft = false;
	bool settingMoveRight = false;
	bool settingRun = false;
	
	bool hasGroundAhead(); // Function to check if there is ground ahead of the enemy
	
	
	// Private functions for internal use only
	void handleInput();
	void update(float dtAsSeconds);
	void draw();

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(Player& character);
	
	// Make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

	// A vector of Vector2f for the fire emiiter locations
	vector <Vector2f> m_FireEmitters;
	
public:

	// the game states - these help allow the game to switch between modes - Patrick
	enum class State { MAIN_MENU, PLAYING, CONTROLS, TOP_TIMES, PAUSED, VICTORY, GAME_OVER };
	
	State state = State::MAIN_MENU;

	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};