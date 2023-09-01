#pragma once

#include "IGameStateMachine.h"
#include "Window.h"
#include "Debug.h"
#include "GlobalDefinitions.h"
#include "Board.h"

#include "Dice.h"
#include "IPlayer.h"

//Базовый класс для состояний
class GameBaseState
{
public:
	//Конструктор
	GameBaseState(Board* board, IGameStateMachine* stateMachine, GameStateType stateType);
	//Деструктор
	virtual ~GameBaseState();

	//Метод инициализации, вызывается 1 раз для инициализации состояния
	virtual void Initialize() = 0;

	//Метод, который вызывается при активации состояния
	virtual void EnterState() = 0;
	//Метод, который вызывается каждый кадр при активном состоянии
	virtual void UpdateState() = 0;
	//Метод, который вызывается при деактивации состояния
	virtual void LeaveState() = 0;

	virtual void Draw(Window* window) = 0;

	//Метод для переключения состояний
	void SwitchState(GameStateType nextState) { StateMachine->SwitchState(nextState); }

	//Метод для вывода в консоль при входе в состояние
	void LogEnter() { Debug::LogInfo("Entered " + GAME_STATE_STRINGS[(int)_stateType]); }

	//Инициализация указателя на первого игрока
	void SetFirstPlayer(IPlayer* player) { PlayerFirst = player; }
	//Инициализация указателя на второго игрока
	void SetSecondPlayer(IPlayer* player) { PlayerSecond = player; }

protected:
	//Указатель на интерфейс машины состояний (нужно для переключения состояний)
	IGameStateMachine* StateMachine;
	//Указатель на доску
	Board* GameBoard;

	//Указатель на первого игрока
	static IPlayer* PlayerFirst;
	//Указатель на второго игрока
	static IPlayer* PlayerSecond;

private:
	//Тип состояний
	GameStateType _stateType;
};

