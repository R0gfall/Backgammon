#pragma once

#include "GameBaseState.h"

class EndGameState : public GameBaseState
{
public:
	EndGameState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::EndGame)
	{

	}

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void Draw(Window* window) override;
};

