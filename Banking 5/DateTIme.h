#pragma once
#include <fstream>
#include <iostream>
#include <ctime>
#include <limits>
#include <fstream>
using namespace std;
class DateTime {
	int year;
	int month;
	int day;
	
public:
	//Validation
	bool isValidTime() const;
	bool operator==(const DateTime& other);

	//Print
	void PrintTime() const;


	//Cosnstructors
	DateTime();
	DateTime(int y, int m , int d);

	friend ofstream& operator<<(ofstream& out, const DateTime& time);
	friend ifstream& operator>>(ifstream& in,  DateTime& time);
	//Seconds Level abstraction
	int getYear() const;
	int getMonth() const;
	int getDay() const;
	


	//setters
	void setYear(int);
	void setMonth(int);
	void setDay(int);
	

	


};