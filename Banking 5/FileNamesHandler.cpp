#include "FileNamesHandler.h"

string FilesNamesHandler::GetPersonalBalancesFile(const string& owner_id)
{
	string result = "Balances" + owner_id + ".db";
	return result;
}

string FilesNamesHandler::GetTotalCardsFile(const string& id_owner)
{
	string result = "TotalCards" + id_owner + ".db";
	return result;
}

string FilesNamesHandler::GetTotalBalancesFile(const string& id_owner)
{
	string result = "TotalBalances" + id_owner + ".db";
	return result;
}

string FilesNamesHandler::GetTotalCardsForSpecificBalanceFile(const string& id_owner, const string& balance_id)
{
	string result = "CardsFor" + balance_id + id_owner + ".db";
	return result;
}

string FilesNamesHandler::getClientsDataBase()
{
	return "Clients.db";
}

string FilesNamesHandler::getEmployeesDataBase()
{
	return "Employees.db";
}

string FilesNamesHandler::getCardsDataBase()
{
	return "Cards.db";
}

string FilesNamesHandler::getAccountCounterFile()
{
	return "BankClientCount.db";
}
