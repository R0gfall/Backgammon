#pragma once

#include "Board.h"

#include "IGameStateMachine.h"


class IPlayer
{
public:
	IPlayer(PlayerOrderType type, IGameStateMachine* stateMachine, Board* board);

	virtual ~IPlayer()
	{

	}

	virtual void MoveCheck() = 0;

	virtual void OnTurnEnter() = 0;
	virtual void OnEndTurnEnter() = 0;
	virtual void OnUpdate() {}
	virtual void OnEndUpdate() {}
	virtual void OnTurnExit() {}

	virtual void Draw(Window* window);

	void NextTurn();

	bool IsFirstTurnMade() { return GameBoard->IsFirstTurnMade(OrderType); }
	bool IsOnEndStage() { return GameBoard->IsOnEndStage(OrderType); }
	bool IsOnEndStage(PlayerOrderType orderType) { return GameBoard->IsOnEndStage(orderType); }

	//fo testing
	void DebugSetEndStage(bool value);

	short CalculateCellId(short fromId, short turnValue);

	PossibleTurns CalculatePossibleTurns();
	bool IsAnyTurnsPossible() { return !CalculatePossibleTurns().empty(); }

	char GetChecksOut() { return GameBoard->GetChecksOut(OrderType); }

protected:
	Board* GameBoard;
	PlayerOrderType OrderType;
	IGameStateMachine* StateMachine;

private:
	void UpdateChecksOutText();

	sf::Font _font;
	sf::Text _checksOutText;
};

