#include "DeleteClientCommand.h"



bool DeleteClientCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor");
    return action_taker->deleteClientAccount();
}

string DeleteClientCommand::getCommandName() const
{
    return "DeleteClient";
}

string DeleteClientCommand::description() const
{
    return " Enter EGN for client to remove from Bank";
}
