#include "Validator.h"



bool Validator::areSame(char a, char b)
{
    return (Validator::isLetter(a) && Validator::isLetter(b) && (a - b == 32 || b - a == 32)) || a == b;
}

bool Validator::SameCommands(const string& command_input, const string& test_command)
{
    if (command_input.size() != test_command.size())
        return false;
    for (size_t i = 0; i < command_input.size(); ++i) {
        if (!areSame(command_input[i], test_command[i]))
            return false;
    }
    return true;
}

double Validator::EnterValidDouble()
{
    double number;
    cin >> number;
    cout << endl;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid Entry,enter again" << endl;
        cin >> number;
        cout << endl;
    }
    return number;
}

bool Validator::isDigit(char a)
{
    return a >= '0' && a <= '9';
}

bool Validator::isLetter(char a)
{
    return (a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z');
}

bool Validator::Delim(char a)
{
    return a == ' ' || a == '\t';
}

bool Validator::ValidPin(const string& _pin_test)
{
    if (_pin_test.size() != 4)
        return false;
    return _pin_test.find_first_not_of("0123456789") == string::npos; // no matches
    

}

bool Validator::ViablePassword(const string& test_password)
{
    if (test_password.size() < 6)
        return false;
    return test_password.find_first_of("0123456789") != string::npos;
}

int Validator::EnterValidInteger()
{
    int number;
    cin >> number;
    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << endl << "Entry was invalid, please enter again" << endl;
        cin >> number;
        cout << endl;

    }
    return number;
}

bool Validator::ValidPhoneNumber(const string& phone)
{
    if (phone.size() != 10 && phone.size() != 12)//089..... || 359 89 ....
        return false;
    return phone.find_first_not_of("0123456789") == string::npos; // no matches
}

bool Validator::ValidEGN(const string& EGN)
{
    return EGN.size() >= 10;
}


