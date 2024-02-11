#pragma once

#include "GameBaseState.h"

//’од первого игрока, когда не все шашки в доме
class FirstPlayerState : public GameBaseState
{
public:
	FirstPlayerState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void Draw(Window* window) override;

private:
	sf::Font _font;
	sf::Text _turnText;

	const std::string _turnTextString = "FIRST Player turn";
};

