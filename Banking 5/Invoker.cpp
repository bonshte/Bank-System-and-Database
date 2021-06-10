#include "Invoker.h"
#include "CreateClientCommand.h"
#include "CreateNewCardCommand.h"
#include "CreateNewBalanceCommand.h"
#include "DeleteBalanceCommand.h"
#include "DeleteCardCommand.h"
#include "DeleteClientCommand.h"
#include "FullReportCommand.h"
#include "ReportForClientCommand.h"
#include "LoggoutCommand.h"
#include "ClearCommand.h"
Invoker* Invoker::instance = nullptr;
Invoker* Invoker::getInstance()
{
	if (instance == nullptr) 
		instance = new Invoker();
	return instance;
   
}

Invoker::~Invoker()
{
	eraseAllCommands();
	clearActor();
	clearCard();
}

string Invoker::NextCommand()
{
	cout << "Waiting For Next Command:";
	
	string next_command;
	cin >> next_command;
	
	if (Validator::SameCommands(next_command,"help")) {
		PrintAvailableCommands();
		return std::move(next_command);
	}
	for (size_t i = 0; i < commands.size(); ++i) {
		
		if (Validator::SameCommands(next_command, commands[i]->ReturnCommandName())) {
			
			if (commands[i]->execute(actor, card_inserted) == true) {
			cout << "Success" << endl;
			}
			else {
				cout << "Fail" << endl;
			}
			
			return next_command;
		}
	}
	for (size_t i = 0; i < actor_commands.size(); ++i) {

	
		if (Validator::SameCommands(next_command, actor_commands[i]->getCommandName())) {
			
			if (actor_commands[i]->execute_on_actor(actor) == true) {
				cout << "Success" << endl;
			}
			else {
				cout << "Failure" << endl;
			}
			return next_command;
		}
	}
	for (size_t i = 0; i < card_commands.size(); ++i) {
		if (Validator::SameCommands(next_command, card_commands[i]->getCommandName())) {
			if (card_commands[i]->execute(card_inserted) == true) {
				cout << "Success" << endl;
			}
			else {
				cout << "Fail" << endl;
			}
			return next_command;
		}
	}
	string exit = "Exit";
	if (!Validator::SameCommands(next_command, exit)) {
		cout << "Invalid Command , try 'help' for command list!" << endl;
	}
	return next_command;


	
	
		
}

void Invoker::PrintAvailableCommands()
{
	cout << "Available Commands:" << endl;
	for (size_t i = 0; i < commands.size(); ++i) {
		cout << commands[i]->ReturnCommandName() << " - " << commands[i]->description() << endl << endl;
	}
	for (size_t i = 0; i < actor_commands.size(); ++i) {
		cout << actor_commands[i]->getCommandName() << " - " << actor_commands[i]->description() << endl << endl;
	}
	
	for (size_t i = 0; i < card_commands.size(); ++i) {
		cout << card_commands[i]->getCommandName() << " - " << actor_commands[i]->description() << endl << endl;
	}
}

void Invoker::eraseAllCommands()
{
	for (size_t i = 0; i < commands.size(); ++i)
		delete commands[i];
	commands.clear();

	
	for (size_t i = 0; i < actor_commands.size(); ++i) {
		delete actor_commands[i];
	}
	actor_commands.clear();

	for (size_t i = 0; i < card_commands.size(); ++i) {
		delete card_commands[i];
	}
	card_commands.clear();

}

void Invoker::switchToAdmin()
{
	
	actor_commands.push_back(new HireCommand());
	actor_commands.push_back(new FireCommand());
	commands.push_back(new LoggoutCommand());
	commands.push_back(new ClearCommand());
}

void Invoker::switchToClient()
{
	
	card_commands.push_back(new CardCheckCommand());
	card_commands.push_back(new CardDepositCommand());
	card_commands.push_back(new CardWithdrawCommand());
	commands.push_back(new LoggoutCommand());
	commands.push_back(new ClearCommand());
}

void Invoker::switchToEmployee()
{
	
	actor_commands.push_back(new CreateClientCommand());
	actor_commands.push_back(new CreateNewBalanceCommand());
	actor_commands.push_back(new CreateNewCardCommand());
	actor_commands.push_back(new DeleteBalanceCommand());
	actor_commands.push_back(new DeleteCardCommand());
	actor_commands.push_back(new DeleteClientCommand());
	actor_commands.push_back(new FullReportCommand());
	actor_commands.push_back(new ReportForClientCommand());
	commands.push_back(new LoggoutCommand());
	commands.push_back(new ClearCommand());

}

void Invoker::SwitchToMain()
{
	
	commands.push_back(new LoginAsClientCommand());
	commands.push_back(new LoginAsAdminCommand());
	commands.push_back(new LoginAsEmployeeCommand());
	commands.push_back(new ClearCommand());
}

Invoker::Invoker()
{
	
	commands.push_back(new LoginAsAdminCommand());
	commands.push_back(new LoginAsEmployeeCommand());
	commands.push_back(new LoginAsClientCommand());
	commands.push_back(new ClearCommand());
	actor = nullptr;
	card_inserted = nullptr;
	
}

void Invoker::clearActor()
{
	delete actor;
	actor = nullptr;
}

void Invoker::clearCard()
{
	delete card_inserted;
	card_inserted = nullptr;
}
