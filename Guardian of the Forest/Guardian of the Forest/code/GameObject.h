#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
protected:
	Sprite m_Sprite;

	// holds position of the game actor	
	Vector2f m_Position;

public:

	Sprite getSprite();

	FloatRect getPosition();

	// virtual destructor
	virtual ~GameObject();

};