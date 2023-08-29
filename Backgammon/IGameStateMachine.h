#pragma once

#include "GlobalDefinitions.h"

class IGameStateMachine
{
public:
	virtual void SwitchState(GameStateType nextState) = 0;
};

