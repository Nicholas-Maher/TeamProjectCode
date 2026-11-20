#pragma once
#include "Screen.h"

class PauseMenu : public Screen
{

private:
    Text m_Title;

    Button m_ResumeButton;
    Button m_MainMenuButton;

public:
    PauseMenu();

    FloatRect getResumeButton() const;
    FloatRect getMainMenuButton() const;

    void draw(sf::RenderWindow& window) override;
};