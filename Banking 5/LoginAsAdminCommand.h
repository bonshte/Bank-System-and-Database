#pragma once
#include "ICommand.h"

class LoginAsAdminCommand :public ICommand {
	string getHashedAdmin();
public:
	bool execute(IAccount*& actor,Card*& card)override;
	string ReturnCommandName()const override;
	string description()override;
	
};