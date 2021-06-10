#include "FileManager.h"
#include <string>
#include <fstream>
#include <iostream>
#include "Balance.h"
#include "Card.h"
#include "FileNamesHandler.h"
#include "StringUtils.h"
using namespace std;

bool FileManager::validUserName(const string& name, const string& filename)
{
	ofstream out(filename.c_str(), ios::app);
	out.close();
	//to make sure such file exists

	
	ifstream in(filename.c_str());
	if (!in.is_open())
		throw std::invalid_argument("invalid file");
	//if the file is empty
	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();
		return true;
	}
	while (in) {
		//Client and Employee Both have the same ifstream constructor
		//not a problem to use Client
		Client current(in);
		if (current.getUsername() == name) {
			out.close();
			return false;
		}
		ReadTillEndOfLineInFile(in);

		if (in.peek() == EOF)
			break;

	}
	in.close();
	return true;
}

bool FileManager::EGNAlreadyInFile(const string& egn, const string& filename)
{
	ofstream out(filename.c_str(),ios::app);
	out.close();
	//make sure the file exists

	ifstream in(filename.c_str());
	
	if (!in.is_open())
		throw std::invalid_argument("invalid file");
	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();
		return false;
	}
	while (in) {
		Client current(in);
		if (current.getEGN() == egn) {
			in.close();
			return true;
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
		
	}
	in.close();
	return false;
}

