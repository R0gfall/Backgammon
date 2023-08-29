#pragma once

#include "IPlayer.h"

#include "Debug.h"

#include "Input.h"
#include "Mouse.h"

#include "Dice.h"

class HumanPlayer : public IPlayer
{
public:
	HumanPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board)
	{
		Debug::LogInfo("Human player was created");
	}

	void MoveCheck() override;

	void OnTurnEnter() override;

	void OnEndTurnEnter() override;

	void OnUpdate() override;

	void OnEndUpdate() override;

	void OnTurnExit() override;

	void HandleMouseClick();

	void HandleCheckMove(Cell* targetCell);
	void MoveCheck(short fromId, short toId);
	
	void RemoveCheck();

	void ChooseCell(Cell* cell);
	void CancelCellChoise();
	bool IsCellCanBeChosen(Cell* cell);

	void ShowPossibleTurns();

	bool IsCellChosen() { return _chosenCell != nullptr; }

private:
	void HandleInput();

	Cell* _chosenCell = nullptr;

	short _firstPossibleCellId = -1;
	short _secondPossibleCellId = -1;

	short _lastPerformedTurn = -1;

	short _performedTurns = 0;

	bool _debugEndMode = false;
};

