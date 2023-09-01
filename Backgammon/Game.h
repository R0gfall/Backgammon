#pragma once

#include "GlobalDefinitions.h"

#include "Window.h"
#include "Debug.h"
#include "Board.h"
#include "Dice.h"

#include "Input.h"

#include "GameStateMachine.h"
#include "GameBaseState.h"

//Класс игры
//Содержит методы для основного игрового цикла: инициализация, обновление и отрисовка
//Создает все управляющие личности
class Game
{
public:
	//Конструктор
	Game();
	//Деструктор
	~Game();

	void Initialize();
	void Update();
	void Draw();

	bool IsOpened();

private:
	Window* _window;

	Board* _board;
	Dice* _dice;

	GameStateMachine* _stateMachine;
};

