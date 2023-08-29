#include "Game.h"

void Game::Initialize()
{
	_board->Initialize();
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
