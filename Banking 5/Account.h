#pragma once
#include "Card.h"
#include <iostream>
#include <vector>
#include <string>
#include "DateTIme.h"
#include <fstream>
#include "BCrypt.hpp"

using namespace std;

class IAccount {
	string account_username; 
	
protected:
	string account_hashedpassword;
	IAccount(const IAccount& other);
	
	//use it only on R value objects
	//in the body of a function which creates the object
public:
	IAccount(const string& username, const string& password); 
	IAccount();
	

	
	bool operator==(const IAccount& other);
	IAccount& operator=(const IAccount& other) = delete;
	virtual ~IAccount() = default;
	virtual void Print()const = 0;

	const string& getUsername()const;
	const string& getHashedPassword()const;

	void setUserName(const string& other);
	void setPassWord(const string& other);


	virtual void writeToFileAccount(ofstream& out)const;
	void readFromFileAccount(ifstream& in);

	

	
	
};