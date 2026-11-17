#include "Player.h"
#include "LevelManager.h"
#include "TextureHolder.h"
#include <iostream>

Player::Player()
{
	// Associate a texture with the sprite
	m_Sprite = Sprite(TextureHolder::GetTexture("graphics/pacman-spritesheet-resized-810-730.png"));
	m_Sprite.setTextureRect(sf::IntRect{ 12,62,50,50 });
	ani_counter = 1;

	m_JumpDuration = .45;
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

void Player::update(float elapsedTime)
{
	timeElapsed = elapsedTime; // needed for cycling between animations

	/********    walking        ********/
	if (m_WalkRightPressed)
	{
		walkRight(elapsedTime);
	}

	if (m_WalkLeftPressed)
	{
		walkLeft(elapsedTime);
	}

	/************   running      *************/
	// incrementally increases speed while right is pressed until max speed is reached
	if (m_RunRightPressed)
	{
		runRight(elapsedTime);
	}

	// incrementally increases speed while left is pressed until max speed is reached
	if (m_RunLeftPressed)
	{
		runLeft(elapsedTime);
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
			m_Position.y -= m_Gravity * 2 * elapsedTime;
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
	m_Feet.left = r.left + 3;
	m_Feet.top = r.top + r.height - 1;
	m_Feet.width = r.width - 6;
	m_Feet.height = 1;

	// Head
	m_Head.left = r.left;
	m_Head.top = r.top + (r.height * .3);
	m_Head.width = r.width;
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

int Player::getHealth() const
{
	return m_Health;
}

void Player::setHealth(int health)
{
	m_Health = health;
}

int Player::getFullHealth() const
{
	return m_FullHealth;
}

void Player::setFullHealth(int fullHealth)
{
	m_FullHealth = fullHealth;
}

int Player::getStartHealth() const
{
	return START_HEALTH;
}

FloatRect Player::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Vector2f Player::getCenter()
{
	return Vector2f(
		m_Position.x + m_Sprite.getGlobalBounds().width / 2,
		m_Position.y + m_Sprite.getGlobalBounds().height / 2
	);
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

bool Player::hit(Time hitTime, int damage)
{
	if (hitTime.asMilliseconds() - m_timeLastHit.asMilliseconds() > 300)// 3 tenths of second
	{
		m_timeLastHit = hitTime;
		m_Health -= damage;
		//std::cout << "hit time: " << hitTime.asSeconds() << std::endl;
		return true;
	}
	else
	{
		return false;
	}
}

/****** Player movement methods - Patrick *****/
void Player::walkRight(float elapsedTime)
{
	m_VelocityX += m_MaxWalkSpeed * m_Acceleration * elapsedTime;

	// Stop accelerating once top speed is reached
	if (m_VelocityX > m_MaxWalkSpeed)
	{
		m_VelocityX = m_MaxWalkSpeed;
	}
	// Multiplying by delta t is needed here to prevent the character hitting max speed immediately
	m_Position.x += m_VelocityX * elapsedTime;

	//2nd row of sprite sheet 3 characters 150 pixels by 50 pixels
	setSpriteFromSheet(sf::IntRect(12, 62, 150, 50));
	//move the rectangle to the appropriate cell
	moveTextureRect();
}

void Player::walkLeft(float elapsedTime)
{
	m_VelocityX -= m_MaxWalkSpeed * m_Acceleration * elapsedTime;

	if (m_VelocityX < -m_MaxWalkSpeed)
	{
		m_VelocityX = -m_MaxWalkSpeed;
	}
	m_Position.x += m_VelocityX * elapsedTime;

	//1st row of sprite sheet 3 characters
	setSpriteFromSheet(sf::IntRect(12, 12, 150, 50));
	//move the rectangle to the appropriate cell
	moveTextureRect();
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

	//2nd row of sprite sheet 3 chara2ters 150 pixels by 50 pixels
	setSpriteFromSheet(sf::IntRect(212, 62, 150, 50));
	//move the rectangle to the appropriate cell
	moveTextureRect();
}

void Player::runLeft(float elapsedTime)
{
	m_VelocityX -= m_MaxRunSpeed * m_Acceleration * elapsedTime;

	if (m_VelocityX < -m_MaxRunSpeed)
	{
		m_VelocityX = -m_MaxRunSpeed;
	}
	m_Position.x += m_VelocityX * elapsedTime;

	//1st row of sprite sheet 3 characters
	setSpriteFromSheet(sf::IntRect(212, 12, 150, 50));
	//move the rectangle to the appropriate cell
	moveTextureRect();
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

void Player::slideStopLeft(float elapsedTime)
{
	m_VelocityX += m_MaxWalkSpeed * m_Deceleration * elapsedTime;

	if (m_VelocityX > 0)
	{
		m_VelocityX = 0;
	}
	m_Position.x += m_VelocityX * elapsedTime;
}
/****** End Player movement methods - Patrick *****/

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

void Player::moveTextureRect()
{
	// if the animation counter is greater than the animation limit reset to 1;
	if (ani_counter == animation_it_limit)
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

Sprite Player::getSpriteFromSheet()
{
	return m_Sprite;
}

// A virtual function
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
	else
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