bool FileManager::RemoveByEgn(const string& egn, const string& filename)
{
	ifstream in(filename.c_str());
	ofstream out("replacement");
	bool found = false;
	while (in) {
		Client current(in);
		
		if (current.getEGN() != egn) {
			out << current << '\n';
			
		}
		else {
			found = true;
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
		
	}
	
	in.close();
	out.close();
	std::remove(filename.c_str());
	std::rename("replacement", filename.c_str());
	return found;
}

void FileManager::AddToClientDataBase(const Client& clnt)
{
	ofstream out(FilesNamesHandler::getClientsDataBase().c_str(), ios::app);
	out << clnt << endl;
	out.close();
}

void FileManager::AddCardToCardsDataBase(const Card& card)
{
	ofstream out(FilesNamesHandler::getCardsDataBase().c_str(), ios::app);
	out << card << endl;
	out.close();
}

void FileManager::AddToEmployeeDataBase(const Employee& emp)
{
	ofstream out(FilesNamesHandler::getEmployeesDataBase().c_str(), ios::app);
	out << emp << endl;
	out.close();
}

void FileManager::ToPersonalDataBase(const Balance& balance)
{
	ofstream out(FilesNamesHandler::GetPersonalBalancesFile(balance.getOwner_ID()).c_str(), ios::app);
	out << balance << endl;
	out.close();
}

void FileManager::DecreaseCountInFile(int count, const string& filename)
{
	ifstream in(filename.c_str());
	if (!in.is_open())
		throw std::invalid_argument("File does not exist");
	int number;
	in >> number;
	if (number - count < 0)
		throw std::invalid_argument("DecreaseCountInFile goes into negative count");
	number -= count;
	in.close();
	ofstream out(filename.c_str(), ios::trunc);
	out << number;
	out.close();
}

void FileManager::IncreaseCountInFile(int count, const string& filename)
{
	ifstream in(filename.c_str());
	if (!in.is_open()) {
		// the file is does not exist yet
		in.close();
		ofstream out(filename.c_str());
		out << count;
		out.close();
		return;
	}
	int currentcount;
	in >> currentcount;
	currentcount += count;
	in.close();
	ofstream out(filename.c_str(), ios::trunc);
	out << currentcount;
	out.close();
}

bool FileManager::CheckBalanceExists(const string& owner_id,const string& balance_id)
{
	ofstream out(FilesNamesHandler::GetPersonalBalancesFile(owner_id).c_str(), ios::app);
	//make sure such file exists
	out.close();


	ifstream in(FilesNamesHandler::GetPersonalBalancesFile(owner_id).c_str());
	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();
		return false;//the file is empty
	}
	
	while (in) {
		Balance current(in);
		if (current.getBalanceID() == balance_id) {
			in.close();
			return true;
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	return false;
	
}

string FileManager::GetOwnerIDbyEGN(const string& egn, const string& filename)
{
	ifstream in(filename.c_str());
	if (!in.is_open()) {
		//file does not exist
		in.close();
		return string();
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();// the file is empty
		return string();
	}
	while (in) {
		//Client and Employee both have the same data members
		Client current(in);
		if (current.getEGN() == egn) {
			in.close();
			return StringUtils::TurnNumberIntoString(current.getId());
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	return string();
}

bool FileManager::DeleteCardFromCardsDB(const string& card_id)
{
	ifstream in(FilesNamesHandler::getCardsDataBase().c_str());
	if (!in.is_open()) {
		in.close();
		//File does not yet exist
		return false;
	}
	if (in.peek() == ifstream::traits_type::eof())
		return false;

	bool foundcard = false;
	ofstream out("Replacement");
	while (in) {
		Card current(in);
		if (current.getID() == card_id) {
			foundcard = true;
		}
		else {
			out << current << endl;
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	out.close();
	std::remove(FilesNamesHandler::getCardsDataBase().c_str());
	std::rename("Replacement", FilesNamesHandler::getCardsDataBase().c_str());

	return foundcard;
}

bool FileManager::DeleteBalanceFromPersonalBalances(const string& balance_id, const string& filename)
{
	ifstream in(filename.c_str());
	ofstream out("Replacement");
	bool found = false;
	if (!in.is_open())
		throw std::invalid_argument("File not found DeleteBalanceFromPersonalBalances");
	while (in) {
		Balance current(in);
		if (current.getBalanceID() == balance_id) {
			found = true;
		}
		else {
			out << current << endl;
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	out.close();
	std::remove(filename.c_str());
	std::rename("Replacement", filename.c_str());
	return found;
}

int FileManager::DeleteAllCardsForGivenBalance(const string& balance_id)
{
	ofstream out_test(FilesNamesHandler::getCardsDataBase().c_str(), ios::app);
	out_test.close();
	//make sure the file exists

	int totalDeleted = 0;
	ifstream in(FilesNamesHandler::getCardsDataBase().c_str());


	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();
		return totalDeleted;
	}
	ofstream out("Replacement");
	while (in) {
		Card current(in);
		if (current.getAssociatedBalanceId() == balance_id) {
			totalDeleted++;
		}
		else {
			out << current << endl;
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	out.close();
	std::remove(FilesNamesHandler::getCardsDataBase().c_str());
	std::rename("Replacement", FilesNamesHandler::getCardsDataBase().c_str());
	return totalDeleted;
	
}

int FileManager::GetCountInFile(const string& filename)
{
	ifstream in(filename.c_str());
	if (!in.is_open())
		return 0;
	if (in.peek() == ifstream::traits_type::eof())
		return 0;
	int count;
	in >> count;

	in.close();
	return count;
}

double FileManager::getMoneyInBalance(const string& balance_id, const string& owner_id)
{
	ifstream in(FilesNamesHandler::GetPersonalBalancesFile(owner_id));
	if (!in.is_open())
		throw std::invalid_argument("Could not open File");
	if (in.peek() == ifstream::traits_type::eof())
		throw std::invalid_argument("getMoneyInBalance cannot find client balance file");

	while (in) {
		Balance current(in);
		if (current.getBalanceID() == balance_id) {
			in.close();
			return current.getMoneyInBalance();
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	throw std::invalid_argument("GetMoneyInBalance Balance not found");
}

void FileManager::SetMoneyInBalance(double money, const string& balance_id, const string& owner_id)
{
	if (money < 0)
		throw std::invalid_argument("Setmoney cannot set to negative");
	ifstream in(FilesNamesHandler::GetPersonalBalancesFile(owner_id).c_str());
	if (!in.is_open())
		throw std::logic_error("Inserting money to balance from card which does not exist");
	if(in.peek() == ifstream::traits_type::eof())
		throw std::logic_error("Inserting money to balance from card which does not exist");
	ofstream out("Replacement");
	while (in) {
		Balance current(in);
		if (current.getBalanceID() == balance_id) {
			current.setMoneyInBalance(money);
		}
		out << current << endl;
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	out.close();
	std::remove(FilesNamesHandler::GetPersonalBalancesFile(owner_id).c_str());
	std::rename("Replacement", FilesNamesHandler::GetPersonalBalancesFile(owner_id).c_str());

}

int FileManager::PrintCardsForBalance(const string& balance_id)
{
	int count = 0;
	ifstream in(FilesNamesHandler::getCardsDataBase().c_str());
	if (!in.is_open()) {
		cout << "No cards for this balance" << endl;
		in.close();
		return 0;
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		cout << "No cards for this balance" << endl;
		in.close();
		return 0;
	}
	while (in) {
		Card current(in);
		if (current.getAssociatedBalanceId() == balance_id) {
			count++;
			current.Print();
		}
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	
	return count;

}

void FileManager::PrintBalancesAndCardsForClient(const string& client_id)
{
	ifstream in(FilesNamesHandler::GetPersonalBalancesFile(client_id).c_str());
	if (!in.is_open()) {
		cout << "File not found" << endl;
		in.close();
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		cout << "No balances found" << endl;
		return;
	}
	int totalcount = 0;
	while (in) {
		Balance current(in);
		current.Print();
		int current_Count =PrintCardsForBalance(current.getBalanceID());
		cout << "Cards For this balance: " << current_Count << endl;
		totalcount += current_Count;
		ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;

	}
	in.close();
	cout << "Total Cards for This Account: " << totalcount << endl;

	
}

int FileManager::GetCreatedAccountsAllTime()
{
	
		ifstream in(FilesNamesHandler::getAccountCounterFile().c_str());
		if (!in.is_open()) {
			in.close();
			return 0;
		}
		if (in.peek() == ifstream::traits_type::eof())
			throw std::logic_error("File With Accounts Count Empty!");
		int count;
		in >> count;
		in.close();
		return count;
	
}

void FileManager::IncrementBankCounterAccounts()
{
	ofstream out_test(FilesNamesHandler::getAccountCounterFile().c_str(), ios::app);
	out_test.close();

	int count;
	ifstream in(FilesNamesHandler::getAccountCounterFile().c_str());
	if (in.peek() == ifstream::traits_type::eof()) {
		count = 0;
	}
	else {
		in >> count;
	}
	in.close();
	ofstream out(FilesNamesHandler::getAccountCounterFile().c_str(), ios::trunc);
	out << count + 1;
	out.close();
}



void FileManager::ReadTillEndOfLineInFile(ifstream& in)
{
	if (!in.is_open())
		throw std::invalid_argument("closed stream passed to read till end of line");
	char transmitter = '\0';
	while (transmitter != '\n')
		in.get(transmitter);


}


