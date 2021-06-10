#include "LoginAsAdminCommand.h"
#include "Invoker.h"
#include "BCrypt.hpp"



string LoginAsAdminCommand::getHashedAdmin()
{
	return BCrypt::generateHash("admin");
}

bool LoginAsAdminCommand::execute(IAccount*& actor, Card*& card)
{
	cout << "Logging as Admin:" << endl;
	cout << "Enter username:" << endl;
	string username;
	cin >> username;
	cout << endl;
	string password;
	cout << "Enter password: " << endl;
	cin >> password;

	if (username == "admin" && BCrypt::validatePassword(password,getHashedAdmin())) {
		actor = new Admin();
		Invoker::getInstance()->eraseAllCommands();
		Invoker::getInstance()->switchToAdmin();
		return true;
	}
	return false;
}

string LoginAsAdminCommand::ReturnCommandName() const
{
	return "LoginAsAdmin";
}

string LoginAsAdminCommand::description()
{
	return "Log as administrator";
}


