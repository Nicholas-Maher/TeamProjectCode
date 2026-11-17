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
#include "VictoryScreen.h"
#include "TopTimesScreen.h"

#include "HUD.h"

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
	int m_TargetFramesPerHUDUpdate = 500;

	MainMenu m_MainMenu;
	VictoryScreen m_VictoryScreen;
	TopTimesScreen m_TopTimesScreen;

	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	// The force pushing the characters down
	const int GRAVITY = 200; // was 300 in og game

	// A regular RenderWindow
	RenderWindow m_Window;

	// The main Views
	View m_MainView;
	/////View m_LeftView;
	/////View m_RightView;

	// Three views for the background
	View m_BGMainView;
	/////View m_BGLeftView;
	/////View m_BGRightView;

	View m_HudView;

	// Declare a sprite and a Texture for the background
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	// Declare a shader for the background
	Shader m_RippleShader;

	// Is the game currently playing?
	bool m_Playing = false;

	// Is character 1 or 2 the current focus?
	/////bool m_Character1 = true;

	// Start in full screen mode
	//////bool m_SplitScreen = false;

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
	void handleInput();
	void update(float dtAsSeconds);
	void draw();	

	// Load a new level
	void loadLevel();

	// Run will call all the private functions
	bool detectCollisions(Player& character); // was PlayableCharacter in og
	
	// Make a vector of the best places to emit sounds from
	void populateEmitters(vector <Vector2f>& vSoundEmitters,
		int** arrayLevel);

	// A vector of Vector2f for the fire emiiter locations
	vector <Vector2f> m_FireEmitters;
	
public:

	// the game states - these help allow the game to switch between modes - Patrick
	enum class State { MAIN_MENU, PLAYING, TOP_TIMES, PAUSED, VICTORY, GAME_OVER };
	
	State state = State::MAIN_MENU;

	// The Engine constructor
	Engine();

	// Run will call all the private functions
	void run();

};