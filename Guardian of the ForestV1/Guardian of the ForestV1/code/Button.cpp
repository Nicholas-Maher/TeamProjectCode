#include "Button.h"

Button::Button()
{
	// Load the font
	m_Font.loadFromFile("fonts/Cinzel.ttf");
}

void Button::spawn(Vector2f position, Color buttonColour, int outlineThickness, String text, Color textColour)
{
    /** Patrick - buttons based on Nicholas' main main button logic from Engine but I added a way to centre the text in the buttons
    using their global bounds
    **/
    // button
    m_Button.setSize(Vector2f(300, 80));
    m_Button.setPosition(position);
    m_Button.setFillColor(buttonColour);
    m_Button.setOutlineColor(Color::White);
    m_Button.setOutlineThickness(outlineThickness);

    // text
    m_Text.setFont(m_Font);
    m_Text.setString(text);
    m_Text.setCharacterSize(30);
    m_Text.setFillColor(textColour);

    FloatRect textBounds = m_Text.getLocalBounds();
    m_Text.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    // Patrick - centring text in the buttons
    FloatRect buttonBounds = m_Button.getGlobalBounds();
    m_Text.setPosition(buttonBounds.left + buttonBounds.width / 2.f, buttonBounds.top + buttonBounds.height / 2.f);
}

FloatRect Button::getButton() const
{
    return m_Button.getGlobalBounds();
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(m_Button);
    window.draw(m_Text);
}