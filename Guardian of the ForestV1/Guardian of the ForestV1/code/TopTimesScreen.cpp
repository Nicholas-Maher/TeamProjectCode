#include "TopTimesScreen.h"
#include "UtilityFunctions.h"

TopTimesScreen::TopTimesScreen()
{
    m_FileToLoad = "gamedata/topTimes.txt"; // sets text file to load
    loadTopTimesFile();

	m_Font.loadFromFile("fonts/Cinzel.ttf");

    // Screen heading text
    m_Title.spawn("TOP TIMES", 100, Color(46, 111, 64), Vector2f(m_Resolution.x / 2.0f, 150));

    // top times text
    m_TimesText.setFont(m_Font);
    m_TimesText.setCharacterSize(50);
    m_TimesText.setFillColor(Color(46, 111, 64));
    setTimesText();

    // Main Menu button
    m_MainMenuButton.spawn(Vector2f(m_Resolution.x / 2.0f, 600), Color(45, 110, 55), 0, "MAIN MENU", Color::White);

    // Reset times button
    m_ResetTimesButton.spawn(Vector2f(m_Resolution.x / 2.0f, 720), Color(45, 110, 55), 0, "RESET TIMES", Color::White);

    // Quit button
    m_QuitButton.spawn(Vector2f(m_Resolution.x / 2.0f, 840), Color(120, 45, 40), 3, "QUIT GAME", Color::White);
}

FloatRect TopTimesScreen::getMainMenuButton() const
{
    return m_MainMenuButton.getButton();
}

FloatRect TopTimesScreen::getResetTimesButton() const
{
    return m_ResetTimesButton.getButton();
}

void TopTimesScreen::setTimesText()
{
    string times[5];

    for (int i = 0; i < m_TopTimes.size(); i++)
    {
        times[i] = convertTimeToString(m_TopTimes[i]);
    }
    std::stringstream timesStream;
    timesStream <<
        "\n1 - " << times[0] <<
        "\n2 - " << times[1] <<
        "\n3 - " << times[2] <<
        "\n4 - " << times[3] <<
        "\n5 - " << times[4];

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
    vector<int> defaultTimes = { 300, 600, 900, 1200, 1500 }; // seconds
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
    m_Title.draw(window);
    window.draw(m_TimesText);
    m_MainMenuButton.draw(window);
    m_ResetTimesButton.draw(window);
    m_QuitButton.draw(window);
}
