#pragma once

#include "GameBaseState.h"

//’од второго игрока, когда не все шашки в доме
class SecondPlayerState : public GameBaseState
{
public:
	SecondPlayerState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void Draw(Window* window) override;

private:
	sf::Font _font;
	sf::Text _turnText;

	const std::string _turnTextString = "SECOND Player turn";
};

