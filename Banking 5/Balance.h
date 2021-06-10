#pragma once
#include "Card.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Client;
class Balance {
	string Balance_id;
	double money_in_balance;
	string owner_id;
public:
	Balance() = delete;
	Balance(const string& EGN, int countBalances,double starting_balance,int id);
	Balance(const Balance& other) = delete;
	~Balance() = default;
	Balance& operator=(const Balance& other) = delete;
	bool operator==(const Balance& other);
	friend ofstream& operator<<(ofstream& out, const Balance& other);
	Balance(ifstream& in);
	
	const string& getBalanceID()const;
	double getMoneyInBalance()const;
	const string& getOwner_ID()const;
	
	void setMoneyInBalance(double amount);
	void Print()const;

};