#include "HumanPlayer.h"

HumanPlayer::HumanPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board) : IPlayer(orderType, stateMachine, board)
{
	Debug::LogInfo("Human player was created");

	_font.loadFromFile(FONT_PATH);

	_chosenCellText.setFont(_font);
	_chosenCellText.setCharacterSize(20);
	_chosenCellText.setFillColor(sf::Color::Black);
	UpdateChosenCellText();

	_chosenCellText.setPosition(sf::Vector2f(1200.f, 100.f));
}

void HumanPlayer::OnTurnEnter()
{
	if (!IsAnyTurnsPossible(HUMAN_SHOULD_LOG))
	{
		NextTurn();
	}
}

void HumanPlayer::OnEndTurnEnter()
{
}

void HumanPlayer::OnUpdate()
{
	HandleInput();

	//Test nend game
	if (Input::IsKeyDown(Input::Key::E))
	{
		DebugSetEndStage(true);
	}
}

void HumanPlayer::OnEndUpdate()
{
	HandleInput();

	//Test nend game
	if (Input::IsKeyDown(Input::Key::E))
	{
		DebugSetEndStage(false);
	}

	//Test nend game
	if (Input::IsKeyDown(Input::Key::C))
	{
		RemoveCheck();
	}
}

void HumanPlayer::OnTurnExit()
{
	CancelCellChoise();

	_firstPossibleCellId = -1;
	_secondPossibleCellId = -1;

	_lastPerformedTurn = -1;

	_performedTurns = 0;
}

void HumanPlayer::Draw(Window* window)
{
	UpdateChosenCellText();
	window->Draw(_chosenCellText);

	IPlayer::Draw(window);
}

void HumanPlayer::HandleMouseClick()
{
	auto targetCell = GameBoard->GetCellByPosition(Mouse::GetRelativePosition());
	if (targetCell == nullptr)
	{
		CancelCellChoise();
		return;
	}

	if (!IsCellChosen())
	{
		if (targetCell->IsFree())
		{
			if (HUMAN_SHOULD_LOG)
			{
				Debug::LogWarning("Cannot chose free cell");
			}
			return;
		}
		ChooseCell(targetCell);

	}
	else
	{
		HandleCheckMove(targetCell);
	}

}

void HumanPlayer::HandleCheckMove(Cell* targetCell)
{
	GameBoard->HideHints();
	auto taregetCellId = targetCell->GetId();

	if (GameBoard->IsMoveCheckPossible(_chosenCell->GetId(), targetCell->GetId()))
	{
		MoveCheck(_chosenCell->GetId(), targetCell->GetId());
		CancelCellChoise();
		return;
	}
	CancelCellChoise();
	Debug::LogWarning("Cannot move check. Impossible variant was chosen");

}

void HumanPlayer::MoveCheck(short fromId, short toId)
{
	short deltaId = Board::CalculateDeltaId(fromId, toId);

	if (!Dice::IsDouble())
		_lastPerformedTurn = deltaId;

	GameBoard->MoveCheck(fromId, toId);
	++_performedTurns;
	if (_performedTurns >= Dice::GetPossibleTurnsAmount())
	{
		NextTurn();
		return;
	}	

	if (!IsAnyTurnsPossible(HUMAN_SHOULD_LOG))
	{
		NextTurn();
		return;
	}
}

void HumanPlayer::RemoveCheck()
{
	if (_chosenCell == nullptr)
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogError("Cannot remove check. No check chosen");
		}
		return;
	}

	if (GameBoard->TryRemoveCheck(_chosenCell->GetId(), HUMAN_SHOULD_LOG))
	{
		// добавлено
		_performedTurns++;
		if (_performedTurns >= Dice::GetPossibleTurnsAmount())
		{
			NextTurn();
			return;
		}
	}

	if (GameBoard->IsGameEnded())
	{
		NextTurn();
		return;
	}
}


void HumanPlayer::ChooseCell(Cell* cell)
{
	if (!IsCellCanBeChosen(cell))
		return;

	_chosenCell = cell;

	if (HUMAN_SHOULD_LOG)
	{
		Debug::Log("Chosen cell is: " + std::to_string(_chosenCell->GetId()));
	}
	ShowPossibleTurns();
}

void HumanPlayer::CancelCellChoise()
{
	if (HUMAN_SHOULD_LOG)
	{
		Debug::Log("Choise cancelled");
	}
	_chosenCell = nullptr;
	GameBoard->HideHints();
}

bool HumanPlayer::IsCellCanBeChosen(Cell* cell)
{
	if (cell == nullptr)
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogWarning("Cannot choose cell. Incorrect pointer given");
		}
		return false;
	}

	auto cellStatus = cell->GetStatus();
	if (cellStatus == CellStatus::FirstPlayer && OrderType == PlayerOrderType::SecondPlayer)
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogWarning("Cannot choose cell with id: " + std::to_string(cell->GetId()) + "\nDifferent types of cell and player order");
		}
		return false;
	}
	if (cellStatus == CellStatus::SecondPlayer && OrderType == PlayerOrderType::FirstPlayer)
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogWarning("Cannot choose cell with id: " + std::to_string(cell->GetId()) + "\nDifferent types of cell and player order");
		}
		return false;
	}

	return true;
}

void HumanPlayer::ShowPossibleTurns()
{
	//Debug::Log("Last performed turn: " + std::to_string(_lastPerformedTurn));

	auto possibleTurns = CalculatePossibleTurns(HUMAN_SHOULD_LOG);

	auto chosenCellId = _chosenCell->GetId();
	if (HUMAN_SHOULD_LOG)
	{
		Debug::Log("Show hint from chosen cell with id: " + std::to_string(chosenCellId));
	}

	auto itr = possibleTurns.find(chosenCellId);
	if (itr != possibleTurns.end())
	{
		for (auto turn : possibleTurns.at(chosenCellId))
		{
			if (HUMAN_SHOULD_LOG)
			{
				Debug::Log("Possible turn to id: " + std::to_string(turn));
			}
			auto targetCell = GameBoard->GetCellById(turn);
			targetCell->ShowHint();
		}
	}
	else
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogWarning("No possible turns from this cell");
		}
		if (!IsOnEndStage())
		{
			CancelCellChoise();
		}
	}

}

void HumanPlayer::HandleInput()
{
	if (Mouse::IsLMBDown(Mouse::Key::LMouseButton))
	{
		HandleMouseClick();
	}

	if (Input::IsKeyDown(Input::Key::Space))
	{
		CancelCellChoise();
	}

	//Reroll 
	if (Input::IsKeyDown(Input::Key::R))
	{
		CancelCellChoise();
		Dice::Roll();
	}

	if (Input::IsKeyDown(Input::Key::Z))
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogWarning("First player max checks out set");
		}
		GameBoard->SetMaxChecksOut(PlayerOrderType::FirstPlayer);
	}
	if (Input::IsKeyDown(Input::Key::X))
	{
		if (HUMAN_SHOULD_LOG)
		{
			Debug::LogWarning("Second player max checks out set");
		}
		GameBoard->SetMaxChecksOut(PlayerOrderType::SecondPlayer);
	}
}

void HumanPlayer::UpdateChosenCellText()
{
	if (IsCellChosen())
	{
		_chosenCellText.setString(CHOSEN_CELL_PLACEHOLDER + std::to_string(_chosenCell->GetId()));
	}
	else
	{
		_chosenCellText.setString(NOT_CHOSEN_CELL_PLACEHOLDER);
	}

}
