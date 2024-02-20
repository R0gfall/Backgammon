#include "EndGameState.h"

EndGameState::EndGameState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::EndGame)
{
	_font.loadFromFile(FONT_PATH);

	_winnerText.setFont(_font);
	_winnerText.setCharacterSize(30);
	_winnerText.setFillColor(sf::Color::White);
	_winnerText.setPosition(sf::Vector2f(500.f, 350.f));
	UpdateWinnerText();
}

void EndGameState::Initialize()
{
}

void EndGameState::EnterState()
{
	LogEnter();
	UpdateWinnerText();
}

void EndGameState::UpdateState()
{
}

void EndGameState::LeaveState()
{
}

void EndGameState::Draw(Window* window)
{
	window->Draw(_winnerText);
}

void EndGameState::UpdateWinnerText()
{
	_winnerText.setString(WINNER_TEXT_PLACEHOLDER + PLAYER_ORDER_TYPE_STRINGS[(char)GameBoard->GetWinner()]);
}
