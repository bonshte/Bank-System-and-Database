#include "CreateNewBalanceCommand.h"



bool CreateNewBalanceCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor");
    return action_taker->createNewBalanceForClient();
}

string CreateNewBalanceCommand::getCommandName() const
{
    return "CreateBalance";
}

string CreateNewBalanceCommand::description() const
{
    return "Enter EGN and create balance for the client with initial funds";
}
