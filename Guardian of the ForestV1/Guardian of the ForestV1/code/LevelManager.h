#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class LevelManager
{
private:
	Vector2i m_LevelSize;
	Vector2f m_StartPosition;

	float m_TimeModifier = 1;
	float m_BaseTimeLimit = 0;

	int m_CurrentLevel = 0;
	// temporarily changed to 3 while we just have 3 levels
	const int NUM_LEVELS = 3;

public:

	// tiles size is 50x50 tile
	const int TILE_SIZE = 50;
	const int VERTS_IN_QUAD = 4;

	float getTimeLimit();

	Vector2f getStartPosition();

	int** nextLevel(VertexArray& rVaLevel);

	Vector2i getLevelSize();

	int getCurrentLevel();
	void setCurrentLevel(int level);

	int getNumLevels() const;

};
