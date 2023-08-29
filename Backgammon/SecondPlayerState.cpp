#include "SecondPlayerState.h"

SecondPlayerState::SecondPlayerState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::SecondPlayer)
{
	_font.loadFromFile(FONT_PATH);
	_turnText.setFont(_font);

	_turnText.setCharacterSize(30);
	_turnText.setFillColor(sf::Color::Black);
	_turnText.setPosition(sf::Vector2f(550.f, 10.f));
	_turnText.setString(_turnTextString);
}

void SecondPlayerState::Initialize()
{
}

void SecondPlayerState::EnterState()
{
	LogEnter();
	Dice::Roll();

	PlayerSecond->OnTurnEnter();
}

void SecondPlayerState::UpdateState()
{
	PlayerSecond->OnUpdate();
}

void SecondPlayerState::LeaveState()
{
	GameBoard->ResetTurns();
	PlayerSecond->OnTurnExit();
}

void SecondPlayerState::Draw(Window* window)
{
	GameBoard->Draw(window);
	window->Draw(_turnText);
	Dice::Draw(window);
}
