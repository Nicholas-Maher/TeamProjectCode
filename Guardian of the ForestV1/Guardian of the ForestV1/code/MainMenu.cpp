#include "MainMenu.h"

MainMenu::MainMenu()
{
	/*Nicholas -- adding Font to the main Menu*/
	m_Font.loadFromFile("fonts/Cinzel.ttf");

    /**************  Nicholas - adding a simple main menu to the game ************/
    /** Patrick - moved Nicholas's logic from Engine::draw() into MainManu and used Screen::draw() to draw the text and 
    buttons rather than m_Window.draw() directly and declared all text and buttons and as member variables in the MainMenu.h rather than local **/


    // Game title
    title.setFont(m_Font);
    title.setString("GUARDIAN OF THE FOREST");
    title.setCharacterSize(100);
    title.setFillColor(Color(46, 111, 64));

    FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    title.setPosition(960, 350);

    // Start Game button
    m_StartButton.setSize(Vector2f(300, 80));
    m_StartButton.setPosition(810, 500);
    m_StartButton.setFillColor(Color(45, 110, 55));
    m_StartButton.setOutlineColor(Color::White);

    // Start Game text
    m_StartText.setFont(m_Font);
    m_StartText.setString("START GAME");
    m_StartText.setCharacterSize(30);
    m_StartText.setFillColor(Color::White);

    FloatRect startBounds = m_StartText.getLocalBounds();
    m_StartText.setOrigin(startBounds.left + startBounds.width / 2.f, startBounds.top + startBounds.height / 2.f);
    m_StartText.setPosition(960, 540);

    // Top times button
    m_TopTimesButton.setSize(Vector2f(300, 80));
    m_TopTimesButton.setPosition(810, 620);
    m_TopTimesButton.setFillColor(Color(45, 110, 55));
    m_TopTimesButton.setOutlineColor(Color::White);

    // Top times text
    m_TopTimesText.setFont(m_Font);
    m_TopTimesText.setString("TOP SCORES");
    m_TopTimesText.setCharacterSize(30);
    m_TopTimesText.setFillColor(Color::White);

    FloatRect topTimesBounds = m_TopTimesText.getLocalBounds();
    m_TopTimesText.setOrigin(topTimesBounds.left + topTimesBounds.width / 2.f, topTimesBounds.top + topTimesBounds.height / 2.f);
    m_TopTimesText.setPosition(960, 660);

    // Quit button
    m_QuitButton.setSize(Vector2f(300, 80));
    m_QuitButton.setPosition(810, 740);
    m_QuitButton.setFillColor(Color(120, 45, 40));
    m_QuitButton.setOutlineColor(Color::White);
    m_QuitButton.setOutlineThickness(3);

    // Quit text
    m_QuitText.setFont(m_Font);
    m_QuitText.setString("QUIT GAME");
    m_QuitText.setCharacterSize(30);
    m_QuitText.setFillColor(Color::White);

    FloatRect quitBounds = m_QuitText.getLocalBounds();
    m_QuitText.setOrigin(quitBounds.left + quitBounds.width / 2.f, quitBounds.top + quitBounds.height / 2.f);
    m_QuitText.setPosition(960, 780);

    /* End of:  Nicholas - adding a simple main menu to the game ************/
	
}

FloatRect MainMenu::getStartButton() const
{
    return m_StartButton.getGlobalBounds();
}

FloatRect MainMenu::getTopTimesButton() const
{
    return m_TopTimesButton.getGlobalBounds();
}

void MainMenu::draw(sf::RenderWindow& window)
{
    window.draw(title);
    window.draw(m_StartButton);
    window.draw(m_StartText);
    window.draw(m_TopTimesButton);
    window.draw(m_TopTimesText);
    window.draw(m_QuitButton);
    window.draw(m_QuitText);
}