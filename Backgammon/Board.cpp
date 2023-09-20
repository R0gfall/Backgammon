#include "Board.h"

Board::Board()
{
	_backgroundTexture.loadFromFile(BOARD_IMAGE_PATH);
	_backgroundSprite.setTexture(_backgroundTexture);

	_leftOffset = sf::Vector2f(317.f, 64.f + 325.f);

	_possibleTurns = new PossibleTurns;
}

Board::~Board()
{
	delete _possibleTurns;
}

void Board::Initialize()
{
	//—оздаютс€ клетки и устанавливаетс€ их тип и позици€
	for (size_t i = 0; i < CELLS_AMOUNT; i++)
	{
		CellType newCellType;

		switch (i)
		{
		case FIRST_PLAYER_HEAD_CELL_ID:
			newCellType = CellType::FirstPlayerHead;
			break;
		case SECOND_PLAYER_HEAD_CELL_ID:
			newCellType = CellType::SecondPlayerHead;
			break;
		default:
			if (i < CELLS_AMOUNT && i > 18)
			{
				newCellType = CellType::FirstPlayerHome;
			}
			else if (i > 5 && i < 12)
			{
				newCellType = CellType::SecondPlayerHome;
			}
			else
			{
				newCellType = CellType::None;
			}
			break;
		}

		Cell* cell = new Cell(newCellType);
		sf::Vector2f offset;

		if (i / (CELLS_AMOUNT / 2) == 0)
		{
			offset.x = cell->GetSize().x * (i % (CELLS_AMOUNT / 2));
		}
		else
		{
			offset.x = cell->GetSize().x * (CELLS_AMOUNT / 2 - 1) + (-1) * cell->GetSize().x * (i % (CELLS_AMOUNT / 2));
		}

		offset.y = cell->GetSize().y * (-1) * (i / (CELLS_AMOUNT / 2));
		cell->SetPosition(_leftOffset + offset);

		auto cellPosition = cell->GetPosition();
		_cells[i] = cell;
	}

	//ƒоска заполн€етс€ клетками
	for (size_t i = 0; i < START_CHECKS_AMOUNT; i++)
	{
		Check* firstCheck = new Check(CheckType::FirstPlayer);
		_cells[FIRST_PLAYER_HEAD_CELL_ID]->AddCheck(firstCheck);
		Check* secondCheck = new Check(CheckType::SecondPlayer);
		_cells[SECOND_PLAYER_HEAD_CELL_ID]->AddCheck(secondCheck);
	}
}

void Board::Draw(Window* window)
{
	window->Draw(_backgroundSprite);
	for (size_t i = 0; i < CELLS_AMOUNT; i++)
	{
		_cells[i]->Draw(window);
	}
}

Cell* Board::GetCellByPosition(sf::Vector2f position)
{
	sf::FloatRect cellsBounds(_cells[23]->GetBounds().left, _cells[23]->GetBounds().top, _cells[23]->GetSize().x * 12, _cells[23]->GetSize().y * 2);

	if (cellsBounds.contains(position))
	{
		sf::Vector2f localPosition;
		localPosition.x = position.x - cellsBounds.left;
		localPosition.y = position.y - cellsBounds.top;

		return _cells[GetCellIdByLocalPosition(localPosition)];
	}

	return nullptr;
}

Cell* Board::GetCellById(short id)
{
	if (id >= 0 && id < CELLS_AMOUNT)
		return _cells[id];

	Debug::LogError("Wrong Cell id given: " + std::to_string(id));
	return nullptr;
}

void Board::MoveCheck(short idFrom, short idTo)
{
	if (!IsMoveCheckPossible(idFrom, idTo))
		return;

	auto cell = _cells[idFrom]->RemoveCheck();
	_cells[idTo]->AddCheck(cell);

	auto cellFromType = _cells[idFrom]->GetType();
	switch (cellFromType)
	{
	case CellType::None:
		break;
	case CellType::FirstPlayerHead:
		_firstPlayerFromHeadTurns++;
		break;
	case CellType::FirstPlayerHome:
		break;
	case CellType::SecondPlayerHead:
		_secondPlayerFromHeadTurns++;
		break;
	case CellType::SecondPlayerHome:
		break;
	default:
		break;
	}

	if (!Dice::IsDouble())
		_lastPerformedTurn = CalculateDeltaId(idFrom, idTo);
}

