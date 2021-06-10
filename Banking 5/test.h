#pragma once
#include "doctest.h"
#include "Validator.h"
#include "StringUtils.h"
#include "PersonalInformation.h"
#include "Card.h"
#include "Admin.h"
#include "Client.h"
#include "DateTIme.h"
TEST_CASE("Validator ValidEGN") {
	string test1 = "0123456789";
	string test2 = "asdasll123";
	string test3 = "dasdlj12";
	string test4 = "031268381643";
	CHECK(Validator::ValidEGN(test1));
	CHECK(Validator::ValidEGN(test2));
	CHECK(!Validator::ValidEGN(test3));
	CHECK(Validator::ValidEGN(test1));
}
TEST_CASE("Validator Valid Number") {
	string test1 = "0896212812";
	string test2 = "08983482143";
	string test3 = "359782839132";
	string test4 = "089235fdf431";
	CHECK(Validator::ValidPhoneNumber(test1));
	CHECK(!Validator::ValidPhoneNumber(test2));
	CHECK(Validator::ValidPhoneNumber(test3));
	CHECK(!Validator::ValidPhoneNumber(test4));
}
TEST_CASE("Validator Valid Password") {
	string test1 = "123ds";
	string test2 = "1231236178";
	string test3 = "sdlasndl";
	CHECK(!Validator::ViablePassword(test1));
	CHECK(Validator::ViablePassword(test2));
	CHECK(!Validator::ViablePassword(test3));
}
TEST_CASE("Validator valid Pin") {
	string test1 = "2135";
	string test2 = "dasd";
	string test3 = "12354";
	CHECK(Validator::ValidPin(test1));
	CHECK(!Validator::ValidPin(test2));
	CHECK(!Validator::ValidPin(test3));
}
TEST_CASE("Validator Same Commands") {
	string test1 = "loginasadmin";
	string test2 = "LoGinAsAdmin";
	string test3 = "Loginasadmin ";
	string test4 = "l ogin as admin";
	CHECK(Validator::SameCommands(test1, "LoginAsAdmin"));
	CHECK(Validator::SameCommands(test2, "LoginAsAdmin"));
	CHECK(!Validator::SameCommands(test3, "LoginAsAdmin"));
	CHECK(!Validator::SameCommands(test4, "LoginAsAdmin"));

}
TEST_CASE("StringUtils turn number into string") {
	int a = 15;
	int b = 28;
	int c = 123;
	string fifteen = "15";
	string twentyeight = "28";
	string hundredtwenty = "120";
	CHECK(fifteen == StringUtils::TurnNumberIntoString(a));
	CHECK(twentyeight == StringUtils::TurnNumberIntoString(b));
	CHECK(hundredtwenty != StringUtils::TurnNumberIntoString(c));
}
TEST_CASE("STRING Utils Find last 4 chars") {
	string test1 = "hello";
	string test2 = "he  ll oo";
	string result1 = "ello";
	string result2 = "lloo";
	CHECK(result1 == StringUtils::FindLast4Chars(test1));
	CHECK(result2 != StringUtils::FindLast4Chars(test2));
}


TEST_CASE("Check String Filling") {
	string sentance = "heelo i am programmer  hello!";
	string result = StringUtils::FillStringSpaces(sentance);
	string result1 = StringUtils::UnFillStringSpaces(result);
	
	CHECK(result == "heelo$i$am$programmer$$hello!");
	CHECK(result1 == sentance);
}

