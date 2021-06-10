#include "ClearCommand.h"


bool ClearCommand::execute(IAccount*& actor, Card*& card)
{
    system("cls");
    return true;
}

string ClearCommand::ReturnCommandName() const
{
    return "Clear";
}

string ClearCommand::description()
    {
        return "Clears the terminal";
    }
