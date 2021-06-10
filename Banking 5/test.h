##pragma once

#include "Validator.h"
#include "StringUtils.h"
#include "PersonalInformation.h"
#include "Card.h"
#include "Admin.h"
#include "Client.h"
#include "DateTIme.h"
#include "doctest.h"
#include "Admin.h"
#include "Balance.h"
#include "Card.h"
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
TEST_CASE("Admin constructor matching password for admin") {
	Admin admin;
	string password = "admin";
	bool valid = BCrypt::validatePassword(password, admin.getHashedPassword());

	CHECK(valid == true);
}
TEST_CASE("Check read Write Balance") {
	Balance one ("1234567890",10,10,10);
	ofstream out("test");
	out << one;
	out.close();
	ifstream in("test");
	Balance two(in);
	in.close();
	CHECK(two.getBalanceID() == one.getBalanceID());
}
TEST_CASE("Balance constructor") {
	//Format id+"BGMYBANK" +EGNLAST4 +CNT
	Balance one("1234567890", 10, 10, 10);
	string result = "10BGMYBANK789010";
	CHECK(one.getBalanceID() == result);
}
TEST_CASE("Card constructor") {
	Card one("0123456789", 10, "0000", 5);
	string result = "5BG678910";
	CHECK(one.getID() == result);
}
TEST_CASE("Card read-write and ==") {
	Card one("0123456789", 10, "0000", 5);
	ofstream out("test");
	out << one;
	out.close();
	ifstream in("test");
	Card two(in);
	in.close();
	CHECK(one.getAssociatedBalanceId() == two.getAssociatedBalanceId());
	CHECK(one.getOwner_id() == two.getOwner_id());
}
TEST_CASE("Client read write ==") {
	DateTime ago(2001, 10, 12);
	Client one("username", "passwor1", "0123456789", "me", "you", "me", "home", "0896217438", ago);
	ofstream out("file");
	out << one;
	out.close();

	ifstream in("file");
	Client two(in);
	in.close();
	CHECK(one.getEGN() == two.getEGN());
	CHECK(one.getId() == two.getId());
	
}
TEST_CASE("Fillings strings") {
	string one = "1 1 1 1 1 1";
	string two = StringUtils::FillStringSpaces(one);
	string two_result = "1$1$1$1$1$1";
	CHECK(two_result == two);
	string one_result = StringUtils::UnFillStringSpaces(two);
	CHECK(one_result == one);
}
