#include "AIPlayer.h"

AIPlayer::AIPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board)
{
	Debug::LogInfo("AI player was created");
}

void AIPlayer::OnTurnEnter()
{
}

void AIPlayer::OnEndTurnEnter()
{
}

void AIPlayer::OnUpdate()
{
}

void AIPlayer::OnEndUpdate()
{
}

void AIPlayer::OnTurnExit()
{
}
