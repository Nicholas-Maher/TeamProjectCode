#include "Player.h"
#include "LevelManager.h"
#include "TextureHolder.h"
#include <iostream>
using namespace std;
#include <cmath>
#include <random>

Player::Player()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/pacman-spritesheet-resized-810-730.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 12,62,50,50 });
	ani_counter = 1;

	m_JumpDuration = .50;
m_Health = m_FullHealth;
}

void Player::spawn(Vector2f startPosition, float gravity)
{
	// Place the Player at the starting point
	m_Position.x = startPosition.x;
	m_Position.y = startPosition.y;

	// Initialize the gravity
	m_Gravity = gravity;

	// Move the sprite in to position
	m_Sprite.setPosition(m_Position);
}


bool Player::handleInput()
{
	m_JustJumped = false;

	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		// Start a jump if not already jumping
		// but only if standing on a block (not falling)
		if (!m_IsJumping && !m_IsFalling)
		{
			m_IsJumping = true;
			m_TimeThisJump = 0;
			m_JustJumped = true;
		}
	}
	// -- Nicholas cause of it was the player charter was consitonly being presed down
	// while collision detection pushed them back up potentially causing the jitter maybe
	// also by adding an else if stateng if ture m_IsJumpng  the if falling is then to be true then
	else if(m_IsJumping)
	{
		m_IsJumping = false;
		m_IsFalling = true;
	}
	// Check if walking keys are pressed
	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		m_WalkLeftPressed = true;
	}
	else
	{
		m_WalkLeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		m_WalkRightPressed = true;
	}
	else
	{
		m_WalkRightPressed = false;
	}

	// Check if running keys are pressed
	if (Keyboard::isKeyPressed(Keyboard::A) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		m_WalkLeftPressed = false;
		m_RunLeftPressed = true;
	}
	else
	{
		m_RunLeftPressed = false;
	}

	if (Keyboard::isKeyPressed(Keyboard::D) && Keyboard::isKeyPressed(Keyboard::LShift))
	{
		m_WalkRightPressed = false;
		m_RunRightPressed = true;
	}
	else
	{
		m_RunRightPressed = false;
	}
	return m_JustJumped;

}

