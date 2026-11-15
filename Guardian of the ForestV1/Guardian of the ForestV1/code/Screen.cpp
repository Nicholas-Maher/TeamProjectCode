#include "Screen.h"

Screen::Screen()
{
	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;
}

FloatRect Screen::getQuitButton() const
{
	return m_QuitButton.getGlobalBounds();
}