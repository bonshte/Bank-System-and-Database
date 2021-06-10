#include "Balance.h"
#include "StringUtils.h"


Balance::Balance(const string& EGN, int countBalances, double starting_balance,int id)
{
	if (!Validator::ValidEGN(EGN))
		throw std::invalid_argument("invalid EGN for card");
	if (countBalances < 0)
		throw std::invalid_argument("balances count cannnot be negative");
	if (starting_balance < 0)
		throw std::invalid_argument("starting balance cannot be negative");
	if (id < 0)
		throw std::invalid_argument("invalid id for Balance constructor");
	owner_id = StringUtils::TurnNumberIntoString(id);
	Balance_id = owner_id +"BGMYBANK" + StringUtils::FindLast4Chars(EGN) + StringUtils::TurnNumberIntoString(countBalances);
	money_in_balance = starting_balance;
}



bool Balance::operator==(const Balance& other)
{
	return Balance_id == other.Balance_id && money_in_balance == other.money_in_balance && owner_id == other.owner_id;
}

Balance::Balance(ifstream& in)
{
	in >> Balance_id;
	in >> money_in_balance;
	in >> owner_id;
}

const string& Balance::getBalanceID() const
{
	return Balance_id;
}






double Balance::getMoneyInBalance() const
{
	return money_in_balance;
}

const string& Balance::getOwner_ID() const
{
	return owner_id;
}



void Balance::setMoneyInBalance(double amount)
{
	if (amount < 0)
		throw std::invalid_argument("amount cannot be negative in balance");
	money_in_balance = amount;
}

void Balance::Print() const
{
	cout << " Balance: "<<Balance_id<<"owned by: " << owner_id << endl;
	cout << "Funds: " << money_in_balance << endl;
	for (int i = 0; i < 30; i++) {
		cout << "-";
	}
	cout << endl;
}







ofstream& operator<<(ofstream& out, const Balance& other)
{
	out << other.Balance_id << " " << other.money_in_balance << " " << other.owner_id << " ";
	return out;
	
}
