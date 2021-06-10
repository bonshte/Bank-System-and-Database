#include "LoginAsClientCommand.h"
#include "Validator.h"
#include "Card.h"
#include "Invoker.h"
bool LoginAsClientCommand::execute(IAccount*& actor, Card*& card)
{
	cout << "Loggin as Client:" << endl;
	cout << "Enter Card ID:" << endl;
	string card_id;
	cin >> card_id;
	cout << endl;
	string pin;
	cout << "Enter PIN: " << endl;
	cin >> pin;
	if (!Validator::ValidPin(pin)) 
		return false;
	

	ofstream out("Cards.db", ios::app);
	out.close();

	ifstream in("Cards.db");
	if (!in.is_open()) {
		throw std::exception("Cards database wont open");
		in.close();
		return false;
	}
	if (in.peek() == ifstream::traits_type::eof()) {
		in.close();
		return false;
	}

	//Format card_id pin balance_id owner_username
	while (in) {
		double startPos = in.tellg();
		Card current(in);
		
		if (card_id == current.getID() && BCrypt::validatePassword(pin, current.getHashedPin())) {
			
			in.seekg(startPos);
			card = new Card(in);
			in.close();
			
			Invoker::getInstance()->eraseAllCommands();
			Invoker::getInstance()->switchToClient();
			return true;
		}




		FileManager::ReadTillEndOfLineInFile(in);
		if (in.peek() == EOF)
			break;
	}
	in.close();
	return false;
}

string LoginAsClientCommand::ReturnCommandName() const
{
	return "LoginAsClient";
}

string LoginAsClientCommand::description()
{
	return "Insert card";
}
