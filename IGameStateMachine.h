#pragma once

#include "GlobalDefinitions.h"

//Интерфейс машины состояний
//Нужен для того, чтобы состояния могли переключаться
class IGameStateMachine
{
public:
	virtual void SwitchState(GameStateType nextState) = 0;
};

