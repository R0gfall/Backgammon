#pragma once

#include "GameBaseState.h"

const std::string WINNER_TEXT_PLACEHOLDER = "Game winner is: ";

//Конечное состояние
//Выводит финальный экран
class EndGameState : public GameBaseState
{
public:
	EndGameState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void Draw(Window* window) override;

private:
	void UpdateWinnerText();

	sf::Font _font;

	sf::Text _winnerText;
};

