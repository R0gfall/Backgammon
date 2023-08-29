#include "IPlayer.h"

IPlayer::IPlayer(PlayerOrderType type, IGameStateMachine* stateMachine, Board* board)
{
	StateMachine = stateMachine;
	GameBoard = board;
	OrderType = type;
}

void IPlayer::NextTurn()
{
	if (!IsFirstTurnMade())
	{
		GameBoard->SetFirstTurnMade(OrderType);
	}

	switch (OrderType)
	{
	case PlayerOrderType::FirstPlayer:
		if (IsOnEndStage(PlayerOrderType::SecondPlayer))
		{
			StateMachine->SwitchState(GameStateType::SecondPlayerEnd);
		}
		else
		{
			StateMachine->SwitchState(GameStateType::SecondPlayer);
		}
		break;
	case PlayerOrderType::SecondPlayer:
		if (IsOnEndStage(PlayerOrderType::FirstPlayer))
		{
			StateMachine->SwitchState(GameStateType::FirstPlayerEnd);
		}
		else
		{
			StateMachine->SwitchState(GameStateType::FirstPlayer);
		}
		break;
	}
}

void IPlayer::DebugSetEndStage(bool value)
{
	GameBoard->SetOnEndStage(OrderType, value);
	Debug::LogWarning("End stage flag set to " + std::to_string(value));
}

short IPlayer::CalculateCellId(short fromId, short turnValue)
{
	return GameBoard->CalculateCellId(fromId, turnValue);
}

PossibleTurns IPlayer::CalculatePossibleTurns()
{
	return GameBoard->GetAllPossibleTurns(OrderType);
}
