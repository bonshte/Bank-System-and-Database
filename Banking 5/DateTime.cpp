#include "DateTime.h"

//Constructors
DateTime::DateTime() {
	time_t now = time(0);
	tm* timeNow = localtime(&now);
	year = 1900 + timeNow->tm_year;
	month = 1 + timeNow->tm_mon;
	day = timeNow->tm_mday;
	

}
DateTime::DateTime(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
	
}


//Printing

void DateTime::PrintTime() const {
	cout << day << " ";
	switch (getMonth())
	{
	case 1: cout << "January";
		break;
	case 2: cout << "February";
		break;
	case 3: cout << "March";
		break;
	case 4: cout << "April";
		break;
	case 5: cout << "May";
		break;
	case 6: cout << "June";
		break;
	case 7: cout << "July";
		break;
	case 8: cout << "August";
		break;
	case 9: cout << "September";
		break;
	case 10: cout << "October";
		break;
	case 11: cout << "November";
		break;
	case 12: cout << "December";
		break;
	}
	cout << " " << getYear() << ", " <<  endl;
}


//Validation
bool DateTime::isValidTime() const {
	bool isfeb = false;
	bool has30days = false;
	bool isLeap = false;
	if (month == 2)
		isfeb = true;
	if (month == 4 || month == 6 || month == 9 || month == 11)
		has30days = true;
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
		isLeap = true;

	return!(day > 31 || day < 1 || month>12 || month < 1 || (isLeap && isfeb && day > 29) || (!isLeap && isfeb && day > 28) || (has30days && day > 30));
}

bool DateTime::operator==(const DateTime& other)
{
	return day == other.day && year == other.year && month == other.month;
}


//Getters
int DateTime::getDay() const {
	return day;
}

int DateTime::getMonth() const {
	return month;
}

int DateTime::getYear() const {
	return year;
}





//Setters
void DateTime::setYear(int y) {
	year = y;
}
void DateTime::setMonth(int m) {
	month = m;
}
void DateTime::setDay(int d) {
	day = d;
}

ofstream& operator<<(ofstream& out, const DateTime& time)
{
	out << time.year << " " << time.month << " " << time.day << " ";
	return out;

}



ifstream& operator>>(ifstream& in,  DateTime& time)
{
	int year, month, day;
	in >> year >> month >> day;
	time.setDay(day);
	time.setMonth(month);
	time.setYear(year);
	return in;
}
