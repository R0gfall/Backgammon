#include "Game.h"

Game::Game()
{
	
	_window = new Window(GAME_NAME);

	Debug::Initialize(_window, LOG_OUTPUT_FILENAME);

	_board = new Board();
	_dice = new Dice();

	_stateMachine = new GameStateMachine(_board);
}

Game::~Game()
{
	delete _dice;

	delete _board;
	delete _stateMachine;

	delete _window;

	Debug::Destroy();
}

void Game::Initialize()
{
	_board->Initialize(_stateMachine);
	_dice->Initialize();

	_stateMachine->Initialize(GAME_INITIAL_STATE);

}

void Game::Update()
{
	_window->Update();

	Input::Update();
	Mouse::Update();

	_stateMachine->Update();
}

void Game::Draw()
{
	_window->BeginDraw();
	
	_stateMachine->Draw(_window);

	_window->EndDraw();
}

bool Game::IsOpened()
{
	return _window->IsOpen();
}
