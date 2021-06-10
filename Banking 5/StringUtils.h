#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <ctime>
#include <thread>
using namespace std;
class StringUtils {
public:
	static string TurnNumberIntoString(int a);
	static string FindLast4Chars(const string& EGN);

	

	static string FillStringSpaces(const string& str);
	static string UnFillStringSpaces(const string& str);
	
	
};