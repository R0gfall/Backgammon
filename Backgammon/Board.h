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

//Класс доски
//Хранит в себе 24 клетки 
//Содержит методы перемещения шашек и сбрасывания с доски
class Board
{
public:
	//Конструктор
	Board();
	//Деструктор
	~Board();

	void Initialize();
	void Draw(Window* window);

	// Получение указателя на клетку по позиции или nullptr 
	Cell* GetCellByPosition(sf::Vector2f position);
	// Получение указателя на клетку по Id или nullptr
	Cell* GetCellById(short id);

	// Перемещение шашки
	void MoveCheck(short idFrom, short idTo);
	// Проверка на возможность пермещения шашки
	bool IsMoveCheckPossible(short idFrom, short idTo);

	//Скидывание шашки с доски
	//Возвращает true если операция выполнена
	bool TryRemoveCheck(short idFrom);
	// Проверка на возможность скидывания шашки с доски
	bool IsRemoveCheckPossible(short idFrom);

	//Проверка на корректность Id
	bool IsCorrectId(short id);

	//Скрыть серые шашки подсказки
	void HideHints();

	//Возвращает модуль разности Id
	static short CalculateDeltaId(short fromId, short toId);
	//Возвращает Id клетки, если совершить ход с fromId на значение turnValue
	static short CalculateCellId(short fromId, short turnValue);
	//Обнуление значений текущего хода
	//Должно вызываться в конце хода каждого игрока
	void ResetTurns();

	//Возвращает словарь всех возможных ходов игрока типа orderType
	PossibleTurns GetAllPossibleTurns(PlayerOrderType orderType);

	//Вызывается после первого хода игрока единственный раз
	void SetFirstTurnMade(PlayerOrderType orderType);
	//Проверка сделан ли первый ход у игрока
	bool IsFirstTurnMade(PlayerOrderType orderType);

	//TODO ОБНОВИТЬ КОММЕНТАРИЙ КОГДА БУДЕТ ДОДЕЛАН КОНЕЦ ИГРЫ
	//Вызывается когда все шашки игрока находятся в доме
	void SetOnEndStage(PlayerOrderType orderType);
	//Метод для отладки
	void SetOnEndStage(PlayerOrderType orderType, bool value);
	//Проверка находятся ли все шашки игрока в доме
	bool IsOnEndStage(PlayerOrderType orderType);

	//Возвращает количество сьрошенных со стола фишек
	char GetChecksOut(PlayerOrderType orderType);

private:
	//Проверка выходит ли ход за пределы дома
	bool IsTurnOverlaping(PlayerOrderType orderType, short fromId, short toId);
	//Проверка возможен ли первый ход (снять 2 шашки с головы)
	bool IsFirstTurnPossible(PlayerOrderType orderType, short fromHeadTurns);

	//Добавляет ход в словарь возможных ходов
	void AddToPossibleTurns(short fromCellId, short toCellId);

	// Получение указателя на клетку относительно позиции клеток доски или nullptr 
	short GetCellIdByLocalPosition(sf::Vector2f localPosition);

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;

	//Отступ от верхнего левого угла окна до верхнего левого угла нижней левой клетки
	sf::Vector2f _leftOffset;

	//Массив всех клеток
	Cell* _cells[CELLS_AMOUNT];

	//Значение кости на который последний раз передвинулась шашка
	short _lastPerformedTurn = -1;

	//Словарь возможных ходов
	PossibleTurns* _possibleTurns;

	//Флаг: сделан ли первый ход у первого игрока
	bool _firstPlayerFirstTurnMade = false;
	//Флаг: сделан ли первый ход у второго игрока
	bool _secondPlayerFirstTurnMade = false;

	//Количество снятых шашек с головы у первого игрока
	//Обновляется после каждого хода в ResetTurns
	char _firstPlayerFromHeadTurns = 0;
	//Количество снятых шашек с головы у второго игрока
	//Обновляется после каждого хода в ResetTurns
	char _secondPlayerFromHeadTurns = 0;

	//Флаг: все ли шашки первого игрока в доме
	bool _firstPlayerOnEndStage = false;
	//Флаг: все ли шашки второго игрока в доме
	bool _secondPlayerOnEndStage = false;

	//Количество сброшенных с доски шашек у первого игрока
	char _firstPlayerChecksOut = 0;
	//Количество сброшенных с доски шашек у второго игрока
	char _secondPlayerChecksOut = 0;
};

