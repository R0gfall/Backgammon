#include "FirstPlayerEndState.h"

FirstPlayerEndState::FirstPlayerEndState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::FirstPlayerEnd)
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
	_hintText.setPosition(sf::Vector2f(480.f, 720.f));
	_hintText.setString(_hintTextString);
}

void FirstPlayerEndState::Initialize()
{

}

void FirstPlayerEndState::EnterState()
{
	LogEnter();
	Dice::Roll();

	PlayerFirst->OnEndTurnEnter();
}

void FirstPlayerEndState::UpdateState()
{
	PlayerFirst->OnEndUpdate();
}

void FirstPlayerEndState::LeaveState()
{
	GameBoard->ResetTurns();
	PlayerFirst->OnTurnExit();
}

void FirstPlayerEndState::Draw(Window* window)
{
	GameBoard->Draw(window);
	PlayerFirst->Draw(window);
	window->Draw(_turnText);
	Dice::Draw(window);
}
