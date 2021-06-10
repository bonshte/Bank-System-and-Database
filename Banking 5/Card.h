#pragma once
#include <string>
#include <iostream>
#include "StringUtils.h"
#include "Validator.h"
class Balance;
class Client;
using namespace std;
class Card {
	string card_id;
	string card_pin;
	string Balance_associated_id;
	string owner_id;
	

protected:
	string CreatePin();
	Card(const Card& other) = delete;
public:
	friend Balance;
	Card(ifstream& in);
	Card() = delete;
	Card(const string& EGN, int countCards, const string& balance,int id);
	~Card() = default;
	bool operator==(const Card& other);
	Card& operator=(const Card& other) = delete;
	
	friend ifstream& operator>>(ifstream& in, Card& other);
	friend ofstream& operator<<(ofstream& out, const Card& other);

	const string& getID()const;
	const string& getAssociatedBalanceId()const;
	const string& getOwner_id()const;
	const string& getHashedPin()const;

	void Print()const;
	

	bool withdraw();
	bool insertMoney();
	bool CheckBalance();
};