#pragma once

#include "IGameStateMachine.h"

#include "InitialState.h"
#include "FirstPlayerState.h"
#include "FirstPlayerEndState.h"
#include "SecondPlayerState.h"
#include "SecondPlayerEndState.h"
#include "EndGameState.h"

//Машина состояний
//Реализует паттерн проектирования "Машина состояний"
//Содержит в себе метод инициализации, переключения и обновления состояний
//При создании создает все состояния
//При инициализации также инициализирует все состояния
class GameStateMachine : public IGameStateMachine
{
public:
	//Конструктор
	GameStateMachine(Board* board);
	//Деструктор
	~GameStateMachine();

	void Initialize(GameStateType initialState);

	void SwitchState(GameStateType nextState) override;

	void Update();
	void Draw(Window* window);

private:
	//Указатель на текущее состояние
	GameBaseState* _curentState;
	
	//Указатели на конкретные состояния
	InitialState* _initialState;
	FirstPlayerState* _firstPlayerState;
	FirstPlayerEndState* _firstPlayerEndState;
	SecondPlayerState* _secondPlayerState;
	SecondPlayerEndState* _secondPlayerEndState;
	EndGameState* _endGameState;
};

