#include "Employee.h"
#include "Client.h"
#include "FileNamesHandler.h"
#include "FileManager.h"
#include "Balance.h"


Employee::Employee(const string& username, const string& password,
	const string& egn, const string& f_name,
	const string& m_name, const string& l_name,
	const string& addr, const string& p_number,
	const DateTime& birth) :
	IAccount(username, password),
	PersonalInformation(egn, f_name, m_name, l_name, p_number, addr, birth){}

bool Employee::operator==(const Employee& other)
{
	return PersonalInformation::operator==(other) && IAccount::operator==(other);
}

Employee::Employee(ifstream& in):IAccount(),PersonalInformation()
{
	readFromFileInformation(in);
	readFromFileAccount(in);
}





void Employee::Print() const
{
	IAccount::Print();
	PersonalInformation::Print();
}

bool Employee::createClientAccount()
{
	string username;
	cout << "Enter username:" << endl;
	cin >> username;
	cout << endl;
	while (username.empty() || 
		!FileManager::validUserName(username,FilesNamesHandler::getClientsDataBase().c_str())) {
		cout << "this username is taken, pick another one" << endl;
		cin >> username;
		cout << endl;
	}
	cout << "Choosed password:" << endl;
	string password;
	cin >> password;
	cout << endl;
	while (!Validator::ViablePassword(password)) {
		cout << "password must be atleast 6 symbols, pick another one!" << endl;
		cin >> password;
		cout << endl;
	}
	cout << "Enter EGN: ";
	string egn_input;
	cin >> egn_input;
	cout << endl;
	while (!Validator::ValidEGN(egn_input)) {
		cout << "invalid egn_input, enter again!" << endl;
		cin >> egn_input;
		cout << endl;
	}
	if (FileManager::EGNAlreadyInFile(egn_input,FilesNamesHandler::getClientsDataBase().c_str()))
		return false;
	
	string firstname;
	string middlename;
	string lastname;
	cout << "Enter first name: " << endl;
	cin >> firstname;
	cout << endl;
	while (firstname.empty()) {
		cout << "this field cannot be empty,enter again!" << endl;
		cin >> firstname;
		cout << endl;
	}
	cout << "Enter middle name: " << endl;
	cin >> middlename;
	cout << endl;
	while (middlename.empty()) {
		cout << "this field cannot be empty,enter again!" << endl;
		cin >> middlename;
		cout << endl;
	}
	cout << "Enter last name: " << endl;
	cin >> lastname;
	cout << endl;
	while (lastname.empty()) {
		cout << "this field cannot be empty,enter again!" << endl;
		cin >> lastname;
		cout << endl;
	}
	cout << "Enter date of birth in format: Year Month Day" << endl;
	int year = Validator::EnterValidInteger();
	int month = Validator::EnterValidInteger();
	int day = Validator::EnterValidInteger();
	DateTime resultDate(year, month, day);
	while (!resultDate.isValidTime()) {
		cout << "Invalid date,enter again" << endl;
		year = Validator::EnterValidInteger();
		month = Validator::EnterValidInteger();
		day = Validator::EnterValidInteger();
		resultDate.setYear(year);
		resultDate.setMonth(month);
		resultDate.setDay(day);
	}
	cout << "Enter phone number:" << endl;
	string phone;
	cin >> phone;
	cout << endl;
	while (!Validator::ValidPhoneNumber(phone)) {
		cout << "Invalid Phone number,enter again!" << endl;
		cin >> phone;
		cout << endl;
	}
	cout << "Enter address: " << endl;
	string addr;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, addr);
	while (addr.empty()) {
		cout << "this field cannot be empty,enter again!" << endl;
		getline(cin, addr);
		cout << endl;
	}
	
	Client result(username, password, egn_input, firstname, middlename, lastname, addr, phone, resultDate);
	FileManager::AddToClientDataBase(result);
	FileManager::IncrementBankCounterAccounts();
	return true;
}

