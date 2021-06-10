#include "BCrypt.hpp"
#include <string>
#include <iostream>
#include "Validator.h"
#define DOCTEST_CONFIG_IMPLEMENT
#include "StringUtils.h"
#include "Card.h"
#include "test.h"
#include "Admin.h"
#include "PersonalInformation.h"
#include "Balance.h"
#include "Employee.h"
#include "Invoker.h"
#include "LoginAsAdminCommand.h"
using namespace std;
void run() {
	string exit = "Exit";
	string command = Invoker::getInstance()->NextCommand();

	while (!Validator::SameCommands(command, exit))
		command = Invoker::getInstance()->NextCommand();
	delete Invoker::getInstance();
}
int main() {
	
	
	run();
	
	
	
	
	//doctest::Context().run();
}