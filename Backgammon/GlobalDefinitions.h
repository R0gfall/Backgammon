#pragma once

#include <string>

#include <map>
#include <list>

#define GAME_NAME "Backgammon"

#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768
//#define WINDOW_WIDTH 1920
//#define WINDOW_HEIGHT 1080

#define BOARD_IMAGE_PATH "../Assets/board.png"
#define DICE_IMAGE_PATH "../Assets/dice.png"
#define FONT_PATH "../Assets/Montserrat-Black.ttf"
#define CHECK_IMAGE_PATH "../Assets/checks.png"

enum class GameStateType
{
	Initial,
	FirstPlayer,
	FirstPlayerEnd,
	SecondPlayer,
	SecondPlayerEnd,
	EndGame
};

enum class PlayerOrderType
{
	FirstPlayer,
	SecondPlayer
};

enum class CellStatus
{
	FirstPlayer,
	SecondPlayer,
	Free,
};

enum class CellType
{
	None,
	FirstPlayerHead,
	FirstPlayerHome,
	SecondPlayerHead,
	SecondPlayerHome,
};

enum class CheckType
{
	FirstPlayer,
	SecondPlayer,
	Hint
};

const std::string GAME_STATE_STRINGS[6] = { "INITIAL_STATE", "FIRST_PLAYER_STATE", "FIRST_PLAYER_END_STATE", "SECOND_PLAYER_STATE", "SECOND_PLAYER_END_STATE", "END_GAME_STATE" };

const GameStateType GAME_INITIAL_STATE = GameStateType::Initial;


using PossibleTurns = std::map<short, std::list<short>>;

/// <summary>
/// 
/// </summary>
/// <param name="valueToClamp">провер€емое число</param>
/// <param name="bottomBorder">нижн€€ граница включительно</param>
/// <param name="topBorder">верхн€€ граница не включительно</param>
/// <returns></returns>
bool IsValueInBounds(short valueToClamp, short bottomBorder, short topBorder);