bool Employee::deleteClientAccount()
{
	cout << "Enter EGN: ";
	string egn_input;
	cin >> egn_input;
	cout << endl;
	while (!Validator::ValidEGN(egn_input)) {
		cout << "invalid egn_input, enter again!" << endl;
		cin >> egn_input;
		cout << endl;
	}
	//check if such user is registered
	if (!FileManager::EGNAlreadyInFile(egn_input, FilesNamesHandler::getClientsDataBase()))
		return false;
	//get his ID
	string client_id = FileManager::GetOwnerIDbyEGN(egn_input, FilesNamesHandler::getClientsDataBase());
	//delete the user
	bool deleted = FileManager::RemoveByEgn(egn_input, FilesNamesHandler::getClientsDataBase().c_str());
	if (deleted) {
		int totalCardsDeleted = 0;
		int totalBalancesDeleted = 0;
		//open file with balances to make sure it exists
		ofstream out_test(FilesNamesHandler::GetPersonalBalancesFile(client_id).c_str(), ios::app);
		out_test.close();
		//if it cannot be read throw exception
		ifstream in(FilesNamesHandler::GetPersonalBalancesFile(client_id).c_str());
		if (!in.is_open()) {
			in.close();
			throw std::exception("Cannot open personal balance database");
		}
		//if it is empty -> the client has no balances -> no cards
		if (in.peek() == EOF) {
			in.close();
			return deleted;
		}
		while (in) {
			//Get balance from the file
			Balance current(in);
			
			FileManager::DeleteAllCardsForGivenBalance(current.getBalanceID());
			std::remove(FilesNamesHandler::GetTotalCardsForSpecificBalanceFile(client_id, current.getBalanceID()).c_str());
			
			//delete the file holding the information about the amount of cards in the current balance


			FileManager::ReadTillEndOfLineInFile(in);
			if (in.peek() == EOF)
				break;
		}
		in.close();
		std::remove(FilesNamesHandler::GetPersonalBalancesFile(client_id).c_str());
		std::remove(FilesNamesHandler::GetTotalBalancesFile(client_id).c_str());
		std::remove(FilesNamesHandler::GetTotalCardsFile(client_id).c_str());

	}
	
	return deleted;
}

bool Employee::createNewBalanceForClient()
{
	//Enter EGN
	string EGN;
	cout << "Client EGN:" << endl;
	cin >> EGN;
	cout << endl;
	//Check for misstype
	while(!Validator::ValidEGN(EGN)) {
		cout << "Invalid EGN , enter again:" << endl;
		cin >> EGN;
		cout << endl;
	}
	//Check if such EGN exists in the database
	if (!FileManager::EGNAlreadyInFile(EGN,FilesNamesHandler::getClientsDataBase().c_str()))
		return false;
	//find username for the client
	string clientID = FileManager::GetOwnerIDbyEGN(EGN,FilesNamesHandler::getClientsDataBase().c_str());
	//Find How Many balances does he have
	int balances = FileManager::GetCountInFile(FilesNamesHandler::GetTotalBalancesFile(clientID));
	cout << "Enter Initial Funds:" << endl;
	double funds = Validator::EnterValidDouble();
	while (funds < 0) {
		cout << "Dunds cannot be negative,enter again" << endl;
		funds = Validator::EnterValidDouble();
	}
	int IDClient = stoi(clientID);
	
	Balance result(EGN, balances, funds, IDClient);
	FileManager::ToPersonalDataBase(result);
	FileManager::IncreaseCountInFile(1, FilesNamesHandler::GetTotalBalancesFile(result.getOwner_ID()));
	//saved to PersonalBalances
	cout << result.getBalanceID() << endl;
	return true;
}

bool Employee::createNewCardForBalance()
{
	string EGN;
	cout << "Client EGN:" << endl;
	cin >> EGN;
	cout << endl;
	//Check for misstype
	while (!Validator::ValidEGN(EGN)) {
		cout << "Invalid EGN , enter again:" << endl;
		cin >> EGN;
		cout << endl;
	}
	//Check if such EGN exists in the database
	if (!FileManager::EGNAlreadyInFile(EGN, FilesNamesHandler::getClientsDataBase().c_str()))
		return false;
	string client_id = FileManager::GetOwnerIDbyEGN(EGN, FilesNamesHandler::getClientsDataBase());

	cout << "Enter Balance ID:" << endl;
	string balance_id;
	cin >> balance_id;
	if (!FileManager::CheckBalanceExists(client_id, balance_id)) {
		cout << "Balance not found" << endl;
		return false;
	}
	int TotalCountCards = FileManager::GetCountInFile(FilesNamesHandler::GetTotalCardsFile(client_id));
	FileManager::IncreaseCountInFile(1, FilesNamesHandler::GetTotalCardsFile(client_id));
	FileManager::IncreaseCountInFile(1, FilesNamesHandler::GetTotalCardsForSpecificBalanceFile(client_id,balance_id));
	Card result(EGN, TotalCountCards, balance_id, stoi(client_id));
	FileManager::AddCardToCardsDataBase(result);
	return true;
}