void Player::update(float elapsedTime)
{
	timeElapsed = elapsedTime;

	// incrementally increases speed while right is pressed until max speed is reached
	if (m_WalkRightPressed)
	{
		walkRight(elapsedTime);

		//2nd row of sprite sheet 3 characters 150 pixels by 50 pixels
		setSpriteFromSheet(sf::IntRect(12, 62, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();
	}

	// incrementally increases speed while right is pressed until max speed is reached
	if (m_RunRightPressed)
	{
		runRight(elapsedTime);

		//2nd row of sprite sheet 3 chara2ters 150 pixels by 50 pixels
		setSpriteFromSheet(sf::IntRect(212, 62, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();
	}

	// incrementally increases speed while left is pressed until max speed is reached
	if (m_WalkLeftPressed)
	{
		walkLeft(elapsedTime);

		//1st row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(12, 12, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();
	}

	// incrementally increases speed while left is pressed until max speed is reached
	if (m_RunLeftPressed)
	{
		runLeft(elapsedTime);

		//1st row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(212, 12, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();
	}

	// If there is no input for walking or running in any direction, the Player will slide quickly to a stop in the direction they were last travelling
	if (!m_WalkRightPressed && !m_WalkLeftPressed && !m_RunRightPressed && !m_RunLeftPressed)
	{
		if (m_VelocityX > 0)
		{
			slideStopRight(elapsedTime);
		}
		else if (m_VelocityX < 0)
		{
			slideStopLeft(elapsedTime);
		}
	}

	// Handle Jumping
	if (m_IsJumping)
	{
		// Update how long the jump has been going
		m_TimeThisJump += elapsedTime;

		//3rd row of sprite sheet 3 characters
		setSpriteFromSheet(sf::IntRect(12, 112, 150, 50));
		//move the rectangle to the appropriate cell
		moveTextureRect();

		// Is the jump going upwards
		if (m_TimeThisJump < m_JumpDuration)
		{
			// Move up at twice gravity
			m_Position.y -= m_Gravity * 2.1 * elapsedTime;
		}
		else
		{
			m_IsJumping = false;
			m_IsFalling = true;
		}
	}

	// Apply gravity
	if (m_IsFalling)
	{
		m_Position.y += m_Gravity * elapsedTime;
	}

	// Update the rect for all body parts
	FloatRect r = getPosition();


	// Feet
	m_Feet.left = r.left;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left + 3;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width - 6;
	m_Head.height = 1;

	// Right
	m_Right.left = r.left + r.width - 2;
	m_Right.top = r.top + r.height * .35;
	m_Right.width = 1;
	m_Right.height = r.height * .3;

	// Left
	m_Left.left = r.left;
	m_Left.top = r.top + r.height * .5;
	m_Left.width = 1;
	m_Left.height = r.height * .3;

	// Move the sprite into position
	m_Sprite.setPosition(m_Position);

}

int Player::getHealth()
{
	return m_Health;
}

int Player::getFullHealth()
{
	return m_FullHealth;
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return Vector2f(m_Position.x + m_Sprite.getGlobalBounds().width / 2, m_Position.y + m_Sprite.getGlobalBounds().height / 2);
}

FloatRect Player::getFeet()
{
	return m_Feet;
}

FloatRect Player::getHead()
{
	return m_Head;
}

FloatRect Player::getLeft()
{
	return m_Left;
}

FloatRect Player::getRight()
{
	return m_Right;
}

Sprite Player::getSprite()
{
	return m_Sprite;
}

Sprite Player::getSpriteFromSheet()
{
	return m_Sprite;
}

/****** Player movement methods - Patrick *****/
void Player::walkRight(float elapsedTime)
{
	m_VelocityX += m_MaxWalkSpeed * m_Acceleration * elapsedTime;

	// Stop accelerating once top speed is reached
	if (m_VelocityX > m_MaxWalkSpeed)
	{
		m_VelocityX = m_MaxWalkSpeed;
		//cout << "Walk Right - Cap hit " << endl;
	}
	// Multiplying by delta t is needed here to prevent the character hitting max speed immediately
	m_Position.x += m_VelocityX * elapsedTime;
	//cout << "Walk Right - Speed: " << m_MaxWalkSpeed << " Velocity: " << m_VelocityX << endl;
}

void Player::runRight(float elapsedTime)
{
	m_VelocityX += m_MaxRunSpeed * m_Acceleration * elapsedTime;

	// Stop accelerating once top speed is reached
	if (m_VelocityX > m_MaxRunSpeed)
	{
		m_VelocityX = m_MaxRunSpeed;
	}
	// Multiplying by delta t is needed here to prevent the character hitting max speed immediately
	m_Position.x += m_VelocityX * elapsedTime;
	//cout << "Run Right - Speed: " << m_MaxRunSpeed << " Velocity: " << m_VelocityX << endl;
}

void Player::slideStopRight(float elapsedTime)
{
	m_VelocityX -= m_MaxWalkSpeed * m_Deceleration * elapsedTime;

	if (m_VelocityX < 0)
	{
		m_VelocityX = 0;
	}
	m_Position.x += m_VelocityX * elapsedTime;
}

void Player::walkLeft(float elapsedTime)
{
	m_VelocityX -= m_MaxWalkSpeed * m_Acceleration * elapsedTime;

	if (m_VelocityX < -m_MaxWalkSpeed)
	{
		m_VelocityX = -m_MaxWalkSpeed;
		//cout << "Walk Left - Cap hit " << endl;
	}
	m_Position.x += m_VelocityX * elapsedTime;
	//cout << "Walk Left - Speed: " << m_MaxWalkSpeed << " Velocity: " << m_VelocityX << endl;
}

void Player::runLeft(float elapsedTime)
{
	m_VelocityX -= m_MaxRunSpeed * m_Acceleration * elapsedTime;

	if (m_VelocityX < -m_MaxRunSpeed)
	{
		m_VelocityX = -m_MaxRunSpeed;
	}
	m_Position.x += m_VelocityX * elapsedTime;
	//cout << "Run Left - Speed: " << m_MaxRunSpeed << " Velocity: " << m_VelocityX << endl;
}

void Player::setSpriteFromSheet(sf::IntRect textureBox)
{
	LevelManager l;
	int tile_size = l.TILE_SIZE;
	sheetCoordinate = sf::Vector2i(textureBox.left, textureBox.top);
	spriteSize = sf::Vector2i(tile_size, tile_size);
	if (textureBox.width > tile_size)
	{
		animation_it_limit = textureBox.width / tile_size;

		horizontal = true;
	}
	else if (textureBox.height > tile_size)
	{
		animation_it_limit = textureBox.height / tile_size;
		horizontal = false;
	}
	else
		throw std::logic_error("Animation bounding box must contain multiply sprites, setSprite(sf::IntRect )\n");
	m_Sprite.setTextureRect(sf::IntRect{ sheetCoordinate, spriteSize });

}


void Player::slideStopLeft(float elapsedTime)
{
	m_VelocityX += m_MaxWalkSpeed * m_Deceleration * elapsedTime;

	if (m_VelocityX > 0)
	{
		m_VelocityX = 0;
	}
	m_Position.x += m_VelocityX * elapsedTime;
}

void Player::stopFalling(float position)
{
	m_Position.y = position - getPosition().height;
	m_Sprite.setPosition(m_Position);
	m_IsFalling = false;
}

void Player::stopRight(float position)
{
	m_Position.x = position - m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Player::stopLeft(float position)
{
	m_Position.x = position + m_Sprite.getGlobalBounds().width;
	m_Sprite.setPosition(m_Position);
}

void Player::stopJump()
{
	// Stop a jump early
	m_IsJumping = false;
	m_IsFalling = true;
}

void Player::moveTextureRect()
{
	// if the animation counter is greater than the animation limit reset to 1;
	if (ani_counter ==animation_it_limit)
	{
		ani_counter = 0;
	}

	if (horizontal)
	{
		m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(spriteSize.x * ani_counter, 0), spriteSize));
	}
	else
	{
		m_Sprite.setTextureRect(sf::IntRect(sheetCoordinate + sf::Vector2i(0, spriteSize.y * ani_counter), spriteSize));
	}

	//increment animation counter to point to the next frame
	double timePerFrame;
	timePerFrame = 1.0 / 6.0;
	animationTimer = animationTimer + timeElapsed;
	if (animationTimer > timePerFrame)
	{
		ani_counter++;
		animationTimer = 0;
	}
}

bool Player::hit(Time hitTime)
{
	if (hitTime.asMilliseconds() - m_timeLastHit.asMilliseconds() > 300)// 3 tenths of second
	{
		m_timeLastHit = hitTime;
		m_Health -= 10.0f;
		return true;
	}
	else
	{
		return false;
	}
}
