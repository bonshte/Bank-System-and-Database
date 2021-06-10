#include "Client.h"
#include <iostream>
using namespace std;


Client::Client(ifstream& in):IAccount(),PersonalInformation()
{
	in >> *this;
}

Client::Client(const string& username, const string& password,
	const string& egn, const string& f_name,
	const string& m_name, const string& l_name,
	const string& addr, const string& p_number,
	const DateTime& birth):IAccount(username,password),
	PersonalInformation(egn,f_name,m_name,l_name,p_number,addr,birth){}

void Client::Print() const
{
	IAccount::Print();
	PersonalInformation::Print();
}

ofstream& operator<<(ofstream& out, const Client& other)
{
	other.WriteToFileInformation(out);
	other.writeToFileAccount(out);
	return out;
}

ifstream& operator>>(ifstream& in, Client& other)
{
	other.readFromFileInformation(in);
	other.readFromFileAccount(in);
	return in;
}
