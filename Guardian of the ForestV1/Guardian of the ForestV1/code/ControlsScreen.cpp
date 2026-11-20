#include "ControlsScreen.h"

ControlsScreen::ControlsScreen()
{
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // title
    m_Title.setFont(m_Font);
    m_Title.setString("CONTROL CONFIGURATION");
    m_Title.setCharacterSize(100);
    m_Title.setFillColor(Color(46, 111, 64));

    FloatRect titleBounds = m_Title.getLocalBounds();
    m_Title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    m_Title.setPosition(m_Resolution.x / 2.0f, 350);

    // jump button
    m_JumpButton.spawn(Vector2f(m_Resolution.x / 3.0f, 500), Color(45, 110, 55), 0, "JUMP", Color::White);

    // m_Jump Text
    m_JumpText.setFont(m_Font);
    m_JumpText.setString("Jump");
    m_JumpText.setCharacterSize(30);
    m_JumpText.setFillColor(Color(46, 111, 64));

    FloatRect boundsJump = m_JumpText.getLocalBounds();
    float xPos = m_JumpButton.getButton().left + m_JumpButton.getButton().width / 2.0f;
    float yPos = m_JumpButton.getButton().getPosition().y - 20;
    m_JumpText.setOrigin(boundsJump.left + boundsJump.width / 2.f, boundsJump.top + boundsJump.height / 2.f);
    m_JumpText.setPosition(xPos, yPos);

    // left button
    m_MoveLeftButton.spawn(Vector2f(m_Resolution.x / 3.0f + m_Resolution.x / 3.0f, 500), Color(45, 110, 55), 0, "MOVE LEFT", Color::White);

    // m_LeftText Text
    m_LeftText.setFont(m_Font);
    m_LeftText.setString("Move Left");
    m_LeftText.setCharacterSize(30);
    m_LeftText.setFillColor(Color(46, 111, 64));

    FloatRect boundsLeft = m_LeftText.getLocalBounds();
    xPos = m_MoveLeftButton.getButton().left + m_MoveLeftButton.getButton().width / 2.0f;
    yPos = m_MoveLeftButton.getButton().top - 20;
    m_LeftText.setOrigin(boundsLeft.left + boundsLeft.width / 2.f, boundsLeft.top + boundsLeft.height / 2.f);
    m_LeftText.setPosition(xPos, yPos);

    // right button
    m_MoveRightButton.spawn(Vector2f(m_Resolution.x / 3.0f, 620), Color(45, 110, 55), 0, "MOVE RIGHT", Color::White);

    // m_RightText Text
    m_RightText.setFont(m_Font);
    m_RightText.setString("Move Right");
    m_RightText.setCharacterSize(30);
    m_RightText.setFillColor(Color(46, 111, 64));

    FloatRect boundsRight = m_RightText.getLocalBounds();
    xPos = m_MoveRightButton.getButton().left + m_MoveRightButton.getButton().width / 2.0f;
    yPos = m_MoveRightButton.getButton().top - 20;
    m_RightText.setOrigin(boundsRight.left + boundsRight.width / 2.f, boundsRight.top + boundsRight.height / 2.f);
    m_RightText.setPosition(xPos, yPos);

    // run button
    m_RunButton.spawn(Vector2f(m_Resolution.x / 3.0f + m_Resolution.x / 3.0f, 620), Color(45, 110, 55), 0, "RUN", Color::White);

    // m_RunText Text
    m_RunText.setFont(m_Font);
    m_RunText.setString("Run");
    m_RunText.setCharacterSize(30);
    m_RunText.setFillColor(Color(46, 111, 64));

    FloatRect boundsRun = m_RunText.getLocalBounds();
    xPos = m_RunButton.getButton().left + m_RunButton.getButton().width / 2.0f;
    yPos = m_RunButton.getButton().top - 20;
    m_RunText.setOrigin(boundsRun.left + boundsRun.width / 2.f, boundsRun.top + boundsRun.height / 2.f);
    m_RunText.setPosition(xPos, yPos);

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
    window.draw(m_Title);
    window.draw(m_JumpText);
    m_JumpButton.draw(window);
    window.draw(m_LeftText);
    m_MoveLeftButton.draw(window);
    window.draw(m_RightText);
    m_MoveRightButton.draw(window);
    window.draw(m_RunText);
    m_RunButton.draw(window);
    m_ResetButton.draw(window);
    m_MenuMenuButton.draw(window);
    m_QuitButton.draw(window);
}