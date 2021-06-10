#include "LoginAsEmployeeCommand.h"
#include "Invoker.h"
#include "FileManager.h"
#include "Account.h"


bool LoginAsEmployeeCommand::execute(IAccount*& actor, Card*& card)
{
	cout << "Loggin as Employee:" << endl;
	cout << "Enter username:" << endl;
	string username;
	cin >> username;
	cout << endl;
	string password;
	cout << "Enter password: " << endl;
	cin >> password;

	ifstream in("Employees.db");
	
	if (!in.is_open()) {
		cout << "currently no employees" << endl;
		return false;
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		cout << "All employees had been fired" << endl;
		return false;
	}
	
	while (in) {
		long long startPos = in.tellg();
		Employee current(in);
		if (username == current.getUsername() && BCrypt::validatePassword(password, current.getHashedPassword())) {
			in.seekg(startPos);
			actor = new Employee(in);
			in.close();
			Invoker::getInstance()->eraseAllCommands();
			Invoker::getInstance()->switchToEmployee();
			return true;
		}
		
		
		
		
		FileManager::ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	return false;
}

string LoginAsEmployeeCommand::ReturnCommandName() const
{
	return "LoginAsEmployee";
}

string LoginAsEmployeeCommand::description()
{
	return "Login as employee";
}
