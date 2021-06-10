#include "FullReportCommand.h"


bool FullReportCommand::execute_on_actor(IAccount* actor)
{
    Employee* action_taker = dynamic_cast<Employee*>(actor);
    if (action_taker == nullptr)
        throw std::invalid_argument("wrong actor FullReportCommand");
   return  action_taker->FullReport();
}

string FullReportCommand::getCommandName() const
{
    return "FullReport";
}

string FullReportCommand::description() const
{
    return "Gives full report for all clients";
}
