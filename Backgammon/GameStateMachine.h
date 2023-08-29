#pragma once

#include "IGameStateMachine.h"

#include "InitialState.h"
#include "FirstPlayerState.h"
#include "FirstPlayerEndState.h"
#include "SecondPlayerState.h"
#include "SecondPlayerEndState.h"
#include "EndGameState.h"

class GameStateMachine : public IGameStateMachine
{
public:
	GameStateMachine(Board* board);

	~GameStateMachine();

	void Initialize(GameStateType initialState);

	void SwitchState(GameStateType nextState) override;

	void Update();
	void Draw(Window* window);

private:
	GameBaseState* _curentState;
	
	InitialState* _initialState;
	FirstPlayerState* _firstPlayerState;
	FirstPlayerEndState* _firstPlayerEndState;
	SecondPlayerState* _secondPlayerState;
	SecondPlayerEndState* _secondPlayerEndState;
	EndGameState* _endGameState;
};

