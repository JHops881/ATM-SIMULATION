#include <iostream>
#include <string>
#include <array>
#include <limits>

using String = std::string;

struct Account
{

	String m_user;
	String m_password;
	float m_balance;

	Account(String user, String password, float balance)
		: m_user(user), m_password(password), m_balance(balance)
	{
	}

};

// there is only one account in thie simulation
Account myAccount("1", "2", 0.00f);


/* This function takes string and will tell you whether or not 
*  the string inputted is a valid expression of USD (#, #.#, or #.##)
*  Note that this function WILL RETURN FALSE if
* 		- there is a dollar sign ($) in you string
*		- if there is more than two decimal places after the decimal
*       - the string is composed of anything other than digits and a decimal
*  Any string that returns true from this function can be
*  cast into a float with no issues
*/
bool isMoneyFloat(String& string)
{
	bool hasDecimal = false;
	int decimalIndex;
	for (int i = 0; i < string.length(); i++)
	{
		if (isdigit(string[i]))
			continue;
		else if (string[i] == '.')
		{
			if (hasDecimal == false)
			{
				hasDecimal = true;
				decimalIndex = i;
				continue;
			} else { return false; }

		} else { return false; }
	}
	if (hasDecimal == false) 
		return true;
	if (decimalIndex >= (string.length() - 3))
		return true;
	else 
		return false;
}



int main()
{
	// This scope is executed prior to the simulation aspect of the ATM
	// actually "Booting". It asks the user to start or exit the program.
	{
		std::cout << "USER: " << myAccount.m_user << " | PASS: " << myAccount.m_password << "\n";

		std::cout << "ATM Simulator : version 1.0.1\n" 
			<< "type 's' to start or 'e' to exit" << std::endl;

		bool waitingForValidInput = true;
		while (waitingForValidInput)
		{
			char input;
			std::cin >> input;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

			if (input == 's')
			{
				std::cout << "\nBooting...\n\n";
				waitingForValidInput = false;
			}
			else if (input == 'e')
			{
				std::cout << "Exiting...\n";
				exit(EXIT_SUCCESS);
			}
			else
			{
				std::cout << "type 's' to start or 'e' to exit. invalid input. try again: ";
			}
		}
	}
	
	// this loop is the game loop of the simulation
	while (true)
	{
		// this scope prompts the user for a username and password that
		// match the username and password that correspond to the account
		{
			bool attemptingLogin = true;

			String inputUser;
			String inputPassword;

			while (attemptingLogin)
			{
				std::cout << "Please enter username: ";
				std::cin >> inputUser;
				std::cout << "Please enter password: ";
				std::cin >> inputPassword;

				if (inputUser == myAccount.m_user && inputPassword == myAccount.m_password)
				{
					attemptingLogin = false;
				}
				else
				{
					std::cout << "\nInvalid credentials\n\n";
				}
			}
		}

		// This is the main menu that contains to bulk of the functionality
		// of the program/simulation.
		bool inMenu = true;

		std::cout << "\nHello User #" + myAccount.m_user + "\n";

		while (inMenu)
		{
			// present menu options
			std::cout << "\nEnter the corresponding command for the following actions: \n" << 
			"'w' : withdraw\n" << 
			"'d' : deposit\n" << 
			"'b' : balance\n" <<
			"'l' : logout\n" <<
			"\n>> ";

			// getting input
			char input;
			std::cin >> input;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

			// handling withdrawals
			if (input == 'w')
			{
				bool waitingForValidInput = true;
				while (waitingForValidInput)
				{
					std::cout << "\n[withdraw] Enter amount: $";
					String withdrawInput;
					std::cin >> withdrawInput;
					if (isMoneyFloat(withdrawInput))
					{
						float amount = std::stof(withdrawInput);
						if (amount > myAccount.m_balance)
						{
							std::cout << "\nNot enough funds in account!\n";
							continue;
						}
						waitingForValidInput = false;
						std::cout << "\nYou have withdrawn $" << amount << "\n";
						myAccount.m_balance -= amount;
					}
					else
						std::cout << "\nInvalid input!\n";
				}
			}

			// handling deposits
			else if (input == 'd')
			{
				bool waitingForValidInput = true;
				while (waitingForValidInput)
				{
					std::cout << "\n[deposit] Enter amount: $";
					String depositInput;
					std::cin >> depositInput;
					if (isMoneyFloat(depositInput))
					{
						float amount = std::stof(depositInput);
						
						waitingForValidInput = false;
						std::cout << "\nYou have deposited $" << amount << "\n";
						myAccount.m_balance += amount;
					}
					else
						std::cout << "\nInvalid input!\n";
				}
			}

			// handling balance request
			else if (input == 'b')
			{
				std::cout << "Your balance is $" << myAccount.m_balance << "\n";
			}

			// handling logout request
			else if (input == 'l')
			{
				std::cout << "\nLogging out...\n\n";
				inMenu = false;
			}

			// handling extreneous input
			else
			{
				std::cout << "\n\nInvalid option!\n";
			}
		}
	}
}