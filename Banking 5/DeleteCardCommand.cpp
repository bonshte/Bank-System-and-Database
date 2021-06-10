#include "DeleteCardCommand.h"



bool DeleteCardCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor");
    return action_taker->deleteCardForClient();
    
}

string DeleteCardCommand::getCommandName() const
{
    return "DeleteCard";
}

string DeleteCardCommand::description() const
{
    return "Enter EGN,  balance ID and then the Card ID you want to delete";
}
