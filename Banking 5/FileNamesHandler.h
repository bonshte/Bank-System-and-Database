#pragma once
#include <string>
using namespace std;
class FileManager;
class Admin;
class Employee;
class FilesNamesHandler {
	friend FileManager;
	friend Admin;
	friend Employee;
	static string GetPersonalBalancesFile(const string& owner_id);
	static string GetTotalCardsFile(const string& id_owner);
	static string GetTotalBalancesFile(const string& id_owner);
	static string GetTotalCardsForSpecificBalanceFile(const string& id_owner, const string& balance_id);
	static string getClientsDataBase();
	static string getEmployeesDataBase();
	static string getCardsDataBase();
	static string getAccountCounterFile();
};