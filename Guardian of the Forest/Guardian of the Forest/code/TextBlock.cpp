#include "TextBlock.h"

TextBlock::TextBlock()
{
    m_Font.loadFromFile("fonts/Cinzel.ttf");
}

void TextBlock::spawn(String text, unsigned int characterSize, Color colour, Vector2f position)
{
    m_Text.setFont(m_Font);
    m_Text.setString(text);
    m_Text.setCharacterSize(characterSize);
    m_Text.setFillColor(colour);

    FloatRect titleBounds = m_Text.getLocalBounds();

    m_Text.setOrigin(
        titleBounds.left + titleBounds.width / 2.f,
        titleBounds.top + titleBounds.height / 2.f
    );
    m_Position = position;
    m_Text.setPosition(m_Position);
}
void TextBlock::setString(String text)
{
    m_Text.setString(text);
    FloatRect textRect = m_Text.getLocalBounds();
    m_Text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_Text.setPosition(m_Position);
}

Vector2f TextBlock::getPosition()
{
    return m_Position;
}

void TextBlock::draw(sf::RenderWindow& window)
{
    window.draw(m_Text);
}
