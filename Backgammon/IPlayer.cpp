#include "IPlayer.h"

IPlayer::IPlayer(PlayerOrderType type, IGameStateMachine* stateMachine, Board* board)
{
	StateMachine = stateMachine;
	GameBoard = board;
	OrderType = type;

	_font.loadFromFile(FONT_PATH);

	_checksOutText.setFont(_font);
	_checksOutText.setCharacterSize(20);
	_checksOutText.setFillColor(sf::Color::Black);
	UpdateChecksOutText();

	_checksOutText.setPosition(sf::Vector2f(1200.f, 10.f));
}

void IPlayer::Draw(Window* window)
{
	UpdateChecksOutText();
	window->Draw(_checksOutText);
}

void IPlayer::NextTurn()
{
	if (!IsFirstTurnMade())
	{
		GameBoard->SetFirstTurnMade(OrderType);
	}

	if (GameBoard->IsGameEnded())
	{
		StateMachine->SwitchState(GameStateType::EndGame);
		return;
	}

	switch (OrderType)
	{
	case PlayerOrderType::FirstPlayer:
		if (IsOnEndStage(PlayerOrderType::SecondPlayer))
		{
			StateMachine->SwitchState(GameStateType::SecondPlayerEnd);
		}
		else
		{
			StateMachine->SwitchState(GameStateType::SecondPlayer);
		}
		break;
	case PlayerOrderType::SecondPlayer:
		if (IsOnEndStage(PlayerOrderType::FirstPlayer))
		{
			StateMachine->SwitchState(GameStateType::FirstPlayerEnd);
		}
		else
		{
			StateMachine->SwitchState(GameStateType::FirstPlayer);
		}
		break;
	}
}

void IPlayer::DebugSetEndStage(bool value)
{
	GameBoard->SetOnEndStage(OrderType, value);
	Debug::LogWarning("End stage flag set to " + std::to_string(value));
}

short IPlayer::CalculateCellId(short fromId, short turnValue)
{
	return GameBoard->CalculateCellId(fromId, turnValue);
}

PossibleTurns IPlayer::CalculatePossibleTurns()
{
	return GameBoard->GetAllPossibleTurns(OrderType);
}

void IPlayer::UpdateChecksOutText()
{
	_checksOutText.setString(CHECKS_OUT_PLACEHOLDER + std::to_string(GetChecksOut()));
}
