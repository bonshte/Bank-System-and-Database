#pragma once
#include "ICommand.h"
class IAccount;
class Card;
class LoginAsClientCommand :public ICommand {
	bool execute(IAccount*& actor, Card*& card)override;
	string ReturnCommandName()const override;
	string description()override;
};