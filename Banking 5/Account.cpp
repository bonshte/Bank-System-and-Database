#include "Account.h"
#include "StringUtils.h"

IAccount::IAccount(const IAccount& other)
{
	account_username = other.account_username;
	account_hashedpassword = other.account_hashedpassword;
}

IAccount::IAccount(const string& username, const string& password)
{
	try
	{
		setPassWord(password);
		setUserName(username);
		
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		throw ex;
	}
}
bool IAccount::operator==(const IAccount& other)
{
	return account_username == other.account_username && account_hashedpassword == other.account_hashedpassword;
}
void IAccount::Print()const {
	cout << account_username << endl;
	cout << account_hashedpassword << endl;
}

IAccount::IAccount()
{
	account_username = "admin";
	account_hashedpassword = BCrypt::generateHash("admin");

}

const string& IAccount::getUsername() const
{
	return account_username;
}

const string& IAccount::getHashedPassword() const
{
	return account_hashedpassword;
}

void IAccount::setUserName(const string& other)
{
	if (other.empty())
		throw std::invalid_argument("invalid username");
	account_username = other;
}

void IAccount::setPassWord(const string& other)
{
	if (!Validator::ViablePassword(other))
		throw std::invalid_argument("invalid password");
	account_hashedpassword = BCrypt::generateHash(other);
}

void IAccount::writeToFileAccount(ofstream& out)const
{
	if (!out.is_open())
		throw std::invalid_argument("invalid stream");
	
	string username1 = StringUtils::FillStringSpaces(account_username);

	out << username1 << " " << account_hashedpassword;
}

void IAccount::readFromFileAccount(ifstream& in)
{
	if (!in.is_open())
		throw std::invalid_argument("stream is not opened");
	string usernamefiltered;

	in >> usernamefiltered;
	account_username = StringUtils::UnFillStringSpaces(usernamefiltered);
	in >> account_hashedpassword;
	
}




