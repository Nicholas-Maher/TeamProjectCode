#include "MainMenu.h"

MainMenu::MainMenu()
{
	/*Nicholas -- adding Font to the main Menu*/
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    /**************  Nicholas - adding a simple main menu to the game ************/
    /** 
    Patrick - moved Nicholas's main menu logic from Engine::draw() into MainManu. I moved the button and text creation logic
    Nicholas made into Button so Button::spawn() could be called to create buttons 
    and added my own way to centre the text in the buttons. Used Screen::draw() to draw the text and 
    buttons rather than m_Window.draw() directly and declared all text and buttons and as member variables in the MainMenu.h 
    **/

    // Game title
    m_Title.setFont(m_Font);
    m_Title.setString("GUARDIAN OF THE FOREST");
    m_Title.setCharacterSize(100);
    m_Title.setFillColor(Color(46, 111, 64));

    FloatRect titleBounds = m_Title.getLocalBounds();
    m_Title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    m_Title.setPosition(m_Resolution.x / 2.0f, 350);

    // Start Game button
    m_StartButton.spawn(Vector2f(m_Resolution.x / 2.0f, 500), Color(45, 110, 55), 0, "START GAME", Color::White);

    // Top times button
    m_TopTimesButton.spawn(Vector2f(m_Resolution.x / 2.0f, 620), Color(45, 110, 55), 0, "TOP SCORES", Color::White);

    // Controls button
    m_ControlsButton.spawn(Vector2f(m_Resolution.x / 2.0f, 740), Color(45, 110, 55), 0, "CONTROLS", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 860), Color(120, 45, 40), 3, "QUIT GAME", Color::White);


    /* End of:  Nicholas - adding a simple main menu to the game ************/
}

FloatRect MainMenu::getStartButton() const
{
    return m_StartButton.getButton();
}

FloatRect MainMenu::getTopTimesButton() const
{
    return m_TopTimesButton.getButton();
}

FloatRect MainMenu::getControlsButton() const
{
    return m_ControlsButton.getButton();
}

void MainMenu::draw(sf::RenderWindow& window)
{
    window.draw(m_Title);
    m_StartButton.draw(window);
    m_TopTimesButton.draw(window);
    m_ControlsButton.draw(window);
    m_QuitButton.draw(window);
}