bool Board::IsMoveCheckPossible(short idFrom, short idTo)
{
	if (!IsCorrectId(idFrom))
	{
		Debug::LogError("Cannot move check FROM cell. Incorrect id given: " + std::to_string(idFrom));
		return false;
	}

	if (!IsCorrectId(idTo))
	{
		Debug::LogError("Cannot move check TO cell. Incorrect id given: " + std::to_string(idTo));
		return false;
	}

	auto cellFrom = _cells[idFrom];
	auto cellTo = _cells[idTo];

	auto cellFromType = cellFrom->GetType();

	switch (cellFromType)
	{
	case CellType::None:
		break;
	case CellType::FirstPlayerHead:
		if (!IsFirstTurnPossible(PlayerOrderType::FirstPlayer, _firstPlayerFromHeadTurns))
			return false;
		break;
	case CellType::FirstPlayerHome:
		if (cellFrom->GetStatus() == CellStatus::FirstPlayer)
		{
			if (IsTurnOverlaping(PlayerOrderType::FirstPlayer, idFrom, idTo))
			{
				Debug::LogError("Cannot move check. No such turn possible from home");
				return false;
			}
		}
		break;
	case CellType::SecondPlayerHead:
		if (!IsFirstTurnPossible(PlayerOrderType::SecondPlayer, _secondPlayerFromHeadTurns))
			return false;
		break;
	case CellType::SecondPlayerHome:
		if (cellFrom->GetStatus() == CellStatus::SecondPlayer)
		{
			if (IsTurnOverlaping(PlayerOrderType::SecondPlayer, idFrom, idTo))
			{
				Debug::LogError("Cannot move check. No such turn possible from home");
				return false;
			}
		}
		break;
	default:
		break;
	}

	auto deltaId = CalculateDeltaId(idFrom, idTo);

	if (deltaId == _lastPerformedTurn)
	{
		Debug::LogError("Cannot move check TO cell. Such turn was just performed");
		return false;
	}

	auto dices = Dice::GetDices();

	if (deltaId != dices.x && deltaId != dices.y)
	{
		Debug::LogError("Cannot move check TO cell. There's no such turn possible due to dices values");
		return false;
	}

	if (!cellFrom->IsRemoveCheckPossible())
		return false;

	if (!cellTo->IsAddCheckPossible(cellFrom->GetStatus()))
		return false;

	return true;
}

bool Board::TryRemoveCheck(short idFrom)
{
	if (!IsRemoveCheckPossible(idFrom))
		return false;

	//TODO провер€ть на состо€ние конечной игры

	auto cell = _cells[idFrom];
	auto cellStatus = cell->GetStatus();

	auto dices = Dice::GetDices();

	auto minDiceValue = dices.x;
	auto maxDiceValue = dices.y;

	if (dices.x > dices.y)
	{
		minDiceValue = dices.y;
		maxDiceValue = dices.x;
	}

	switch (cellStatus)
	{
	case CellStatus::FirstPlayer:
		//TODO мб не все услови€ учитываютс€
		//TODO надо учитывать предыдущий сделанный ход

		if (IsTurnOverlaping(PlayerOrderType::FirstPlayer, idFrom, CalculateCellId(idFrom, minDiceValue)))
		{
			_lastPerformedTurn = minDiceValue;
		}
		else if (IsTurnOverlaping(PlayerOrderType::FirstPlayer, idFrom, CalculateCellId(idFrom, maxDiceValue)))
		{
			_lastPerformedTurn = maxDiceValue;
		}

		_firstPlayerChecksOut++;
		break;
	case CellStatus::SecondPlayer:
		if (IsTurnOverlaping(PlayerOrderType::SecondPlayer, idFrom, CalculateCellId(idFrom, minDiceValue)))
		{
			_lastPerformedTurn = minDiceValue;
		}
		else if (IsTurnOverlaping(PlayerOrderType::SecondPlayer, idFrom, CalculateCellId(idFrom, maxDiceValue)))
		{
			_lastPerformedTurn = maxDiceValue;
		}

		_secondPlayerChecksOut++;
		break;
	}

	if (IsGameEnded())
	{
		SetWinner();
	}

	cell->RemoveCheck();

	return true;
}

