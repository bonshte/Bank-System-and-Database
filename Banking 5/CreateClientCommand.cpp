#include "CreateClientCommand.h"
#include "Employee.h"


bool CreateClientCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor on Create Client");
    return action_taker->createClientAccount();
}

string CreateClientCommand::getCommandName() const
{
    return "CreateClient";
}

string CreateClientCommand::description() const
{
    return "Fill information about new Client and create account";
}
