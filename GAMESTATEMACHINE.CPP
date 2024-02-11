#include "GameStateMachine.h"

GameStateMachine::GameStateMachine(Board* board)
{
	_curentState = nullptr;

	_initialState = new InitialState(board, this);
	_firstPlayerState = new FirstPlayerState(board, this);
	_firstPlayerEndState = new FirstPlayerEndState(board, this);
	_secondPlayerState = new SecondPlayerState(board, this);
	_secondPlayerEndState = new SecondPlayerEndState(board, this);
	_endGameState = new EndGameState(board, this);
}

GameStateMachine::~GameStateMachine()
{
	delete _initialState;
	delete _firstPlayerState;
	delete _firstPlayerEndState;
	delete _secondPlayerState;
	delete _secondPlayerEndState;
	delete _endGameState;
}

void GameStateMachine::Initialize(GameStateType initialState)
{
	_initialState->Initialize();
	_firstPlayerState->Initialize();
	_firstPlayerEndState->Initialize();
	_secondPlayerState->Initialize();
	_secondPlayerEndState->Initialize();
	_endGameState->Initialize();
	SwitchState(initialState);
}

void GameStateMachine::SwitchState(GameStateType nextState)
{
	if (_curentState != nullptr)
	{
		_curentState->LeaveState();
	}

	switch (nextState)
	{
	case GameStateType::Initial:
		_curentState = _initialState;
		break;
	case GameStateType::FirstPlayer:
		_curentState = _firstPlayerState;
		break;
	case GameStateType::FirstPlayerEnd:
		_curentState = _firstPlayerEndState;
		break;
	case GameStateType::SecondPlayer:
		_curentState = _secondPlayerState;
		break;
	case GameStateType::SecondPlayerEnd:
		_curentState = _secondPlayerEndState;
		break;
	case GameStateType::EndGame:
		_curentState = _endGameState;
		break;
	}

	_curentState->EnterState();
}

void GameStateMachine::Update()
{
	_curentState->UpdateState();
}

void GameStateMachine::Draw(Window* window)
{
	_curentState->Draw(window);
}
