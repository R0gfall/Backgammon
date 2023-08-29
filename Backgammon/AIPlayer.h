#pragma once

#include "IPlayer.h"

#include "Debug.h"

class AIPlayer : public IPlayer
{
public:
	AIPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board)
	{
		Debug::LogInfo("AI player was created");
	}

	void MoveCheck() override;

	void OnTurnEnter() override;

	void OnEndTurnEnter() override;

private:

};