bool Employee::deleteBalanceForClient()
{
	string EGN;
	cout << "Client EGN:" << endl;
	cin >> EGN;
	cout << endl;
	//Check for misstype
	while (!Validator::ValidEGN(EGN)) {
		cout << "Invalid EGN , enter again:" << endl;
		cin >> EGN;
		cout << endl;
	}
	//Check if such EGN exists in the database
	if (!FileManager::EGNAlreadyInFile(EGN, FilesNamesHandler::getClientsDataBase().c_str()))
		return false;
	string client_id = FileManager::GetOwnerIDbyEGN(EGN, FilesNamesHandler::getClientsDataBase());

	cout << "Enter Balance ID:" << endl;
	string balance_id;
	cin >> balance_id;
	cout << endl;
	if (!FileManager::CheckBalanceExists(client_id, balance_id)) {
		cout << "Balance not found" << endl;
		return false;
	}
	
	bool deleted = FileManager::DeleteBalanceFromPersonalBalances(balance_id, FilesNamesHandler::GetPersonalBalancesFile(client_id));
		

	if (deleted) {
		FileManager::DecreaseCountInFile(1, FilesNamesHandler::GetTotalBalancesFile(client_id));
		int countDeleted = FileManager::DeleteAllCardsForGivenBalance(balance_id);
		FileManager::DecreaseCountInFile(countDeleted, FilesNamesHandler::GetTotalCardsFile(client_id));
		std::remove(FilesNamesHandler::GetTotalCardsForSpecificBalanceFile(client_id, balance_id).c_str());
	}
	
	return deleted;
}

bool Employee::deleteCardForClient()
{
	string EGN;
	cout << "Client EGN:" << endl;
	cin >> EGN;
	cout << endl;
	//Check for misstype
	while (!Validator::ValidEGN(EGN)) {
		cout << "Invalid EGN , enter again:" << endl;
		cin >> EGN;
		cout << endl;
	}
	//Check if such EGN exists in the database
	if (!FileManager::EGNAlreadyInFile(EGN, FilesNamesHandler::getClientsDataBase().c_str()))
		return false;
	string client_id = FileManager::GetOwnerIDbyEGN(EGN, FilesNamesHandler::getClientsDataBase());

	cout << "Enter Balance ID:" << endl;
	string balance_id;
	cin >> balance_id;
	cout << endl;
	if (!FileManager::CheckBalanceExists(client_id, balance_id)) {
		cout << "Balance not found" << endl;
		return false;
	}
	string card_id;
	cout << "Enter Card_id" << endl;
	cin >> card_id;
	cout << endl;
	bool deleted = FileManager::DeleteCardFromCardsDB(card_id);
	if (!deleted) {
		cout << "Card not found" << endl;
		return false;
	}
	FileManager::DecreaseCountInFile(1, FilesNamesHandler::GetTotalCardsFile(client_id));
	FileManager::DecreaseCountInFile(1, FilesNamesHandler::GetTotalCardsForSpecificBalanceFile(client_id,balance_id));

	return true;
	
}

bool Employee::FullReport()
{
	ofstream out(FilesNamesHandler::getClientsDataBase().c_str(), ios::app);
	out.close();
	//make sure the file exists

	ifstream in(FilesNamesHandler::getClientsDataBase().c_str());
	if (!in.is_open()) {
		cout << "File does not exist" << endl;
		return false;
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		cout << "File is empty" << endl;
		return false;
	}
	while (in) {
		Client current(in);
		cout <<"EGN:"<< current.getEGN() << endl;
		cout << "Balance accounts:" <<
			FileManager::GetCountInFile(FilesNamesHandler::GetTotalBalancesFile
			(StringUtils::TurnNumberIntoString(current.getId()).c_str())) << endl;
		cout << "Cards: " << FileManager::GetCountInFile
		(FilesNamesHandler::GetTotalCardsFile(StringUtils::TurnNumberIntoString(current.getId()))) << endl << endl;
		
		//FileManager::PrintBalancesAndCardsForClient(StringUtils::TurnNumberIntoString(current.getId()));
		FileManager::ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	return true;
}

bool Employee::PersonalReport()
{
	string EGN;
	cout << "Client EGN:" << endl;
	cin >> EGN;
	cout << endl;
	//Check for misstype
	while (!Validator::ValidEGN(EGN)) {
		cout << "Invalid EGN , enter again:" << endl;
		cin >> EGN;
		cout << endl;
	}
	//Check if such EGN exists in the database
	if (!FileManager::EGNAlreadyInFile(EGN, FilesNamesHandler::getClientsDataBase().c_str()))
		return false;
	string client_id = FileManager::GetOwnerIDbyEGN(EGN, FilesNamesHandler::getClientsDataBase());

	ifstream in(FilesNamesHandler::GetPersonalBalancesFile(client_id));
	
	if (!in.is_open()) {
		cout << "No balances Found";
		in.close();
		return false;
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		cout << "All Balances had been deleted" << endl;
		return false;
	}
	while (in) {
		Balance current(in);
		current.Print();
		FileManager::PrintCardsForBalance(current.getBalanceID());
		FileManager::ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	return true;
}





ofstream& operator<<(ofstream& out, const Employee& other)
{

	other.WriteToFileInformation(out);
	other.writeToFileAccount(out);
	return out;
}

ifstream& operator>>(ifstream& in, Employee& other)
{
	other.readFromFileInformation(in);
	other.readFromFileAccount(in);
	return in;
}
