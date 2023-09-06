#include "AIPlayer.h"

AIPlayer::AIPlayer(PlayerOrderType orderType, AiDifficulty difficulty, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board), _difficulty(difficulty)
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
