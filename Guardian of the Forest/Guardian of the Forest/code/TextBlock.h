#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

// used for gathering the setting of font, string, character size, colour, and position of text blocks in the screen all into one reusable class
class TextBlock
{
private:
	Font m_Font;
	Text m_Text;
	Vector2f m_Position;

public:
	TextBlock();
	void spawn(String text, unsigned int characterSize, Color colour, Vector2f position);
	void setString(String text);
	Vector2f getPosition();
	void draw(sf::RenderWindow& window);
};