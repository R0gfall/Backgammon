#include "InitialState.h"

InitialState::InitialState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::Initial)
{
	// Default preset Human vs AI
	_playersStatus[0] = 0;
	_playersStatus[1] = 1;

	// Default preset AI difficulty
	_playerDifficulty[0] = AiDifficulty::Easy;
	_playerDifficulty[1] = AiDifficulty::Easy;

	_playersStatusStrings[0] = "\n\t\tHUMAN";
	_playersStatusStrings[1] = "\n\t\t\tAI";

	_font.loadFromFile(FONT_PATH);

	//Установка шрифта
	_startGameText.setFont(_font);

	_firstPlayerText.setFont(_font);
	_firstPlayerHint.setFont(_font);
	_firstPlayerDifficulty.setFont(_font);
	_firstPlayerDifficultyHint.setFont(_font);

	_secondPlayerText.setFont(_font);
	_secondPlayerHint.setFont(_font);
	_secondPlayerDifficulty.setFont(_font);
	_secondPlayerDifficultyHint.setFont(_font);

	//Размер шрифта
	_startGameText.setCharacterSize(40);

	_firstPlayerText.setCharacterSize(20);
	_firstPlayerHint.setCharacterSize(20);
	_firstPlayerDifficulty.setCharacterSize(20);
	_firstPlayerDifficultyHint.setCharacterSize(20);

	_secondPlayerText.setCharacterSize(20);
	_secondPlayerHint.setCharacterSize(20);
	_secondPlayerDifficulty.setCharacterSize(20);
	_secondPlayerDifficultyHint.setCharacterSize(20);

	//Позиция текста
	_startGameTextPosition = sf::Vector2f(400.f, 600.f);

	_firstPlayerTextPosition = sf::Vector2f(200.f + 80.f, 200.f);
	_firstPlayerHintPosition = sf::Vector2f(200.f, 200.f + 100.f);
	_firstPlayerDifficultyPosition = sf::Vector2f(200.f + 50.f, 200.f + 100.f + 80.f);
	_firstPlayerDifficultyHintPosition = sf::Vector2f(200.f, 200.f + 100.f + 80.f + 50.f);

	_secondPlayerTextPosition = sf::Vector2f(800.f + 80.f, 200.f);
	_secondPlayerHintPosition = sf::Vector2f(800.f, 200.f + 100.f);
	_secondPlayerDifficultyPosition = sf::Vector2f(800.f + 50.f, 200.f + 100.f + 80.f);
	_secondPlayerDifficultyHintPosition = sf::Vector2f(800.f, 200.f + 100.f + 80.f + 50.f);

	//Установка позиции текста
	_startGameText.setPosition(_startGameTextPosition);

	_firstPlayerText.setPosition(_firstPlayerTextPosition);
	_firstPlayerHint.setPosition(_firstPlayerHintPosition);
	_firstPlayerDifficulty.setPosition(_firstPlayerDifficultyPosition);
	_firstPlayerDifficultyHint.setPosition(_firstPlayerDifficultyHintPosition);

	_secondPlayerText.setPosition(_secondPlayerTextPosition);
	_secondPlayerHint.setPosition(_secondPlayerHintPosition);
	_secondPlayerDifficulty.setPosition(_secondPlayerDifficultyPosition);
	_secondPlayerDifficultyHint.setPosition(_secondPlayerDifficultyHintPosition);

	//Установка текста
	_startGameText.setString("Press Space to StartGame");
	_firstPlayerHint.setString("Press to choose First Player\n\t\tQ - Human \tW - AI");
	_firstPlayerDifficultyHint.setString("\tPress to choose Difficulty\n\t\tE - EASY \tR - HARD");
	_secondPlayerHint.setString("Press to choose Second Player\n\t\tA - Human \tS - AI");
	_secondPlayerDifficultyHint.setString("\tPress to choose Difficulty\n\t\tD - EASY \tF - HARD");
	UpdateText();
}

