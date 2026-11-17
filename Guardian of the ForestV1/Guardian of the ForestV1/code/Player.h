#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
protected:
	// Of course we will need a sprite
	Sprite m_Sprite;

	/*************** Clo animation variables ***************/
	// And a texture
	Texture m_Texture;

	sf::Vector2i sheetCoordinate; // Coordinate on spritesheet
	sf::Vector2i spriteSize;

	int animation_it_limit;
	bool horizontal{ true };
	int ani_counter{};
	int counter{};
	Clock clock;
	float timeElapsed;
	float animationTimer = 0;
	/*************** Clo animation variables end ***************/

	// How long does a jump last
	float m_JumpDuration;

	// Is character currently jumping or falling
	bool m_IsJumping;
	bool m_IsFalling;

	// Which directions is the character currently walking in
	bool m_WalkLeftPressed = false;
	bool m_WalkRightPressed = false;

	// Which directions is the character currently running in
	bool m_RunLeftPressed = false;
	bool m_RunRightPressed = false;

	// How long has this jump lasted so far
	float m_TimeThisJump;

	// Has the player just initialted a jump
	bool m_JustJumped = false;

	// Private variables and functions come next
private:
	// What is the gravity
	float m_Gravity;

	// How fast is the character
	float m_MaxWalkSpeed = 300;
	float m_MaxRunSpeed = 700;
	float m_VelocityX = 0;
	float m_Acceleration = 0.9;
	float m_Deceleration = 2;

	const int START_POWER = 0;
	const int START_FULL_POWER = 100;
	int m_FullPower = START_FULL_POWER;
	int m_Power = START_POWER;

	const int START_HEALTH = 100;
	int m_FullHealth = START_HEALTH;
	int m_Health = START_HEALTH;

	// When was the gameactor last hit
	Time m_timeLastHit;

	// Where is the player
	Vector2f m_Position;

	// Where are the characters various body parts?
	FloatRect m_Feet;
	FloatRect m_Head;
	FloatRect m_Right;
	FloatRect m_Left;

	// And a texture
	//Texture m_Texture;

	// All our public functions will come next
public:
	// A constructor specific to Player
	Player(); // our version didn't have this here

	void spawn(Vector2f startPosition, float gravity);

	// The overriden input handler for Player
	bool handleInput();

	//setSprite to use correct animation cell
	void setSpriteFromSheet(sf::IntRect textureBox); // clo

	//move the rectangle to the next cell in the animation
	void moveTextureRect(); // clo

	int getPower() const;
	void setPower(int health);
	int getFullPower() const;
	void setFullPower(int fullHealth);
	int getStartPower() const;
	int getStartFullPower() const;

	int getHealth() const;
	void setHealth(int health);
	int getFullHealth() const;
	void setFullHealth(int fullHealth);
	int getStartHealth() const;

	// Handle the player getting hit by an enemy
	bool hit(Time hitTime, int damage);

	// Where is the player
	FloatRect getPosition();

	// A rectangle representing the position of different parts of the sprite
	FloatRect getFeet();
	FloatRect getHead();
	FloatRect getRight();
	FloatRect getLeft();

	// Send a copy of the sprite to main
	Sprite getSprite();
	Sprite getSpriteFromSheet(); // clo

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
