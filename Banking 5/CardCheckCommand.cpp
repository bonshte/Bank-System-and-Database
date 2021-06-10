#include "CardCheckCommand.h"
#include "Card.h"
bool CardCheckCommand::execute(Card* card)
{
    return card->CheckBalance();
}

string CardCheckCommand::getCommandName() const
{
    return "Check";
}

string CardCheckCommand::description() const
{
    return "Check Balance on logged card";
}
