#pragma once
#include "Account.h"
class IActorCommand {
public:
	virtual bool execute_on_actor(IAccount* actor) = 0;
	virtual string getCommandName()const = 0;
	virtual ~IActorCommand() = default;
	virtual string description() const = 0;
};