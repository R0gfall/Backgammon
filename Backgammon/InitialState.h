#pragma once

#include "GameBaseState.h"

#include "AIPlayer.h"
#include "HumanPlayer.h"

#include "Input.h"

const std::string FIRST_PLAYER_TEXT_PLACEHOLDER = "First Player is: ";
const std::string SECOND_PLAYER_TEXT_PLACEHOLDER = "Second Player is: ";
const std::string DIFFICULTY_TEXT_PLACEHOLDER = "AI difficulty is: ";

//Начальное состояние
//Содержит в себе логику выбора противников
class InitialState : public GameBaseState
{
public:
	InitialState(Board* board, IGameStateMachine* stateMachine);

	void Initialize() override;

	void EnterState() override;
	void UpdateState() override;
	void LeaveState() override;

	void StartGame();

	void UpdateText();

	void Draw(Window* window) override;

private:
	sf::Font _font;

	sf::Text _startGameText;
	sf::Text _firstPlayerText;
	sf::Text _firstPlayerHint;
	sf::Text _firstPlayerDifficulty;
	sf::Text _firstPlayerDifficultyHint;
	sf::Text _secondPlayerText;
	sf::Text _secondPlayerHint;
	sf::Text _secondPlayerDifficulty;
	sf::Text _secondPlayerDifficultyHint;

	sf::Vector2f _startGameTextPosition;
	sf::Vector2f _firstPlayerTextPosition;
	sf::Vector2f _firstPlayerHintPosition;
	sf::Vector2f _firstPlayerDifficultyPosition;
	sf::Vector2f _firstPlayerDifficultyHintPosition;
	sf::Vector2f _secondPlayerTextPosition;
	sf::Vector2f _secondPlayerHintPosition;
	sf::Vector2f _secondPlayerDifficultyPosition;
	sf::Vector2f _secondPlayerDifficultyHintPosition;

	bool _playersStatus[2]; // 0(false) - Human, 1(true) - AI
	AiDifficulty _playerDifficulty[2];

	std::string _playersStatusStrings[2];
};

