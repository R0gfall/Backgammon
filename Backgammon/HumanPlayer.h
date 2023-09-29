#pragma once

#include "IPlayer.h"

#include "Debug.h"

#include "Input.h"
#include "Mouse.h"

#include "Dice.h"

const std::string CHOSEN_CELL_PLACEHOLDER = "Chosen cell: ";
const std::string NOT_CHOSEN_CELL_PLACEHOLDER = "No cell chosen";

//���������� ����� ������
class HumanPlayer : public IPlayer
{
public:
	//�����������
	HumanPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board);


	void OnTurnEnter() override;
	void OnEndTurnEnter() override;
	void OnUpdate() override;
	void OnEndUpdate() override;
	void OnTurnExit() override;

	void Draw(Window* window) override;

private:
	//����� ��������� ����� ����
	void HandleMouseClick();

	//����� ��������� ����������� ����� �� ��������� ������
	void HandleCheckMove(Cell* targetCell);
	//����� ����������� ����� 
	void MoveCheck(short fromId, short toId);

	//����� ������ ����� � ����� (� ��������� ������ ����, ����� ��� ����� � ����)
	void RemoveCheck();

	//����� ������ ������
	void ChooseCell(Cell* cell);
	//����� ������ ������ ������
	void CancelCellChoise();
	//��������, ����� �� ������ ���� �������
	bool IsCellCanBeChosen(Cell* cell);

	//����� ��� ����������� �����-���������
	void ShowPossibleTurns();

	//��������, ������� �� ������
	bool IsCellChosen() { return _chosenCell != nullptr; }

	//����� ��������� �����
	void HandleInput();
	//����� ���������� ������
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
