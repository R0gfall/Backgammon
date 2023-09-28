#include "Cell.h"

short Cell::_idCounter = 0;

Cell::Cell(CellType type) : _id(_idCounter++), _type(type)
{
	_cellSize = sf::Vector2f(62.f, 325.f);
	_textOffset = sf::Vector2f(10.f, 10.f);

	
	_font.loadFromFile(FONT_PATH);

	_idText.setFont(_font);
	_idText.setString(std::to_string(_id));
	_idText.setFillColor(sf::Color::Red);
	_idText.setCharacterSize(20);

	_debugRect.setOutlineColor(sf::Color::Green);
	_debugRect.setOutlineThickness(1.f);
	_debugRect.setFillColor(sf::Color(0, 255, 0, 40));
	_debugRect.setSize(_cellSize);

	_hintCheck = new Check(CheckType::Hint);
}

Cell::~Cell()
{
	for (auto check : _checks)
	{
		delete check;
	}

	delete _hintCheck;
}

void Cell::SetPosition(sf::Vector2f position)
{
	_debugRect.setPosition(position);
	_idText.setPosition(position + _textOffset);
}

sf::Vector2f Cell::GetPosition()
{
	return _debugRect.getPosition();
}

void Cell::Draw(Window* window)
{
	window->Draw(_debugRect);
	window->Draw(_idText);

	for(auto check : _checks)
	{
		check->Draw(window);
	}
}


bool Cell::IsAddCheckPossible(CellStatus fromCellStatus)
{
	switch (fromCellStatus)
	{
	case CellStatus::Free:
		Debug::LogWarning("Cannot move check from free cell");
		return false;
		break;
	case CellStatus::FirstPlayer:
		return IsAddCheckPossible(CheckType::FirstPlayer);
		break;
	case CellStatus::SecondPlayer:
		return IsAddCheckPossible(CheckType::SecondPlayer);
		break;
	}

}

bool Cell::IsAddCheckPossible(CheckType checkType)
{
	if (IsHinted())
	{
		Debug::LogError("Cannot add check to Cell with id: " + std::to_string(_id) + "\nHint is shown");
		return false;
	}

	if (checkType == CheckType::FirstPlayer && _status == CellStatus::SecondPlayer)
	{
		Debug::LogError("Cannot add check to Cell with id: " + std::to_string(_id) + "\nDifferent type of cell status and check type");
		return false;
	}

	if (checkType == CheckType::SecondPlayer && _status == CellStatus::FirstPlayer)
	{
		Debug::LogError("Cannot add check to Cell with id: " + std::to_string(_id) + "\nDifferent type of cell status and check type");
		return false;
	}

	return true;
}

bool Cell::IsAddCheckPossible(Check* check)
{
	if (check == nullptr)
	{
		Debug::LogError("Cannot add check to Cell with id: " + std::to_string(_id) + "\n Incorrect pointer given");
		return false;
	}

	return IsAddCheckPossible(check->GetType());
}

bool Cell::IsRemoveCheckPossible()
{
	if (IsHinted())
	{
		Debug::LogError("Cannot remove check from Cell with id: " + std::to_string(_id) + "\n Hint is shown");
		return false;
	}
	if (_checks.empty())
	{
		Debug::LogError("Cannot remove check from Cell with id: " + std::to_string(_id) + "\nContainer is empty");
		return false;
	}
	return true;
}

void Cell::AddCheck(Check* check)
{
	if (!IsAddCheckPossible(check))
		return;

	switch (check->GetType())
	{
	case CheckType::FirstPlayer:
		_status = CellStatus::FirstPlayer;
		break;
	case CheckType::SecondPlayer:
		_status = CellStatus::SecondPlayer;
		break;
	}

	sf::Vector2f globalPosition = _debugRect.getPosition();
	sf::Vector2f vertialOffset;

	if (_id / 12)
	{
		vertialOffset.y += _checks.size() * PER_CHECK_OFFSET;
	}
	else
	{
		vertialOffset.y = CELL_HEIGHT - CHECK_HEIGHT;

		vertialOffset.y -= _checks.size() * PER_CHECK_OFFSET;
	}

	check->SetPosition(globalPosition + vertialOffset);

	_checks.push_back(check);
}

Check* Cell::RemoveCheck()
{
	Check* returnValue = nullptr;

	if (!IsRemoveCheckPossible())
		return returnValue;

	returnValue = _checks.back();
	_checks.pop_back();

	if (_checks.empty())
		_status = CellStatus::Free;

	return returnValue;
}

size_t Cell::GetChecksAmout()
{
	return _checks.size();
}

void Cell::ShowHint()
{
	if (!IsHinted())
	{
		AddHint();

		_isHintShown = true;
	}
}

void Cell::HideHint()
{
	if (IsHinted())
	{
		RemoveHint(_hintItr);
		_isHintShown = false;
	}
}

void Cell::AddHint()
{
	AddCheck(_hintCheck);
	auto itr = _checks.end();
	std::advance(itr, -1);
	_hintItr = itr;
}

void Cell::RemoveHint(std::list<Check*>::iterator itr)
{
	if (!_checks.empty())
	{
		_checks.erase(itr);
		return;
	}
	Debug::LogError("Cannot remove Hint from Cell with id: " + std::to_string(_id) + "\nContainer is empty");
	return;
}
 