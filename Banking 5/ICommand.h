#pragma once
#include <iostream>
using namespace std;
class Card;
class IAccount;
class ICommand {
public:
	virtual bool execute(IAccount*& actor,Card*& card) = 0;
	virtual string ReturnCommandName()const = 0;
	virtual ~ICommand() = default;
	virtual string description() = 0;
};