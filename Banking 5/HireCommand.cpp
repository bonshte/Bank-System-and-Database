#include "HireCommand.h"
#include "Admin.h"


bool HireCommand::execute_on_actor(IAccount* actor)
{
    Admin* action_taker = dynamic_cast<Admin*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong action taker on Hire");
  return action_taker->CreateNewEmployee();
    
       
    

}

string HireCommand::getCommandName() const
{
    return "Hire";
}

string HireCommand::description() const
{
    return "Enter Information for new Employee";
}
