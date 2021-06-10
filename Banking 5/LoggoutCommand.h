#pragma once
#include "ICommand.h"
class Card;
class IAccount;
class LoggoutCommand :public ICommand {
public:
	string ReturnCommandName()const override;
	bool execute(IAccount*&, Card*& card)override;
	string description() override;
};