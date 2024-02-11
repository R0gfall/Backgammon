#include "AIPlayer.h"

AIPlayer::AIPlayer(PlayerOrderType orderType, AiDifficulty difficulty, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board), _difficulty(difficulty)
{
	StateMachine = stateMachine;
	GameBoard = board;
	OrderType = orderType;
	_difficulty = difficulty;

	Debug::LogInfo("AI player was created");
}

void AIPlayer::OnTurnEnter()
{
}

void AIPlayer::OnEndTurnEnter()
{
// через двумерный массив клетками
//Cell* Board::GetCellById(short id)
	//PossibleTurns* _possibleTurns = 0;
	//*_possibleTurns = GameBoard->GetAllPossibleTurns(OrderType);
	Cell* cell[6];
	cell[0] = GameBoard->GetCellById(7);
	cell[1] = GameBoard->GetCellById(8);
	cell[2] = GameBoard->GetCellById(9);
	cell[3] = GameBoard->GetCellById(10);
	cell[4] = GameBoard->GetCellById(11);
	cell[5] = GameBoard->GetCellById(12);
	cell[0]._checks

}

void AIPlayer::OnUpdate()
{
}

void AIPlayer::OnEndUpdate()
{
}

void AIPlayer::OnTurnExit()
{
}
