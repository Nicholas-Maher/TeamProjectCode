#include "TopTimesScreen.h"

TopTimesScreen::TopTimesScreen()
{
    m_FileToLoad = "gamedata/topTimes.txt"; // sets text file to load
    loadTopTimesFile();

	m_Font.loadFromFile("fonts/Cinzel.ttf");

    /** Patrick - buttons based on Nicholas' main main button logic **/

    // Screen heading text
    m_Title.setFont(m_Font);
    m_Title.setString("Top Times");
    m_Title.setCharacterSize(100);
    m_Title.setFillColor(Color(46, 111, 64));

    FloatRect titleBounds = m_Title.getLocalBounds();
    m_Title.setOrigin(titleBounds.left + titleBounds.width / 2.f, titleBounds.top + titleBounds.height / 2.f);
    m_Title.setPosition(960, 150);

    // top times text
    m_TimesText.setFont(m_Font);
    m_TimesText.setCharacterSize(50);
    m_TimesText.setFillColor(Color(46, 111, 64));
    setTimesText();

    // Main Menu button
    m_MainMenuButton.setSize(Vector2f(300, 80));
    m_MainMenuButton.setPosition(810, 600);
    m_MainMenuButton.setFillColor(Color(45, 110, 55));
    m_MainMenuButton.setOutlineColor(Color::White);

    // main menu text
    m_MainMenuText.setFont(m_Font);
    m_MainMenuText.setString("MAIN MENU");
    m_MainMenuText.setCharacterSize(30);
    m_MainMenuText.setFillColor(Color::White);

    FloatRect menuBounds = m_MainMenuText.getLocalBounds();
    m_MainMenuText.setOrigin(menuBounds.left + menuBounds.width / 2.f, menuBounds.top + menuBounds.height / 2.f);
    m_MainMenuText.setPosition(960, 640);

    // Reset times button
    m_ResetTimesButton.setSize(Vector2f(300, 80));
    m_ResetTimesButton.setPosition(810, 720);
    m_ResetTimesButton.setFillColor(Color(45, 110, 55));
    m_ResetTimesButton.setOutlineColor(Color::White);

    // Reset times text
    m_ResetTimesText.setFont(m_Font);
    m_ResetTimesText.setString("RESET TIMES");
    m_ResetTimesText.setCharacterSize(30);
    m_ResetTimesText.setFillColor(Color::White);

    FloatRect resetBounds = m_ResetTimesText.getLocalBounds();
    m_ResetTimesText.setOrigin(resetBounds.left + resetBounds.width / 2.f, resetBounds.top + resetBounds.height / 2.f);
    m_ResetTimesText.setPosition(960, 760);

    // Quit button
    m_QuitButton.setSize(Vector2f(300, 80));
    m_QuitButton.setPosition(810, 840);
    m_QuitButton.setFillColor(Color(120, 45, 40));
    m_QuitButton.setOutlineColor(Color::White);
    m_QuitButton.setOutlineThickness(3);

    m_QuitButton.getGlobalBounds();

    // Quit text
    m_QuitText.setFont(m_Font);
    m_QuitText.setString("QUIT GAME");
    m_QuitText.setCharacterSize(30);
    m_QuitText.setFillColor(Color::White);

    FloatRect quitBounds = m_QuitText.getLocalBounds();
    m_QuitText.setOrigin(quitBounds.left + quitBounds.width / 2.f, quitBounds.top + quitBounds.height / 2.f);
    m_QuitText.setPosition(960, 880);
}

FloatRect TopTimesScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getGlobalBounds();
}

FloatRect TopTimesScreen::getResetTimesButton() const
{
    return m_ResetTimesButton.getGlobalBounds();
}

void TopTimesScreen::setTimesText()
{
    std::stringstream timesStream;
    timesStream <<
        "\n1 - " << m_TopTimes[0] <<
        "\n2 - " << m_TopTimes[1] <<
        "\n3 - " << m_TopTimes[2] <<
        "\n4 - " << m_TopTimes[3] <<
        "\n5 - " << m_TopTimes[4];

    m_TimesText.setString(timesStream.str());

    FloatRect textRect = m_TimesText.getLocalBounds();
    m_TimesText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_TimesText.setPosition(m_Resolution.x / 2.0f, 370);
}

// reads the top times from the top times text file and puts them into the top times vector
void TopTimesScreen::loadTopTimesFile()
{
    // Load the appropriate text file
    ifstream inputFile(m_FileToLoad);

    // read the times in the file into a vector
    string time;
    while (inputFile >> time)
    {
        m_TopTimes.push_back(stoi(time)); // converts the string in the row into an int and pushes it into the top times vector
    }

    // close the file
    inputFile.close();
}

// returns whether or not the time should be in the top times leaderboard
bool TopTimesScreen::isATopTime(int time)
{
    for (int timeEntry : m_TopTimes)
    {
        // if the new time is lower than the top in the current position of the vector
        if (time <= timeEntry)
        {
            return true;
        }
    }
    return false;
}

// adds the new time to the leaderboard, and updates the text file and the text
void TopTimesScreen::addTimeToLeaderboard(int time)
{
    m_TopTimes.push_back(time);
    sort(m_TopTimes.begin(), m_TopTimes.end()); // sorts from quickest to slowest
    if (m_TopTimes.size() > m_NumTopTimes)
    {
        m_TopTimes.pop_back(); // removes the last time in the list
    }
    updateTopTimesFile();
    setTimesText();
}

// writes the top times from the vector into the text file
void TopTimesScreen::updateTopTimesFile()
{
    ofstream OutputFile(m_FileToLoad);

    for (int j = 0; j < m_TopTimes.size(); j++)
    {
        OutputFile << m_TopTimes[j] << endl;
    }
    // Close the file
    OutputFile.close();
}

// resets the high scores to be between 1000 and 5000 and updates the vector, the file, and the text 
// if the top times vector doesn't already match the default values
void TopTimesScreen::resetTopTimesToDefaults()
{
    vector<int> defaultTimes = { 1000, 2000, 3000, 4000, 5000 };
    // updates the vector, text file, and text for the screen if the top times vector doesn't already have default values
	// comparing vectors source - https://www.geeksforgeeks.org/cpp/quickly-check-two-stl-vectors-contain-elements-not/
    if (m_TopTimes != defaultTimes)
    {
        m_TopTimes.clear();
        // loops through the default times vector and pushes each value into the top times vector
        for (int defaultTime : defaultTimes)
        {
            m_TopTimes.push_back(defaultTime);
        }
        updateTopTimesFile();
        setTimesText();
    }
}

void TopTimesScreen::draw(sf::RenderWindow& window)
{
    window.draw(m_Title);
    window.draw(m_TimesText);
    window.draw(m_MainMenuButton);
    window.draw(m_MainMenuText);
    window.draw(m_ResetTimesButton);
    window.draw(m_ResetTimesText);
    window.draw(m_QuitButton);
    window.draw(m_QuitText);
}
