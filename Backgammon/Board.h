#pragma once

#include <SFML/Graphics.hpp>

#include "GlobalDefinitions.h"
#include "Window.h"
#include "Cell.h"

#include "Debug.h"

#include "Dice.h"

const int CELLS_AMOUNT = 24;

const short FIRST_PLAYER_HEAD_CELL_ID = 0;
const short SECOND_PLAYER_HEAD_CELL_ID = 12;

const std::string CHECKS_OUT_PLACEHOLDER = "Checks out: ";

class Board
{
public:
	Board();
	~Board();

	void Initialize();
	void Update();
	void Draw(Window* window);

	Cell* GetCellByPosition(sf::Vector2f position);
	Cell* GetCellById(short id);

	void MoveCheck(short idFrom, short idTo);
	bool IsMoveCheckPossible(short idFrom, short idTo);

	//End Game
	void RemoveCheck(short idFrom);
	bool IsRemoveCheckPossible(short idFrom);

	bool IsCorrectId(short id);

	void HideHints();

	static short CalculateDeltaId(short fromId, short toId);
	static short CalculateCellId(short fromId, short turnValue);
	void ResetTurns();

	PossibleTurns GetAllPossibleTurns(PlayerOrderType orderType);

	void SetFirstTurnMade(PlayerOrderType orderType);
	bool IsFirstTurnMade(PlayerOrderType orderType);

	void SetOnEndStage(PlayerOrderType orderType);
	void SetOnEndStage(PlayerOrderType orderType, bool value);
	bool IsOnEndStage(PlayerOrderType orderType);

private:
	bool IsTurnOverlaping(PlayerOrderType orderType, short fromId, short toId);

	bool IsFirstTurnPossible(PlayerOrderType orderType, short fromHeadTurns);

	void AddToPossibleTurns(short fromCellId, short toCellId);

	short GetCellIdByLocalPosition(sf::Vector2f localPosition);

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;

	sf::Font _font;
	sf::Text _firstPlayerChecksOutText;
	sf::Text _secondPlayerChecksOutText;

	sf::Vector2f _leftOffset;

	Cell* _cells[CELLS_AMOUNT];

	//значение кости на который последний раз передвинулась шашка
	short _lastPerformedTurn = -1;

	PossibleTurns* _possibleTurns;

	bool _firstPlayerFirstTurnMade = false;
	bool _secondPlayerFirstTurnMade = false;

	char _firstPlayerFromHeadTurns = 0;
	char _secondPlayerFromHeadTurns = 0;

	bool _firstPlayerOnEndStage = false;
	bool _secondPlayerOnEndStage = false;

	char _firstPlayerChecksOut = 0;
	char _secondPlayerChecksOut = 0;
};

