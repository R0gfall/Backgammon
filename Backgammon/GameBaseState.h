#pragma once

#include "IGameStateMachine.h"
#include "Window.h"
#include "Debug.h"
#include "GlobalDefinitions.h"
#include "Board.h"


#include "Dice.h"
#include "IPlayer.h"

class GameBaseState
{
public:
	GameBaseState(Board* board, IGameStateMachine* stateMachine, GameStateType stateType)
	{
		StateMachine = stateMachine;
		GameBoard = board;
		_stateType = stateType;	
	}
	virtual ~GameBaseState()
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

	virtual void Initialize() = 0;

	virtual void EnterState() = 0;
	virtual void UpdateState() = 0;
	virtual void LeaveState() = 0;

	virtual void Draw(Window* window) = 0;

	void SwitchState(GameStateType nextState)
	{
		StateMachine->SwitchState(nextState);
	}

	GameStateType GetPlayerType() { return _stateType; }

	void LogEnter()
	{
		Debug::LogInfo("Entered " + GAME_STATE_STRINGS[(int)_stateType]);
	}

	void SetFirstPlayer(IPlayer* player) { PlayerFirst = player; }
	void SetSecondPlayer(IPlayer* player) { PlayerSecond = player; }

protected: 
	IGameStateMachine* StateMachine;
	Board* GameBoard;

	static IPlayer* PlayerFirst;
	static IPlayer* PlayerSecond;

private:
	GameStateType _stateType;
};

