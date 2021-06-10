#pragma once
#include "ICommand.h"
class ClearCommand :public ICommand {
public:
	bool execute(IAccount*& actor, Card*& card)override;
	string ReturnCommandName()const override;
	string description()override;
};