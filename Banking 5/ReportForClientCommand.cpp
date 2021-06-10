#include "ReportForClientCommand.h"



bool ReportForClientCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong action taker on Hire");
    return action_taker->PersonalReport();
}

string ReportForClientCommand::getCommandName() const
{
    return "ReportForClient";
}

string ReportForClientCommand::description() const
{
    return "Get Report For Client by EGN";
}
