#pragma once
#include "Account.h"
#include "PersonalInformation.h"
#include <fstream>

class Employee :public IAccount,public PersonalInformation {

	
public:
	Employee() = delete;
	Employee(const string& username, const string& password, const string& egn,
		const string& f_name, const string& m_name, const string& l_name,
		const string& addr, const string& p_number, const DateTime& birth);
	bool operator==(const Employee& other);
	Employee& operator=(const Employee& other) = delete;
	~Employee() = default;
	Employee(ifstream& in);

	friend ofstream& operator<<(ofstream& out, const Employee& other);
	friend ifstream& operator>>(ifstream& in, Employee& other);
	
	void Print()const override;

	bool createClientAccount();
	bool deleteClientAccount();
	bool createNewBalanceForClient();
	bool createNewCardForBalance();
	bool deleteBalanceForClient();
	bool deleteCardForClient();
	bool FullReport();
	bool PersonalReport();

	
};