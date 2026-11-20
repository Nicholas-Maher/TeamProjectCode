#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Button
{
private:
	Font m_Font;
	RectangleShape m_Button;
	Text m_Text;

public:
	Button();
	void spawn(Vector2f position, Color buttonColour, int outlineThickness, String text, Color textColour);
	void setString(String text);
	FloatRect getButton() const;
	void draw(sf::RenderWindow& window);

};