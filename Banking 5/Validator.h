#pragma once
#include <string>
#include <iostream>
using namespace std;
class Validator {
	static bool areSame(char a, char b);
public:
	static bool SameCommands(const string& command_input, const string& test_command);
	static double EnterValidDouble();
	static int EnterValidInteger();
	static bool isDigit(char a);
	static bool isLetter(char a);
	static bool Delim(char a);
	static bool ValidPin(const string& _pin_test);
	static bool ViablePassword(const string& test_password);
	static bool ValidPhoneNumber(const string& phone);
	static bool ValidEGN(const string& EGN);
};