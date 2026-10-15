#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class PlayableCharacter
{
protected:
	// sprite sheet
	Sprite m_Sprite;
	Sprite m_SpriteSheet;

	int ani_counter{};
	sf::Vector2i sheetCoordinate; // Coordinate on spritesheet
	sf::Vector2i spriteSize;
	int animation_it_limit;
	bool horizontal{ true };
	
	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently walking in
	bool m_WalkLeftPressed;
	bool m_WalkRightPressed;

	// Which directions is the character currently walking in
	bool m_RunLeftPressed;
	bool m_RunRightPressed;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;
	
	float timeElapsed;
	float animationTimer = 0;

	// Private variables and functions
private:
	// What is the gravity
	float m_Gravity;

	// How fast is the character
	float m_MaxWalkSpeed = 300;
	float m_MaxRunSpeed = 700;
	float m_VelocityX = 0;
	float m_Acceleration = 0.9;
	float m_Deceleration = 2;


	// Where is the player
	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	Texture m_Texture;

	// All our public functions will come next
public:

	void spawn(Vector2f startPosition, float gravity);

	bool handleInput();
	// This class is now abstract and cannot be instanciated

	//setSprite to use correct animation cell
	void setSpriteFromSheet(sf::IntRect textureBox);

	//move the rectangle to the next cell in the animation
	void moveTextureRect();

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();
	Sprite getSpriteFromSheet();

	// Make the character walk
	void walkLeft(float elapsedTime);
	void walkRight(float elapsedTime);

	// Make the character run
	void runLeft(float elapsedTime);
	void runRight(float elapsedTime);

	// Make the character slide to a stop
	void slideStopRight(float elapsedTime);
	void slideStopLeft(float elapsedTime);

	// Make the character stand firm
	void stopFalling(float position);
	void stopRight(float position);
	void stopLeft(float position);
	void stopJump();

	// Where is the center of the character
	Vector2f getCenter();

	// We will call this function once every frame
	void update(float elapsedTime);
};
