#include "LoggoutCommand.h"
#include "Invoker.h"
string LoggoutCommand::ReturnCommandName() const
{
    return "LogOut";
}

bool LoggoutCommand::execute(IAccount*&, Card*& card)
{
    Invoker::getInstance()->eraseAllCommands();
    Invoker::getInstance()->SwitchToMain();
    Invoker::getInstance()->clearActor();
    Invoker::getInstance()->clearCard();
    return true;
}

string LoggoutCommand::description()
{
    return "Go to main menu";
}