bool Board::IsRemoveCheckPossible(short idFrom)
{
	if (!IsCorrectId(idFrom))
	{
		Debug::LogError("Cannot remove check FROM cell. Incorrect id given: " + std::to_string(idFrom));
		return false;
	}

	auto cell = _cells[idFrom];

	if (!cell->IsRemoveCheckPossible())
		return false;

	auto cellStatus = cell->GetStatus();
	auto cellType = cell->GetType();

	auto dices = Dice::GetDices();
	bool firstDiceTurnPossible;
	bool secondDiceTurnPossible;

	switch (cellType)
	{
	case CellType::FirstPlayerHome:
		if (cellStatus != CellStatus::FirstPlayer)
		{
			Debug::LogError("Cannot remove check FROM cell. You can only remove your cell");
			return false;
		}

		if (Dice::IsDouble())
		{
			firstDiceTurnPossible = IsTurnOverlaping(PlayerOrderType::FirstPlayer, idFrom, CalculateCellId(idFrom, dices.x));
			secondDiceTurnPossible = firstDiceTurnPossible;
		}
		else
		{
			firstDiceTurnPossible = IsTurnOverlaping(PlayerOrderType::FirstPlayer, idFrom, CalculateCellId(idFrom, dices.x)) && dices.x != _lastPerformedTurn;
			secondDiceTurnPossible = IsTurnOverlaping(PlayerOrderType::FirstPlayer, idFrom, CalculateCellId(idFrom, dices.y)) && dices.y != _lastPerformedTurn;
		}

		if (!firstDiceTurnPossible && !secondDiceTurnPossible)
		{
			Debug::LogError("Cannot remove check FROM cell. No such turns possible");
			return false;
		}
		break;
	case CellType::SecondPlayerHome:
		if (cellStatus != CellStatus::SecondPlayer)
		{
			Debug::LogError("Cannot remove check FROM cell. You can only remove your cell");
			return false;
		}

		firstDiceTurnPossible = IsTurnOverlaping(PlayerOrderType::SecondPlayer, idFrom, CalculateCellId(idFrom, dices.x)) && dices.x != _lastPerformedTurn;
		secondDiceTurnPossible = IsTurnOverlaping(PlayerOrderType::SecondPlayer, idFrom, CalculateCellId(idFrom, dices.y)) && dices.y != _lastPerformedTurn;

		if (!firstDiceTurnPossible && !secondDiceTurnPossible)
		{
			Debug::LogError("Cannot remove check FROM cell. No such turns possible");
			return false;
		}
		break;
	default:
		Debug::LogError("Cannot remove check FROM cell. You can only remove cell from home");
		return false;
		break;
	}

	return true;
}

bool Board::IsCorrectId(short id)
{
	return IsValueInBounds(id, 0, CELLS_AMOUNT);
}

void Board::HideHints()
{
	for (auto cell : _cells)
	{
		cell->HideHint();
	}
}

short Board::CalculateDeltaId(short fromId, short toId)
{
	if (fromId < toId)
		return toId - fromId;
	else
		return (CELLS_AMOUNT + toId) - fromId;
}

short Board::CalculateCellId(short fromId, short turnValue)
{
	return (fromId + turnValue) % CELLS_AMOUNT;
}

void Board::ResetTurns()
{
	_lastPerformedTurn = -1;
	_firstPlayerFromHeadTurns = 0;
	_secondPlayerFromHeadTurns = 0;
  
	if (IsGameEnded())
	{
		SetWinner();
	}
}

PossibleTurns Board::GetAllPossibleTurns(PlayerOrderType orderType)
{
	_possibleTurns->clear();

	for (auto cell : _cells)
	{
		auto cellStatus = cell->GetStatus();

		if ((short)cellStatus == (short)orderType)
		{
			auto currentCellId = cell->GetId();

			auto dices = Dice::GetDices();

			auto firstTurn = CalculateCellId(currentCellId, dices.x);
			auto secondTurn = CalculateCellId(currentCellId, dices.y);

			if (!Dice::IsDouble())
			{
				if (IsMoveCheckPossible(currentCellId, firstTurn))
				{
					AddToPossibleTurns(currentCellId, firstTurn);
				}
				if (IsMoveCheckPossible(currentCellId, secondTurn))
				{
					AddToPossibleTurns(currentCellId, secondTurn);
				}
			}
			else
			{
				if (IsMoveCheckPossible(currentCellId, firstTurn))
				{
					AddToPossibleTurns(currentCellId, firstTurn);
				}
			}
		}
	}

	return *_possibleTurns;
}

void Board::SetFirstTurnMade(PlayerOrderType orderType)
{
	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		_firstPlayerFirstTurnMade = true;
		break;
	case PlayerOrderType::SecondPlayer:
		_secondPlayerFirstTurnMade = true;
		break;
	}
}

bool Board::IsFirstTurnMade(PlayerOrderType orderType)
{
	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		return _firstPlayerFirstTurnMade;
		break;
	case PlayerOrderType::SecondPlayer:
		return _secondPlayerFirstTurnMade;
		break;
	}
	return false;
}

