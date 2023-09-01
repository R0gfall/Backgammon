#include "GameBaseState.h"

IPlayer* GameBaseState::PlayerFirst = nullptr;
IPlayer* GameBaseState::PlayerSecond = nullptr;

GameBaseState::GameBaseState(Board* board, IGameStateMachine* stateMachine, GameStateType stateType)
{
	StateMachine = stateMachine;
	GameBoard = board;
	_stateType = stateType;
}

GameBaseState::~GameBaseState()
{
	if (PlayerFirst != nullptr)
	{
		delete PlayerFirst;
		PlayerFirst = nullptr;
		Debug::LogWarning("Destroyed PlayerFirst ptr");
	}
	if (PlayerSecond != nullptr)
	{
		delete PlayerSecond;
		PlayerSecond = nullptr;
		Debug::LogWarning("Destroyed PlayerSecond ptr");
	}
}
