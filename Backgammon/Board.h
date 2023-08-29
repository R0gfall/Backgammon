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

//����� �����
//������ � ���� 24 ������ 
//�������� ������ ����������� ����� � ����������� � �����
class Board
{
public:
	//�����������
	Board();
	//����������
	~Board();

	void Initialize();
	void Draw(Window* window);

	// ��������� ��������� �� ������ �� ������� ��� nullptr 
	Cell* GetCellByPosition(sf::Vector2f position);
	// ��������� ��������� �� ������ �� Id ��� nullptr
	Cell* GetCellById(short id);

	// ����������� �����
	void MoveCheck(short idFrom, short idTo);
	// �������� �� ����������� ���������� �����
	bool IsMoveCheckPossible(short idFrom, short idTo);

	//���������� ����� � �����
	//���������� true ���� �������� ���������
	bool TryRemoveCheck(short idFrom);
	// �������� �� ����������� ���������� ����� � �����
	bool IsRemoveCheckPossible(short idFrom);

	//�������� �� ������������ Id
	bool IsCorrectId(short id);

	//������ ����� ����� ���������
	void HideHints();

	//���������� ������ �������� Id
	static short CalculateDeltaId(short fromId, short toId);
	//���������� Id ������, ���� ��������� ��� � fromId �� �������� turnValue
	static short CalculateCellId(short fromId, short turnValue);
	//��������� �������� �������� ����
	//������ ���������� � ����� ���� ������� ������
	void ResetTurns();

	//���������� ������� ���� ��������� ����� ������ ���� orderType
	PossibleTurns GetAllPossibleTurns(PlayerOrderType orderType);

	//���������� ����� ������� ���� ������ ������������ ���
	void SetFirstTurnMade(PlayerOrderType orderType);
	//�������� ������ �� ������ ��� � ������
	bool IsFirstTurnMade(PlayerOrderType orderType);

	//TODO �������� ����������� ����� ����� ������� ����� ����
	//���������� ����� ��� ����� ������ ��������� � ����
	void SetOnEndStage(PlayerOrderType orderType);
	//����� ��� �������
	void SetOnEndStage(PlayerOrderType orderType, bool value);
	//�������� ��������� �� ��� ����� ������ � ����
	bool IsOnEndStage(PlayerOrderType orderType);

	//���������� ���������� ���������� �� ����� �����
	char GetChecksOut(PlayerOrderType orderType);

private:
	//�������� ������� �� ��� �� ������� ����
	bool IsTurnOverlaping(PlayerOrderType orderType, short fromId, short toId);
	//�������� �������� �� ������ ��� (����� 2 ����� � ������)
	bool IsFirstTurnPossible(PlayerOrderType orderType, short fromHeadTurns);

	//��������� ��� � ������� ��������� �����
	void AddToPossibleTurns(short fromCellId, short toCellId);

	// ��������� ��������� �� ������ ������������ ������� ������ ����� ��� nullptr 
	short GetCellIdByLocalPosition(sf::Vector2f localPosition);

	sf::Texture _backgroundTexture;
	sf::Sprite _backgroundSprite;

	//������ �� �������� ������ ���� ���� �� �������� ������ ���� ������ ����� ������
	sf::Vector2f _leftOffset;

	//������ ���� ������
	Cell* _cells[CELLS_AMOUNT];

	//�������� ����� �� ������� ��������� ��� ������������� �����
	short _lastPerformedTurn = -1;

	//������� ��������� �����
	PossibleTurns* _possibleTurns;

	//����: ������ �� ������ ��� � ������� ������
	bool _firstPlayerFirstTurnMade = false;
	//����: ������ �� ������ ��� � ������� ������
	bool _secondPlayerFirstTurnMade = false;

	//���������� ������ ����� � ������ � ������� ������
	//����������� ����� ������� ���� � ResetTurns
	char _firstPlayerFromHeadTurns = 0;
	//���������� ������ ����� � ������ � ������� ������
	//����������� ����� ������� ���� � ResetTurns
	char _secondPlayerFromHeadTurns = 0;

	//����: ��� �� ����� ������� ������ � ����
	bool _firstPlayerOnEndStage = false;
	//����: ��� �� ����� ������� ������ � ����
	bool _secondPlayerOnEndStage = false;

	//���������� ���������� � ����� ����� � ������� ������
	char _firstPlayerChecksOut = 0;
	//���������� ���������� � ����� ����� � ������� ������
	char _secondPlayerChecksOut = 0;
};

