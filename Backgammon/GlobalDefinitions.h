#pragma once

#include <string>

#include <map>
#include <list>

//Название окна
#define GAME_NAME "Backgammon"

//Размеры окна в пикселях
#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

//Пути к файлам
#define BOARD_IMAGE_PATH "../Assets/board.png"
#define DICE_IMAGE_PATH "../Assets/dice.png"
#define FONT_PATH "../Assets/Montserrat-Black.ttf"
#define CHECK_IMAGE_PATH "../Assets/checks.png"

//Перечисление типов состояний
enum class GameStateType
{
	Initial,
	FirstPlayer,
	FirstPlayerEnd,
	SecondPlayer,
	SecondPlayerEnd,
	EndGame
};

//Массив строк, соответствующий перечислению GameStateType
const std::string GAME_STATE_STRINGS[6] = { "INITIAL_STATE", "FIRST_PLAYER_STATE", "FIRST_PLAYER_END_STATE", "SECOND_PLAYER_STATE", "SECOND_PLAYER_END_STATE", "END_GAME_STATE" };

//Перечисление типов очередности ходов
enum class PlayerOrderType
{
	//Первый игрок
	FirstPlayer,
	//Второй игрок
	SecondPlayer,
	None,
};

//Массив строк, соответствующий перечислению PlayerOrderType
const std::string PLAYER_ORDER_TYPE_STRINGS[3] = { "NONE", "FIRST PLAYER", "SECOND PLAYER" };

//Перечисление сложности ИИ
enum class AiDifficulty
{
	Easy,
	Medium,
	Hard
};

//Массив строк, соответствующий перечислению AiDifficulty
const std::string AI_DIFFICULTY_STRINGS[3] = { "EASY", "MEDIUM", "HARD" };

//Перечисление состояний клетки
enum class CellStatus
{
	//Клетка занята первым игроком
	FirstPlayer,
	//Клетка занята вторым игроком
	SecondPlayer,
	//Клетка свободна
	Free,
};

//Перечисление типов клетки
enum class CellType
{
	None,
	//Голова первого игрока (клетка с id 0)
	FirstPlayerHead,
	//Дом первого игрока (клетки с id от 18 до 23)
	FirstPlayerHome,
	//Голова второго игрока (клетка с id 12)
	SecondPlayerHead,
	//Дом второго игрока (клетки с id от 6 до 11)
	SecondPlayerHome,
};

//Перечисление типов шашки
enum class CheckType
{
	//Шашка первого игрока
	FirstPlayer,
	//Шашка второго игрока
	SecondPlayer,
	//Серая шашка подсказка возмодного хода
	Hint
};

//Начальное состояние которое будет активно в начале
const GameStateType GAME_INITIAL_STATE = GameStateType::Initial;

//Словарь возможных ходов
//Ключ - Id клетки 
//Значение - список Id клеток на которые может быть перемещена шашка
using PossibleTurns = std::map<short, std::list<short>>;

/// <summary>
/// Проверка, которая определяет принадлежит ли число заданному диапазону
/// </summary>
/// <param name="valueToClamp">проверяемое число</param>
/// <param name="bottomBorder">нижняя граница включительно</param>
/// <param name="topBorder">верхняя граница не включительно</param>
/// <returns></returns>
bool IsValueInBounds(short valueToClamp, short bottomBorder, short topBorder);