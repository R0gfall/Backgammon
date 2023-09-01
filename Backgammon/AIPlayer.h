#pragma once

#include "IPlayer.h"

#include "Debug.h"

//Конкретный класс игрока
class AIPlayer : public IPlayer
{
public:
	//Конструктор
	AIPlayer(PlayerOrderType orderType, IGameStateMachine* stateMachine, Board* board);

	void OnTurnEnter() override;
	void OnEndTurnEnter() override;
	void OnUpdate() override;
	void OnEndUpdate() override;
	void OnTurnExit() override;

private:

};

