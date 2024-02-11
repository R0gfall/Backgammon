#pragma once

#include <string>

#include <map>
#include <list>

//�������� ����
#define GAME_NAME "Backgammon"

//������� ���� � ��������
#define WINDOW_WIDTH 1366
#define WINDOW_HEIGHT 768

//���� � ������
#define BOARD_IMAGE_PATH "../Assets/board.png"
#define DICE_IMAGE_PATH "../Assets/dice.png"
#define FONT_PATH "../Assets/Montserrat-Black.ttf"
#define CHECK_IMAGE_PATH "../Assets/checks.png"

#define LOG_OUTPUT_FILENAME_START "../game_log_"
#define LOG_OUTPUT_FILENAME_END ".txt"

#define GLOBAL_SHOULD_LOG false
#define HUMAN_SHOULD_LOG false
#define AI_SHOULD_LOG false

const int FIRST_PLAYER_INIT_CELL = 0;
const int SECOND_PLAYER_INIT_CELL = 12;



//������������ ����� ���������
enum class GameStateType
{
	Initial,
	FirstPlayer,
	FirstPlayerEnd,
	SecondPlayer,
	SecondPlayerEnd,
	EndGame
};

//������ �����, ��������������� ������������ GameStateType
const std::string GAME_STATE_STRINGS[6] = { "INITIAL_STATE", "FIRST_PLAYER_STATE", "FIRST_PLAYER_END_STATE", "SECOND_PLAYER_STATE", "SECOND_PLAYER_END_STATE", "END_GAME_STATE" };

//������������ ����� ����������� �����
enum class PlayerOrderType
{
	//������ �����
	FirstPlayer,
	//������ �����
	SecondPlayer,
	None,
};

//������ �����, ��������������� ������������ PlayerOrderType
const std::string PLAYER_ORDER_TYPE_STRINGS[3] = { "FIRST PLAYER", "SECOND PLAYER", "NONE"};

//������������ ��������� ��
enum class AiDifficulty
{
	Easy,
	Hard
};

//������ �����, ��������������� ������������ AiDifficulty
const std::string AI_DIFFICULTY_STRINGS[2] = { "EASY", "HARD" };

//������������ ��������� ������
enum class CellStatus
{
	//������ ������ ������ �������
	FirstPlayer,
	//������ ������ ������ �������
	SecondPlayer,
	//������ ��������
	Free,
};

//������ �����, ��������������� ������������ CellStatus
const std::string CELL_STATUS_STRINGS[3] = { "FirstPlayer", "SecondPlayer", "Free" };

//������������ ����� ������
enum class CellType
{
	None,
	//������ ������� ������ (������ � id 0)
	FirstPlayerHead,
	//��� ������� ������ (������ � id �� 18 �� 23)
	FirstPlayerHome,
	//������ ������� ������ (������ � id 12)
	SecondPlayerHead,
	//��� ������� ������ (������ � id �� 6 �� 11)
	SecondPlayerHome,
};

//������������ ����� �����
enum class CheckType
{
	//����� ������� ������
	FirstPlayer,
	//����� ������� ������
	SecondPlayer,
	//����� ����� ��������� ���������� ����
	Hint
};

//��������� ��������� ������� ����� ������� � ������
const GameStateType GAME_INITIAL_STATE = GameStateType::Initial;

//������� ��������� �����
//���� - Id ������ 
//�������� - ������ Id ������ �� ������� ����� ���� ���������� �����
using PossibleTurns = std::map<short, std::list<short>>;

/// <summary>
/// ��������, ������� ���������� ����������� �� ����� ��������� ���������
/// </summary>
/// <param name="valueToClamp">����������� �����</param>
/// <param name="bottomBorder">������ ������� ������������</param>
/// <param name="topBorder">������� ������� �� ������������</param>
/// <returns></returns>
bool IsValueInBounds(short valueToClamp, short bottomBorder, short topBorder);