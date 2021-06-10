#include "StringUtils.h"
#include "Validator.h"

string StringUtils::TurnNumberIntoString(int number)
{
    if (number < 0)
        throw std::invalid_argument("invalid count");
    
	ofstream out;
	out.open("turningNumberIntoString");

	out << number << endl;
	out.close();

	ifstream in;
	in.open("turningNumberIntoString");
	if (!in.is_open()) {
		throw std::exception("could not generate number");
	}
	char buffer[100];
	in.getline(buffer, 100, '\n');
	int length = strlen(buffer) + 1;

	char* result = new char[length];
	strcpy_s(result, length, buffer);

	std::remove("turningNumberIntoString");

	string str = result;
	delete[] result;
	return str;
}

string StringUtils::FindLast4Chars(const string& str)
{
	if (str.size() < 4)
		throw std::invalid_argument("too small string");
	string result;
	int length = str.size();
	for (int i = 0; i < 4; i++) {
		 result.push_back(str[length - 4 + i]);
	}
	return result;
}





string StringUtils::FillStringSpaces(const string& str)
{
	string result;
	for (int i = 0; i < str.size(); ++i) {
		if (Validator::Delim(str[i])) {
			result.push_back('$');
		}
		else {
			result.push_back(str[i]);
		}

	}
	return result;
}

string StringUtils::UnFillStringSpaces(const string& str)
{
	string result;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == '$') {
			result.push_back(' ');
		}
		else {
			result.push_back(str[i]);
		}
	}
	return result;
}




