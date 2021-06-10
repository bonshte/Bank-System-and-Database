#pragma once

#include "IActorCommand.h"
#include "Employee.h"
class CreateNewBalanceCommand :public IActorCommand {
public:
	bool execute_on_actor(IAccount* actor)override;
	string getCommandName()const override;
	string description()const override;
};