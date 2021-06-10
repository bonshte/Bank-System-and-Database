#pragma once
#include "ICommand.h"

class IAccount;
class Card;
class LoginAsEmployeeCommand :public ICommand {
public:
	bool execute(IAccount*& actor,Card*& card)override;
	string ReturnCommandName()const override;
	string description()override;
};