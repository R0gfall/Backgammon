#pragma once

#include <SFML/Graphics.hpp>
#include <list>

#include "Window.h"

#include "Check.h"

#include "Debug.h"

const short CELL_WIDTH = 62;
const short CELL_HEIGHT = 325;

const float PER_CHECK_OFFSET = 10.f;

const float CELL_WEIGHT_DEFAULT_VALUE = 1.f;

//Класс клетки
//Содержит в себе массив шашек, которые находятся на данной клетке
class Cell
{
public:
	//Конструктор
	Cell(CellType type);
	//Деструктор
	~Cell();

	//Возращает размер области клетки
	sf::Vector2f GetSize() { return _cellSize; }

	//Задает позицию клетки в координатах окна
	void SetPosition(sf::Vector2f position);
	//Возвращает позицию клетки в координатах окна
	sf::Vector2f GetPosition();

	//Возвращает Id клетки
	short GetId() { return _id; }
	//Возвращает область клетки 
	sf::FloatRect GetBounds() { return _debugRect.getGlobalBounds(); }

	void Draw(Window* window);

	//Проверка на возможность добавления шашки в список
	bool IsAddCheckPossible(CellStatus fromCellStatus);
	//Проверка на возможность добавления шашки в список
	bool IsAddCheckPossible(CheckType checkType);
	//Проверка на возможность добавления шашки в список
	bool IsAddCheckPossible(Check* check);
	//Проверка на возможность удаления шашки из клетки
	bool IsRemoveCheckPossible();

	//Проверка отображается ли подсказка на клетке
	bool IsHinted() { return _isHintShown; }

	//Добавление шашки в список
	void AddCheck(Check* check);
	//Удаление шашки из списка
	Check* RemoveCheck();

	// Возвращает количество шашек в клетке
	size_t GetChecksAmout();

	//Показывает шашку-подсказку
	void ShowHint();
	//Скрывает шашку-подсказку
	void HideHint();

	//Проверка свободна ли клетка (true если список шашек пуст)
	bool IsFree() { return _status == CellStatus::Free; }
	//Возвращает состояние клетки
	CellStatus GetStatus() { return _status; }

	//Возвращает тип клетки
	CellType GetType() { return _type; }

	//TODO методы для алгоритма не реализованы
	void SetWeight1(float weight) { _weight1 = weight; }
	float GetWeight1() { return _weight1; }
	void SetWeight2(float weight) { _weight2 = weight; }
	float GetWeight2() { return _weight2; }

private:
	//Добавляет шашку-подсказку в конец списка
	void AddHint();
	//Удаляет шашку-подсказку из конца списка
	void RemoveHint(std::list<Check*>::iterator itr);

	//Размер области клетки
	sf::Vector2f _cellSize;

	//Область клетки
	sf::RectangleShape _debugRect;
	//Отображаемое Id клетки
	sf::Text _idText;
	sf::Font _font;
	//Отступ текста от левого верхнего угла области клетки
	sf::Vector2f _textOffset;

	//Id клетки
	short _id;
	static short _idCounter;

	//Списко шашек
	std::list<Check*> _checks;
	//Итератор на шашку-подсказку
	std::list<Check*>::iterator _hintItr;

	//Шашка подсказка
	Check* _hintCheck;
	//Флаг: показана ли шашка-подсказка
	bool _isHintShown = false;

	CellStatus _status = CellStatus::Free;
	CellType _type;

	float _weight1 = CELL_WEIGHT_DEFAULT_VALUE;
	float _weight2 = CELL_WEIGHT_DEFAULT_VALUE;
};

