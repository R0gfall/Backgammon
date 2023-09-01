#pragma once

#include "GameBaseState.h"

//Ход первого игрока, когда все шашки в доме
class FirstPlayerEndState : public GameBaseState
{
public:
	FirstPlayerEndState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void Draw(Window* window) override;

private:
	sf::Font _font;
	sf::Text _turnText;
	sf::Text _hintText;

	const std::string _turnTextString = "FIRST Player turn END";
	const std::string _hintTextString = "Choose and Press 'C' to remove Check";
};

