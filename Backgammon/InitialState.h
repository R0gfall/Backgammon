#pragma once

#include "GameBaseState.h"

#include "AIPlayer.h"
#include "HumanPlayer.h"

#include "Input.h"

const std::string FIRST_PLAYER_TEXT_PLACEHOLDER = "First Player is: ";
const std::string SECOND_PLAYER_TEXT_PLACEHOLDER = "Second Player is: ";

class InitialState : public GameBaseState
{
public:
	InitialState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void StartGame();

	void UpdatePlayerStatusText();

	void Draw(Window* window) override;

private:
	sf::Font _font;

	sf::Text _startGameText;
	sf::Text _firstPlayerText;
	sf::Text _firstPlayerHint;
	sf::Text _secondPlayerText;
	sf::Text _secondPlayerHint;

	sf::Vector2f _startGameTextPosition;
	sf::Vector2f _firstPlayerTextPosition;
	sf::Vector2f _firstPlayerHintPosition;
	sf::Vector2f _secondPlayerTextPosition;
	sf::Vector2f _secondPlayerHintPosition;

	bool _playersStatus[2]; // 0 - Human, 1 - AI
	std::string _playersStatusStrings[2];
};

