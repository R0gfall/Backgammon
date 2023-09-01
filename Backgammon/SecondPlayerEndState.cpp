#include "SecondPlayerEndState.h"

SecondPlayerEndState::SecondPlayerEndState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::SecondPlayerEnd)
{
	_font.loadFromFile(FONT_PATH);
	_turnText.setFont(_font);

	_turnText.setCharacterSize(30);
	_turnText.setFillColor(sf::Color::Black);
	_turnText.setPosition(sf::Vector2f(550.f, 10.f));
	_turnText.setString(_turnTextString);

	_hintText.setFont(_font);

	_hintText.setCharacterSize(30);
	_hintText.setFillColor(sf::Color::White);
	_hintText.setPosition(sf::Vector2f(380.f, 720.f));
	_hintText.setString(_hintTextString);
}

void SecondPlayerEndState::Initialize()
{

}

void SecondPlayerEndState::EnterState()
{
	LogEnter();
	Dice::Roll();

	PlayerSecond->OnEndTurnEnter();
}

void SecondPlayerEndState::UpdateState()
{
	PlayerSecond->OnEndUpdate();
}

void SecondPlayerEndState::LeaveState()
{
	GameBoard->ResetTurns();
	PlayerSecond->OnTurnExit();
}

void SecondPlayerEndState::Draw(Window* window)
{
	GameBoard->Draw(window);
	PlayerSecond->Draw(window);
	window->Draw(_turnText);
	window->Draw(_hintText);
	Dice::Draw(window);
}
