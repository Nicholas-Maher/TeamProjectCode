#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>

using namespace std;
using namespace sf;

// a template function for taking in a numeric data type representing seconds and returning a string time in the format -:-- 
// (used by Engine::update() and TopTimesScreen)
template<class T>
String convertTimeToString(T time)
{
	stringstream ssTime;
	String stringTime;

	int minutes = (int)time / 60;
	int seconds = (int)time % 60;

	if (seconds < 10)
	{
		ssTime << minutes << ":0" << seconds;
	}
	else
	{
		ssTime << minutes << ":" << seconds;
	}
	stringTime = ssTime.str();
	return stringTime;
}