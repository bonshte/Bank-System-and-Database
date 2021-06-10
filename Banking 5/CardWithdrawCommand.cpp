#include "CardWithdrawCommand.h"
#include "Card.h"
bool CardWithdrawCommand::execute(Card* card)
{
    return card->withdraw();
}

 string CardWithdrawCommand::getCommandName() const
{
    return "Withdraw";
}

 string CardWithdrawCommand::description() const
 {
     return "withdraw funds from logged card";
 }
