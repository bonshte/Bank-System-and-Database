#pragma once
#include <string>
#include "Client.h"
#include "Employee.h"
#include "Card.h"
using namespace std;

class FileManager {
public:
	FileManager() = delete;

	 static bool validUserName(const string& name,const string& filename);
	 //Checks if the given name is already in use in the database
	 static bool EGNAlreadyInFile(const string& egn, const string& filename);
	 //Checks if EGN is in file
	 static bool RemoveByEgn(const string& egn,const string& filename);
	 //Removes the egn from the file
	 static void AddToClientDataBase(const Client& clnt);
	 //appens Client to the DataBase
	 static void AddCardToCardsDataBase(const Card& card);
	 //appends Card to the DataBase
	 static void AddToEmployeeDataBase(const Employee& emp);
	 //appends Employee to the DataBase
	 static void ToPersonalDataBase(const Balance& balance);
	 //appends to PersonalBalances
	 static void DecreaseCountInFile(int count, const string& filename);
	 //Decreases the count in file by the amount given
	 static void IncreaseCountInFile(int count, const string& filename);
	 //Increases the count in file by the amount given
	 static bool CheckBalanceExists(const string& owner_id,const string& balance_id);
	 //Checks if such balance exists
	 static string GetOwnerIDbyEGN(const string& egn, const  string& filename);
	 //return the ID of the Person if found,else empty string
	 static bool DeleteCardFromCardsDB(const string& card_id);
	 //Deletes Card if found and return boolean
	 static bool DeleteBalanceFromPersonalBalances(const string& balance_id, const string& filename);
	 //Deletes Balance from Personal Balances
	 static int DeleteAllCardsForGivenBalance(const string& balance_id);
	 //Deletes all the cards for this balance
	 static int GetCountInFile(const string& filename);
	 //Return the Number in the file
	 static double getMoneyInBalance(const string& balance_id, const string& owner_id);
	 //returns the money in this balance
	 static void SetMoneyInBalance(double money, const string& balance_id, const string& owner_id);
	 //Sets the amount of money in the balance
	 static int PrintCardsForBalance(const string& balance_id);
	 //Prints all Cards attached to this balance and return the count
	 static void PrintBalancesAndCardsForClient(const string& client_id);
	 
	 static int GetCreatedAccountsAllTime();
	 //returns file where accounts are counted
	 static void IncrementBankCounterAccounts();

	 static void ReadTillEndOfLineInFile(ifstream& in);
};