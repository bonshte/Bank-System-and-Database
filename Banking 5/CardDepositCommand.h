#pragma once
#include "CardCommands.h"
class CardDepositCommand :public CardCommands {
public:
	bool execute(Card* card)override;
	string getCommandName()const override;
	string description()const override;

};