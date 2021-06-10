#pragma once
#include <string>
class Card;
using namespace std;
class CardCommands {
public:
	virtual bool execute(Card* card) = 0;
	virtual string getCommandName()const = 0;
	virtual string description() const = 0;
};