#pragma once

#include "GameBaseState.h"

class SecondPlayerEndState : public GameBaseState
{
public:
	SecondPlayerEndState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void Draw(Window* window) override;

private:
	sf::Font _font;
	sf::Text _turnText;
	sf::Text _hintText;

	const std::string _turnTextString = "Second Player Turn END";
	const std::string _hintTextString = "Choose check to remove";
};

