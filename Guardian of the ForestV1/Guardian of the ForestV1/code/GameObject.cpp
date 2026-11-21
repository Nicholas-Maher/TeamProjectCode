#include "GameObject.h"

FloatRect GameObject::getPosition()
{
	return m_Sprite.getGlobalBounds();
}

Sprite GameObject::getSprite()
{
	return m_Sprite;
}

GameObject::~GameObject()
{

}