void InitialState::Initialize()
{
}

void InitialState::EnterState()
{
	LogEnter();
}

void InitialState::UpdateState()
{
	if (Input::IsKeyDown(Input::Key::Space))
	{
		StartGame();
	}
	
	//First player status
	if (Input::IsKeyDown(Input::Key::Q))
	{
		_playersStatus[0] = 0;
		UpdateText();
	}
	if (Input::IsKeyDown(Input::Key::W))
	{
		_playersStatus[0] = 1;
		UpdateText();
	}
	//First player ai difficulty
	if (Input::IsKeyDown(Input::Key::E))
	{
		_playerDifficulty[0] = AiDifficulty::Easy;
		UpdateText();
	}
	if (Input::IsKeyDown(Input::Key::R))
	{
		_playerDifficulty[0] = AiDifficulty::Hard;
		UpdateText();
	}


	//Second player status
	if (Input::IsKeyDown(Input::Key::A))
	{
		_playersStatus[1] = 0;
		UpdateText();
	}
	if (Input::IsKeyDown(Input::Key::S))
	{
		_playersStatus[1] = 1;
		UpdateText();
	}
	//Second player ai difficulty
	if (Input::IsKeyDown(Input::Key::D))
	{
		_playerDifficulty[1] = AiDifficulty::Easy;
		UpdateText();
	}
	if (Input::IsKeyDown(Input::Key::F))
	{
		_playerDifficulty[1] = AiDifficulty::Hard;
		UpdateText();
	}
}

void InitialState::LeaveState()
{
}

void InitialState::StartGame()
{
	if (!_playersStatus[0])
	{
		auto firstPlayer = new HumanPlayer(PlayerOrderType::FirstPlayer, StateMachine, GameBoard);
		SetFirstPlayer(firstPlayer);
	}
	else
	{
		auto firstPlayer = new AIPlayer(PlayerOrderType::FirstPlayer, _playerDifficulty[0], StateMachine, GameBoard);
		SetFirstPlayer(firstPlayer);
	}

	if (!_playersStatus[1])
	{
		auto secondPlayer = new HumanPlayer(PlayerOrderType::SecondPlayer, StateMachine, GameBoard);
		SetSecondPlayer(secondPlayer);
	}
	else
	{
		auto secondPlayer = new AIPlayer(PlayerOrderType::SecondPlayer, _playerDifficulty[1], StateMachine, GameBoard);
		SetSecondPlayer(secondPlayer);
	}

	SwitchState(GameStateType::FirstPlayer);
}

void InitialState::UpdateText()
{
	_firstPlayerText.setString(FIRST_PLAYER_TEXT_PLACEHOLDER + _playersStatusStrings[(short)_playersStatus[0]]);
	_secondPlayerText.setString(SECOND_PLAYER_TEXT_PLACEHOLDER + _playersStatusStrings[(short)_playersStatus[1]]);

	_firstPlayerDifficulty.setString(DIFFICULTY_TEXT_PLACEHOLDER + AI_DIFFICULTY_STRINGS[(short)_playerDifficulty[0]]);
	_secondPlayerDifficulty.setString(DIFFICULTY_TEXT_PLACEHOLDER + AI_DIFFICULTY_STRINGS[(short)_playerDifficulty[1]]);
}

void InitialState::Draw(Window* window)
{
	window->Draw(_startGameText);

	window->Draw(_firstPlayerText);
	window->Draw(_firstPlayerHint);

	if (_playersStatus[0] == 1)
	{
		window->Draw(_firstPlayerDifficulty);
		window->Draw(_firstPlayerDifficultyHint);
	}


	window->Draw(_secondPlayerText);
	window->Draw(_secondPlayerHint);

	if (_playersStatus[1] == 1)
	{
		window->Draw(_secondPlayerDifficulty);
		window->Draw(_secondPlayerDifficultyHint);
	}

}
