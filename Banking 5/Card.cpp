#include "Card.h"
#include "BCrypt.hpp"
#include "FileManager.h"
string Card::CreatePin()
{
	srand(time(0));
	int randomNumber = rand() % 10000;
	char* result = new char[5];
	result[4] = 0;
	for (int i = 0; i < 4; i++) {
		if (randomNumber == 0) {
			for (int j = i; j < 4; j++) {
				result[3 - j] = '0';
			}
			break;
		}

		result[3 - i] = randomNumber % 10 + 48;
		randomNumber /= 10;
	}
	string str = result;
	delete[] result;
	return std::move(str);
}

Card::Card(ifstream& in)
{
	in >> card_id;
	in >> card_pin;
	in >> Balance_associated_id;
	in >> owner_id;
	
}

Card::Card(const string& EGN, int countCards, const string& balance, int id):
	Balance_associated_id(balance)
{
	if (Balance_associated_id.empty() || id < 0 )
		throw std::invalid_argument("invalid inputs for card");
	owner_id = StringUtils::TurnNumberIntoString(id);
	card_id = owner_id + "BG" + StringUtils::FindLast4Chars(EGN) + StringUtils::TurnNumberIntoString(countCards);
	string constructedPin = CreatePin();
	cout << "Card_ID:" << card_id << endl;
	cout << "PIN:" << constructedPin << endl;
	card_pin = BCrypt::generateHash(constructedPin);
}

bool Card::operator==(const Card& other)
{
	return card_id == other.card_id && card_pin == other.card_pin &&
		Balance_associated_id == other.Balance_associated_id &&
		owner_id == other.owner_id;
}



const string& Card::getID() const
{
	return card_id;
}

const string& Card::getAssociatedBalanceId() const
{
	return Balance_associated_id;
}

const string& Card::getOwner_id() const
{
	return owner_id;
}

const string& Card::getHashedPin() const
{
	return card_pin;
}

void Card::Print() const
{
	cout << "Card ID: " << card_id << endl;
	cout << "Owner by: " << owner_id << endl << endl;
	
}

bool Card::withdraw()
{
	cout << "Enter Amount:" << endl;
	double funds = Validator::EnterValidDouble();
	if (funds <= 0) {
		cout << "must be positive number" << endl;
		return false;
	}
	double money_in_balance = FileManager::getMoneyInBalance(Balance_associated_id, owner_id);
	if (money_in_balance - funds < 0) {
		cout << "Not enough funds" << endl;
		return false;
	}
	money_in_balance -= funds;
	FileManager::SetMoneyInBalance(money_in_balance, Balance_associated_id, owner_id);
	return true;
}

bool Card::insertMoney()
{
	cout << "Enter Amount:" << endl;
	double funds = Validator::EnterValidDouble();
	if (funds <= 0) {
		cout << "must be positive number" << endl;
		return false;
	}
	double money_in_balance = FileManager::getMoneyInBalance(Balance_associated_id, owner_id);
	money_in_balance += funds;
	FileManager::SetMoneyInBalance(money_in_balance,Balance_associated_id,owner_id);
	return true;
}

bool Card::CheckBalance()
{
	double moneyInBalance = FileManager::getMoneyInBalance(Balance_associated_id, owner_id);
	cout << "Balance ID: " << Balance_associated_id << endl;
	cout << "Funds: " << moneyInBalance << endl;
	return true;
}



ifstream& operator>>(ifstream& in, Card& other)
{
	if (!in.is_open())
		throw std::invalid_argument("stream is closed");
	in >> other.card_id;
	in >> other.card_pin;
	in >> other.Balance_associated_id;
	in >> other.owner_id;
	return in;
}

ofstream& operator<<(ofstream& out, const Card& other)
{
	if (!out.is_open())
		throw std::invalid_argument("stream is closed");
	out << other.card_id << " " << other.card_pin << " " << other.Balance_associated_id << " " << other.owner_id << " ";
		
	return out;
}
