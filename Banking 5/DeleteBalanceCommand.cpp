#include "DeleteBalanceCommand.h"



bool DeleteBalanceCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor");
    return action_taker->deleteBalanceForClient();
}

string DeleteBalanceCommand::getCommandName() const
{
    return "DeleteBalance";
}

string DeleteBalanceCommand::description() const
{
    return "Enter EGN and id for the balance you want to delete";
}
