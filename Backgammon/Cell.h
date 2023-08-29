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

class Cell
{
public:
	Cell(CellType type);
	~Cell()
	{
		for (auto check : _checks)
		{
			delete check;
		}

		delete _hintCheck;
	}

	sf::Vector2f GetSize() { return _cellSize; }

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();

	short GetId() { return _id; }
	sf::FloatRect GetBounds() { return _debugRect.getGlobalBounds(); }

	void Draw(Window* window);

	bool IsAddCheckPossible(CellStatus fromCellStatus);
	bool IsAddCheckPossible(CheckType checkType);
	bool IsAddCheckPossible(Check* check);
	bool IsRemoveCheckPossible();

	bool IsHinted() { return _isHintShown; }

	void AddCheck(Check* check);
	Check* RemoveCheck();

	void ShowHint();
	void HideHint();

	bool IsFree() { return _status == CellStatus::Free; }
	CellStatus GetStatus() { return _status; }

	CellType GetType() { return _type; }

	void SetWeight1(float weight) { _weight1 = weight; }
	float GetWeight1() { return _weight1; }
	void SetWeight2(float weight) { _weight2 = weight; }
	float GetWeight2() { return _weight2; }

private:
	void AddHint();
	void RemoveHint(std::list<Check*>::iterator itr);

	sf::Vector2f _cellSize;

	sf::RectangleShape _debugRect;
	sf::Text _turnText;
	sf::Font _font;
	sf::Vector2f _textOffset;

	short _id;
	static short _idCounter;

	std::list<Check*> _checks;
	std::list<Check*>::iterator _hintItr;

	Check* _hintCheck;
	bool _isHintShown = false;

	CellStatus _status = CellStatus::Free;
	CellType _type;

	float _weight1 = CELL_WEIGHT_DEFAULT_VALUE;
	float _weight2 = CELL_WEIGHT_DEFAULT_VALUE;
};

