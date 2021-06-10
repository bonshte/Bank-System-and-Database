#pragma once

#include <vector>
#include "Admin.h"
#include "Employee.h"
#include "Client.h"
#include "CardCheckCommand.h"
#include "CardDepositCommand.h"
#include "CardWithdrawCommand.h"
#include "ICommand.h"
#include "IActorCommand.h"
#include "LoginAsAdminCommand.h"
#include "LoginAsEmployeeCommand.h"
#include "HireCommand.h"
#include "FireCommand.h"
#include "LoggoutCommand.h"
#include "LoginAsClientCommand.h"


class Invoker {
	
	vector<ICommand*> commands;// komandi ot vida Login As
	vector<IActorCommand*> actor_commands;//komandi ot accounti
	vector<CardCommands*> card_commands;

	
	Card* card_inserted;
	IAccount* actor;
	
	static Invoker* instance;//tova durji invokera
protected:
	void PrintAvailableCommands();
	void eraseAllCommands();//deletes all commands
	void switchToAdmin();//admin menu
	void switchToClient();//client menu
	void switchToEmployee();//employee menu
	void SwitchToMain();//main menu
	Invoker();

	
	void clearActor();
	void clearCard();

public:
	friend LoginAsClientCommand;
	friend LoggoutCommand;
	friend LoginAsEmployeeCommand;
	friend LoginAsAdminCommand;
	static Invoker* getInstance();
	Invoker(const Invoker* other) = delete;
	Invoker& operator=(const Invoker& other) = delete;
	~Invoker();
	

	string NextCommand();
	
	

};