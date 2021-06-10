#include "PersonalInformation.h"
#include "StringUtils.h"
#include "DateTIme.h"
#include "FileManager.h"
int PersonalInformation::id_counter = FileManager::GetCreatedAccountsAllTime();
PersonalInformation::PersonalInformation(const string& egn, const string& f_name,
	const string& m_name, const string& l_name,
	const string& p_number, const string& adr,
	const DateTime& date)
{
	try
	{
		setEGN(egn);
		setFirstName(f_name);
		setMiddleName(m_name);
		setLastName(l_name);
		setPhoneNumer(p_number);
		setAddress(adr);
		setBirthDate(date);
		Personal_id = id_counter++;
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
		throw ex;
	}
}

PersonalInformation::PersonalInformation(ifstream& in)
{
	readFromFileInformation(in);
}

bool PersonalInformation::operator==(const PersonalInformation& other)
{
	return EGN == other.EGN && First_name == other.First_name && Middle_name == other.Middle_name &&
		Last_name == other.Last_name && Phone_number == other.Phone_number && address == other.address &&
		birth_date == other.birth_date && Personal_id == other.Personal_id;
}





void PersonalInformation::Print() const
{
	cout << "Personal Information:" << endl;
	cout << Personal_id << endl;
	cout << First_name << endl;
	cout << Middle_name << endl;
	cout << Last_name << endl;
	cout << Phone_number << endl;
	cout << address << endl;
	birth_date.PrintTime();

}

int PersonalInformation::getId() const
{
	return  Personal_id;
}

const string& PersonalInformation::getEGN() const
{
	return EGN;
}

const string& PersonalInformation::getFirstName() const
{
	return First_name;
}

const string& PersonalInformation::getMiddleName() const
{
	return Middle_name;
}

const string& PersonalInformation::getLastName() const
{
	return Last_name;
}

const string& PersonalInformation::getPhoneNumber() const
{
	return Phone_number;
}

const string& PersonalInformation::getAddress() const
{
	return address;
}

const DateTime& PersonalInformation::getBirth_time() const
{
	return birth_date;
}

void PersonalInformation::setEGN(const string& other)
{
	if (!Validator::ValidEGN(other))
		throw std::invalid_argument("invalid egn input");
	EGN = other;
}

void PersonalInformation::setFirstName(const string& other)
{
	if (other.empty())
		throw std::invalid_argument("invalid name");
	First_name = other;
}

void PersonalInformation::setMiddleName(const string& other)
{
	if (other.empty())
		throw std::invalid_argument("invalid name");
	Middle_name = other;
}

void PersonalInformation::setLastName(const string& other)
{
	if (other.empty())
		throw std::invalid_argument("invalid name");
	Last_name = other;
}

void PersonalInformation::setPhoneNumer(const string& other)
{
	if (!Validator::ValidPhoneNumber(other))
		throw std::invalid_argument("invalid phone number");
	Phone_number = other;
}

void PersonalInformation::setAddress(const string& other)
{
	if (other.empty())
		throw std::invalid_argument("invalid address");
	address = other;
}

void PersonalInformation::setBirthDate(const DateTime& other)
{
	if (!other.isValidTime())
		throw std::invalid_argument("invalid date");
	birth_date = other;
}

void PersonalInformation::readFromFileInformation(ifstream& in)
{
	if (!in.is_open()) 
		throw std::invalid_argument("stream is not opened");
	string egn1;
	string firstname1;
	string middlename1;
	string lastname1;
	string phonenumber1;
	string address1;
	DateTime date1;
	in >> egn1;
	in >> firstname1;
	in >> middlename1;
	in >> lastname1;
	in >> phonenumber1;
	in >> address1;
	in >> date1;
	in >> Personal_id;

	EGN = StringUtils::UnFillStringSpaces(egn1);
	First_name = StringUtils::UnFillStringSpaces(firstname1);
	Middle_name = StringUtils::UnFillStringSpaces(middlename1);
	Last_name = StringUtils::UnFillStringSpaces(lastname1);
	Phone_number = StringUtils::UnFillStringSpaces(phonenumber1);
	address = StringUtils::UnFillStringSpaces(address1);
	birth_date = date1;
	
	
}

void PersonalInformation::WriteToFileInformation(ofstream& out)const
{
	if (!out.is_open())
		throw std::invalid_argument("stream is closed");

	string egn1 = StringUtils::FillStringSpaces(EGN);
	string firstname1 = StringUtils::FillStringSpaces(First_name);
	string middlename1 = StringUtils::FillStringSpaces(Middle_name);
	string lastname1 = StringUtils::FillStringSpaces(Last_name);
	string phonenumber1 = StringUtils::FillStringSpaces(Phone_number);
	string address1 = StringUtils::FillStringSpaces(address);

	out << egn1 << " " << firstname1 << " " << middlename1 << " " << lastname1 << " " << phonenumber1 << " "
		<< address1 << " ";
	out << birth_date << Personal_id << " ";

	
}


