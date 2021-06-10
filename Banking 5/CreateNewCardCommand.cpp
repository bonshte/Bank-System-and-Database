#include "CreateNewCardCommand.h"



bool CreateNewCardCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor");
   return action_taker->createNewCardForBalance();
}

string CreateNewCardCommand::getCommandName() const
{
    return "createCard";
}

string CreateNewCardCommand::description() const
{
    return "Enter EGN for client and Balance on which to create a new card";
}
