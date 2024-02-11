#pragma once

#include "IPlayer.h"

#include "Debug.h"

#include "Input.h"
#include "Mouse.h"

#include "Dice.h"

const std::string CHOSEN_CELL_PLACEHOLDER = "Chosen cell: ";
const std::string NOT_CHOSEN_CELL_PLACEHOLDER = "No cell chosen";

//Конкретный класс игрока
class HumanPlayer : public IPlayer
{
public:
	//Конструктор
	HumanPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board);


	void OnTurnEnter() override;	
	void OnEndTurnEnter() override;
	void OnUpdate() override;
	void OnEndUpdate() override;
	void OnTurnExit() override;

	void Draw(Window* window) override;

private:
	//Метод обработки клика мыши
	void HandleMouseClick();

	//Метод обработки перемещения шашки на указанную клетку
	void HandleCheckMove(Cell* targetCell);
	//Метод перемещения шашки 
	void MoveCheck(short fromId, short toId);

	//Метод сброса шашки с доски (в финальной стадии игры, когда все шашки в доме)
	void RemoveCheck();

	//Метод выбора клетки
	void ChooseCell(Cell* cell);
	//Метод отмены выбора клетки
	void CancelCellChoise();
	//Проверка, может ли клетка быть выбрана
	bool IsCellCanBeChosen(Cell* cell);

	//Метод для отображения шашек-подсказок
	void ShowPossibleTurns();

	//Проверка, выбрана ли клетка
	bool IsCellChosen() { return _chosenCell != nullptr; }

	//Метод обработки ввода
	void HandleInput();
	//Метод обновления текста
	void UpdateChosenCellText();

	sf::Font _font;
	sf::Text _chosenCellText;

	Cell* _chosenCell = nullptr;

	short _firstPossibleCellId = -1;
	short _secondPossibleCellId = -1;

	short _lastPerformedTurn = -1;

	short _performedTurns = 0;

	bool _debugEndMode = false;
};

