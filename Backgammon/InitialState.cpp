#include "InitialState.h"

InitialState::InitialState(Board* board, IGameStateMachine* stateMachine) : GameBaseState(board, stateMachine, GameStateType::Initial)
{
	// Default preset Human vs AI
	_playersStatus[0] = 0;
	_playersStatus[1] = 1;

	_playersStatusStrings[0] = "\n\t\tHUMAN";
	_playersStatusStrings[1] = "\n\t\t\tAI";

	_font.loadFromFile(FONT_PATH);

	_startGameText.setFont(_font);
	_firstPlayerText.setFont(_font);
	_firstPlayerHint.setFont(_font);
	_secondPlayerText.setFont(_font);
	_secondPlayerHint.setFont(_font);

	_startGameText.setCharacterSize(40);
	_firstPlayerText.setCharacterSize(20);
	_firstPlayerHint.setCharacterSize(20);
	_secondPlayerText.setCharacterSize(20);
	_secondPlayerHint.setCharacterSize(20);

	_startGameTextPosition = sf::Vector2f(400.f, 600.f);
	_firstPlayerTextPosition = sf::Vector2f(200.f + 80.f, 200.f);
	_firstPlayerHintPosition = sf::Vector2f(200.f, 200.f + 100.f);
	_secondPlayerTextPosition = sf::Vector2f(800.f + 80.f, 200.f);
	_secondPlayerHintPosition = sf::Vector2f(800.f, 200.f + 100.f);

	_startGameText.setPosition(_startGameTextPosition);
	_firstPlayerText.setPosition(_firstPlayerTextPosition);
	_firstPlayerHint.setPosition(_firstPlayerHintPosition);
	_secondPlayerText.setPosition(_secondPlayerTextPosition);
	_secondPlayerHint.setPosition(_secondPlayerHintPosition);

	_startGameText.setString("Press Space to StartGame");
	_firstPlayerHint.setString("Press to choose First Player\n\t\tQ - Human \tW - AI");
	_secondPlayerHint.setString("Press to choose Second Player\n\t\tA - Human \tS - AI");
	UpdatePlayerStatusText();
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
	if (Input::IsKeyDown(Input::Key::Q))
	{
		_playersStatus[0] = 0;
		UpdatePlayerStatusText();
	}
	if (Input::IsKeyDown(Input::Key::W))
	{
		_playersStatus[0] = 1;
		UpdatePlayerStatusText();
	}
	if (Input::IsKeyDown(Input::Key::A))
	{
		_playersStatus[1] = 0;
		UpdatePlayerStatusText();
	}
	if (Input::IsKeyDown(Input::Key::S))
	{
		_playersStatus[1] = 1;
		UpdatePlayerStatusText();
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
		auto firstPlayer = new AIPlayer(PlayerOrderType::FirstPlayer, StateMachine, GameBoard);
		SetFirstPlayer(firstPlayer);
	}

	if (!_playersStatus[1])
	{
		auto secondPlayer = new HumanPlayer(PlayerOrderType::SecondPlayer, StateMachine, GameBoard);
		SetSecondPlayer(secondPlayer);
	}
	else
	{
		auto secondPlayer = new AIPlayer(PlayerOrderType::SecondPlayer, StateMachine, GameBoard);
		SetSecondPlayer(secondPlayer);
	}

	SwitchState(GameStateType::FirstPlayer);
}

void InitialState::UpdatePlayerStatusText()
{
	_firstPlayerText.setString(FIRST_PLAYER_TEXT_PLACEHOLDER + _playersStatusStrings[(short)_playersStatus[0]]);
	_secondPlayerText.setString(SECOND_PLAYER_TEXT_PLACEHOLDER + _playersStatusStrings[(short)_playersStatus[1]]);
}

void InitialState::Draw(Window* window)
{
	window->Draw(_startGameText);
	window->Draw(_firstPlayerText);
	window->Draw(_firstPlayerHint);
	window->Draw(_secondPlayerText);
	window->Draw(_secondPlayerHint);

}
