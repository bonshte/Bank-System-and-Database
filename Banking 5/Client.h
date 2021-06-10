#pragma once
#include "Account.h"
#include "PersonalInformation.h"



class Client :public IAccount, public PersonalInformation {
public:
	Client(ifstream& in);
	Client() = delete;
	Client(const string& username, const string& password, const string& egn,
		const string& f_name, const string& m_name, const string& l_name,
		const string& addr, const string& p_number, const DateTime& birth);
	
	Client& operator=(const Client& other) = delete;
	~Client() = default;
	
	friend ofstream& operator<<(ofstream& out, const Client& other);
	friend ifstream& operator>>(ifstream& in, Client& other);

	void Print()const override;

};