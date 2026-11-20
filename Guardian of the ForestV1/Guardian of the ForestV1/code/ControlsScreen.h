#pragma once
#include "Screen.h"

class ControlsScreen : public Screen
{

private:
	TextBlock m_Title;
	TextBlock m_JumpText;
	TextBlock m_LeftText;
	TextBlock m_RightText;
	TextBlock m_RunText;

	Button m_JumpButton;
	Button m_MoveLeftButton;
	Button m_MoveRightButton;
	Button m_RunButton;
	Button m_ResetButton;
	Button m_MenuMenuButton;

public:
	ControlsScreen();

	FloatRect getJumpButton() const;
	FloatRect getMoveLeftButton() const;
	FloatRect getMoveRightButton() const;
	FloatRect getRunButton() const;
	FloatRect getResetButton() const;
	FloatRect getMainMenuButton() const;

	void setJumpButtonText(String text);
	void setMoveLeftButtonText(String text);
	void setMoveRightButtonText(String text);
	void setRunButtonText(String text);

	void draw(sf::RenderWindow& window) override;
};