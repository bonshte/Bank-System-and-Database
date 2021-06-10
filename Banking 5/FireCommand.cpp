#include "FireCommand.h"



bool FireCommand::execute_on_actor(IAccount* actor)
{
    Admin* action_taker = dynamic_cast<Admin*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong action taker on Fire");
    return action_taker->DeleteEmployee();
        
        
   
}

string FireCommand::getCommandName() const
{
    return "Fire";
}

string FireCommand::description() const
{
    return " Enter EGN for the employee you want to fire";
}
