#include "FirstPlayerState.h"

FirstPlayerState::FirstPlayerState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::FirstPlayer)
{
	_font.loadFromFile(FONT_PATH);
	_turnText.setFont(_font);

	_turnText.setCharacterSize(30);
	_turnText.setFillColor(sf::Color::Black);
	_turnText.setPosition(sf::Vector2f(550.f, 10.f));
	_turnText.setString(_turnTextString);
}

void FirstPlayerState::Initialize()
{
}

void FirstPlayerState::EnterState()
{
	LogEnter();
	Dice::Roll();

	PlayerFirst->OnTurnEnter();
}

void FirstPlayerState::UpdateState()
{
	PlayerFirst->OnUpdate();
}

void FirstPlayerState::LeaveState()
{
	LogLeave();
	GameBoard->ResetTurns();
	PlayerFirst->OnTurnExit();
}

void FirstPlayerState::Draw(Window* window)
{
	GameBoard->Draw(window);
	PlayerFirst->Draw(window);
	window->Draw(_turnText);
	Dice::Draw(window);
}
