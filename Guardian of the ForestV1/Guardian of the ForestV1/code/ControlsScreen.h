#pragma once
#include "Screen.h"

class ControlsScreen : public Screen
{

private:
	Text m_Title;
	Text m_JumpText;
	Text m_LeftText;
	Text m_RightText;
	Text m_RunText;

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