#pragma once

#include "GlobalDefinitions.h"

#include "Window.h"
#include "Debug.h"
#include "Board.h"
#include "Dice.h"

#include "Input.h"

#include "GameStateMachine.h"
#include "GameBaseState.h"

//����� ����
//�������� ������ ��� ��������� �������� �����: �������������, ���������� � ���������
//������� ��� ����������� ��������
class Game
{
public:
	//�����������
	Game();
	//����������
	~Game();

	void Initialize();
	void Update();
	void Draw();

	bool IsOpened();

private:
	Window* _window;

	Board* _board;
	Dice* _dice;

	GameStateMachine* _stateMachine;
};

