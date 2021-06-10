#include "CardDepositCommand.h"
#include "Card.h"
bool CardDepositCommand::execute(Card* card)
{
    return card->insertMoney();
}

 string CardDepositCommand::getCommandName() const
{
    return "Deposit";
}

 string CardDepositCommand::description() const
 {
     return "deposit money in logged card";
 }
