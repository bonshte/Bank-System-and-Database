#pragma once
#include "Account.h"
#include "FileManager.h"
#include"Employee.h"
#include "FileNamesHandler.h"


class Admin:public IAccount{
public:
	Admin() = default;
	~Admin() = default;




	bool CreateNewEmployee();
	//enter Credentials for employee if the credentials are valid
	// add the employee to the Bank 
	//add to file with employees
	bool DeleteEmployee();
	// enter EGN for employee,
	//checks if employee with such EGN exists,
	//if yes delete from bank and file

	friend ofstream& operator<<(ofstream& out, const Admin& other);
	friend ifstream& operator>>(ifstream& in, Admin& other);

	void Print()const override;
};