void Board::SetOnEndStage(PlayerOrderType orderType)
{
	SetOnEndStage(orderType, true);
}

void Board::SetOnEndStage(PlayerOrderType orderType, bool value)
{
	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		_firstPlayerOnEndStage = value;
		break;
	case PlayerOrderType::SecondPlayer:
		_secondPlayerOnEndStage = value;
		break;
	}
}

bool Board::IsOnEndStage(PlayerOrderType orderType)
{
	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		return _firstPlayerOnEndStage;
		break;
	case PlayerOrderType::SecondPlayer:
		return _secondPlayerOnEndStage;
		break;
	}
	return false;
}

char Board::GetChecksOut(PlayerOrderType orderType)
{
	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		return _firstPlayerChecksOut;
		break;
	case PlayerOrderType::SecondPlayer:
		return _secondPlayerChecksOut;
		break;
	}

	return -1;
}

bool Board::IsGameEnded()
{
	return _firstPlayerChecksOut >= START_CHECKS_AMOUNT || _secondPlayerChecksOut >= START_CHECKS_AMOUNT;
}

PlayerOrderType Board::GetWinner()
{
	return _gameWinner;
}

void Board::SetMaxChecksOut(PlayerOrderType orderType)
{
	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		_firstPlayerChecksOut = START_CHECKS_AMOUNT;
		break;
	case PlayerOrderType::SecondPlayer:
		_secondPlayerChecksOut = START_CHECKS_AMOUNT;
		break;
	default:
		Debug::LogError("Cannot set max checks out amount. None player order type given");
		break;
	}
}

void Board::SetWinner()
{
	if (_firstPlayerChecksOut >= START_CHECKS_AMOUNT)
	{
		SetWinner(PlayerOrderType::FirstPlayer);
	}
	else
	{
		SetWinner(PlayerOrderType::SecondPlayer);
	}
}

void Board::SetWinner(PlayerOrderType orderType)
{
	_gameWinner = orderType;
}

bool Board::IsTurnOverlaping(PlayerOrderType orderType, short fromId, short toId)
{
	if (!IsCorrectId(fromId))
	{
		Debug::LogError("Incorrect id given: " + std::to_string(fromId));
		return false;
	}

	if (!IsCorrectId(toId))
	{
		Debug::LogError("Incorrect id given: " + std::to_string(toId));
		return false;
	}

	switch (orderType)
	{
	case PlayerOrderType::FirstPlayer:
		return (fromId < CELLS_AMOUNT && fromId > 17) && (toId >= 0 && toId < 6);
		break;
	case PlayerOrderType::SecondPlayer:
		return (fromId < 12 && fromId >= 6) && (toId >= 12 && toId < 18);
		break;
	}

	return false;
}

bool Board::IsFirstTurnPossible(PlayerOrderType orderType, short fromHeadTurns)
{
	if (IsFirstTurnMade(orderType) && fromHeadTurns > 0)
	{
		Debug::LogError("Cannot move check FROM head cell twice. You've already taken check from head at this turn");
		return false;
	}
	
	if (!IsFirstTurnMade(orderType))
	{
		if (!Dice::IsDouble() && fromHeadTurns > 0)
		{
			Debug::LogError("Cannot move check FROM head cell twice. There's not a double on dices");
			return false;
		}

		auto dices = Dice::GetDices();

		if ((dices.x == 1 || dices.x == 2 || dices.x == 4) && fromHeadTurns > 0)
		{
			Debug::LogError("Cannot move check FROM head cell twice. Double must contain 3, 5 or 6");
			return false;
		}

		if (!IsValueInBounds(fromHeadTurns, 0, 2))
		{
			Debug::LogError("Cannot move check FROM head cell more than twice");
			return false;
		}
	}

	return true;
}

void Board::AddToPossibleTurns(short fromCellId, short toCellId)
{
	auto itr = _possibleTurns->find(fromCellId);
	if (itr != _possibleTurns->end())
	{
		_possibleTurns->at(fromCellId).push_back(toCellId);
	}
	else
	{
		std::list<short> _turnsList;
		_turnsList.push_back(toCellId);
		_possibleTurns->emplace(fromCellId, _turnsList);
	}
}

short Board::GetCellIdByLocalPosition(sf::Vector2f localPosition)
{
	short line = (int)localPosition.y / (int)_cells[0]->GetSize().y;
	short id = 0;
	if (line == 0)
	{
		id = 23 - (int)localPosition.x / (int)_cells[0]->GetSize().x;
	}
	else
	{
		id = (int)localPosition.x / (int)_cells[0]->GetSize().x;
	}
	return id;
}
