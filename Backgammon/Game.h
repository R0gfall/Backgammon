#pragma once

#include "GlobalDefinitions.h"

#include "Window.h"
#include "Debug.h"
#include "Board.h"
#include "Dice.h"

#include "Input.h"

#include "GameStateMachine.h"
#include "GameBaseState.h"


class Game
{
public:
	Game()
	{
		_window = new Window(GAME_NAME);

		_board = new Board();
		_dice = new Dice();

		_stateMachine = new GameStateMachine(_board);
	}
	~Game()
	{
		delete _dice;
		delete _window;
		delete _board;
		delete _stateMachine;
	}

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

