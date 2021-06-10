#include "Admin.h"
#include <limits.h>
#include "DateTIme.h"
#include "Employee.h"















bool Admin::CreateNewEmployee()
{
	string username;
	cout << "Enter username:" << endl;
	cin >> username;
	cout << endl;
	while (username.empty() || 
		!FileManager::validUserName(username,FilesNamesHandler::getEmployeesDataBase().c_str())) {
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
	if (FileManager::EGNAlreadyInFile(egn_input, FilesNamesHandler::getEmployeesDataBase())) {
		cout << "Employee with such EGN exists!" << endl;
		return false;
	}
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
	char addr_buffer[100];
	string addr;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	getline(cin, addr);
	while (addr.empty()) {
		cout << "this field cannot be empty,enter again!" << endl;
		getline(cin, addr);
		cout << endl;
	}
	
	Employee result(username, password, egn_input, firstname, middlename, lastname, addr, phone, resultDate);
	FileManager::AddToEmployeeDataBase(result);
	FileManager::IncrementBankCounterAccounts();
	return true;


}

bool Admin::DeleteEmployee()
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
	if (!FileManager::EGNAlreadyInFile(egn_input, FilesNamesHandler::getEmployeesDataBase()))
		return false;

	return FileManager::RemoveByEgn(egn_input, FilesNamesHandler::getEmployeesDataBase().c_str());
}

void Admin::Print() const
{
	cout << "Status: Admin" << endl;
	cout << getUsername() << endl;

}

ofstream& operator<<(ofstream& out, const Admin& other)
{
	other.writeToFileAccount(out);
	return out;
}

ifstream& operator>>(ifstream& in, Admin& other)
{
	other.readFromFileAccount(in);
	return in;
}
