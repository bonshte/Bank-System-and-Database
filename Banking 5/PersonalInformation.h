#pragma once
#include <iostream>
#include <string>
#include "DateTIme.h"
#include "Validator.h"
using namespace std;
class PersonalInformation {
	static int id_counter;
	int Personal_id;
	string EGN;
	string First_name;
	string Middle_name;
	string Last_name;
	string Phone_number;
	string address;
	DateTime birth_date;
protected:
	PersonalInformation(const PersonalInformation& other) = default;
public:
	virtual ~PersonalInformation() = default;
	PersonalInformation() = default;
	PersonalInformation(const string& egn, const string& f_name, const string& m_name, const string& l_name, const string& p_number,
		const string& adr,
		const DateTime& date);
	PersonalInformation(ifstream& in);
	bool operator==(const PersonalInformation& other);
	PersonalInformation& operator=(const PersonalInformation& other) = delete;


	virtual void Print()const = 0;

	int getId()const;
	const string& getEGN()const;
	const string& getFirstName()const;
	const string& getMiddleName()const;
	const string& getLastName()const;
	const string& getPhoneNumber()const;
	const string& getAddress()const;
	const DateTime& getBirth_time()const;


	
	void setEGN (const string& other);
	void setFirstName (const string& other);
	void setMiddleName (const string& other);
	void setLastName(const string& other);
	void setPhoneNumer(const  string& other);
	void setAddress(const string& other);
	void setBirthDate(const DateTime& other);

	void readFromFileInformation(ifstream& in);
	void WriteToFileInformation(ofstream& out) const;
};