#pragma once

#include "IPlayer.h"

#include "Debug.h"

//���������� ����� ������
class AIPlayer : public IPlayer
{
public:
	//�����������
	AIPlayer(PlayerOrderType orderType, AiDifficulty difficulty, IGameStateMachine* stateMachine, Board* board);

	void OnTurnEnter() override;

	void OnEndTurnEnter() override;



	void OnUpdate() override;
	void OnEndUpdate() override;
	void OnTurnExit() override;

private:
	AiDifficulty _difficulty;
};

