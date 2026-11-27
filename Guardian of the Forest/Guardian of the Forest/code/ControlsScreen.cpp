#include "ControlsScreen.h"

ControlsScreen::ControlsScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // title
    m_Title.spawn("CONTROL CONFIGURATION", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 350));

    // jump button
    m_JumpButton.spawn(Vector2f(m_Resolution.x / 3.0f, 500), Color(45, 110, 55), 0, "JUMP", Color::White);

    // m_Jump Text
    float xPos = m_JumpButton.getButton().left + m_JumpButton.getButton().width / 2.0f;
    float yPos = m_JumpButton.getButton().getPosition().y - 20;
    m_JumpText.spawn("JUMP", 30, Color(46, 111, 64), Vector2f(xPos, yPos));

    // left button
    m_MoveLeftButton.spawn(Vector2f(m_Resolution.x / 3.0f + m_Resolution.x / 3.0f, 500), Color(45, 110, 55), 0, "MOVE LEFT", Color::White);

    // m_LeftText Text
    xPos = m_MoveLeftButton.getButton().left + m_MoveLeftButton.getButton().width / 2.0f;
    yPos = m_MoveLeftButton.getButton().top - 20;
    m_LeftText.spawn("MOVE LEFT", 30, Color(46, 111, 64), Vector2f(xPos, yPos));

    // right button
    m_MoveRightButton.spawn(Vector2f(m_Resolution.x / 3.0f, 620), Color(45, 110, 55), 0, "MOVE RIGHT", Color::White);

    // m_RightText Text
    xPos = m_MoveRightButton.getButton().left + m_MoveRightButton.getButton().width / 2.0f;
    yPos = m_MoveRightButton.getButton().top - 20;
    m_RightText.spawn("MOVE RIGHT", 30, Color(46, 111, 64), Vector2f(xPos, yPos));

    // run button
    m_RunButton.spawn(Vector2f(m_Resolution.x / 3.0f + m_Resolution.x / 3.0f, 620), Color(45, 110, 55), 0, "RUN", Color::White);

    // m_RunText Text
    xPos = m_RunButton.getButton().left + m_RunButton.getButton().width / 2.0f;
    yPos = m_RunButton.getButton().top - 20;
    m_RunText.spawn("RUN", 30, Color(46, 111, 64), Vector2f(xPos, yPos));

    // reset button
    m_ResetButton.spawn(Vector2f(m_Resolution.x / 2.0f, 740), Color(45, 110, 55), 0, "RESTORE DEFAULTS", Color::White);

    // main menu button
    m_MenuMenuButton.spawn(Vector2f(m_Resolution.x / 2.0f, 860), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 980), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
}

FloatRect ControlsScreen::getJumpButton() const
{
    return m_JumpButton.getButton();
}

FloatRect ControlsScreen::getMoveLeftButton() const
{
    return m_MoveLeftButton.getButton();
}

FloatRect ControlsScreen::getMoveRightButton() const
{
    return m_MoveRightButton.getButton();
}

FloatRect ControlsScreen::getRunButton() const
{
    return m_RunButton.getButton();
}
FloatRect ControlsScreen::getResetButton() const
{
    return m_ResetButton.getButton();
}
FloatRect ControlsScreen::getMainMenuButton() const
{
    return m_MenuMenuButton.getButton();
}

void ControlsScreen::setJumpButtonText(String text)
{
    m_JumpButton.setString(text);
}

void ControlsScreen::setMoveLeftButtonText(String text)
{
    m_MoveLeftButton.setString(text);
}

void ControlsScreen::setMoveRightButtonText(String text)
{
    m_MoveRightButton.setString(text);
}

void ControlsScreen::setRunButtonText(String text)
{
    m_RunButton.setString(text);
}

void ControlsScreen::draw(sf::RenderWindow& window)
{
    m_Title.draw(window);
    m_JumpText.draw(window);
    m_LeftText.draw(window);
    m_RightText.draw(window);
    m_RunText.draw(window);

    m_JumpButton.draw(window);
    m_MoveLeftButton.draw(window);
    m_MoveRightButton.draw(window);
    m_RunButton.draw(window);
    m_ResetButton.draw(window);
    m_MenuMenuButton.draw(window);
    m_QuitButton.draw(window);
}