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


Account myAccount("189", "0001", 980.50f);


int main()
{
	/* 
	*  This scope is executed prior to the simulation aspect of the ATM
	*  actually "Booting". It asks the user to start or exit the program.
	*/
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
	
	// this true loop is the game loop of the simulation
	while (true)
	{
		// Login Section;
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

		/* This is the main menu that contains to bulk of the functionality
		*  of the program/simulation.
		*/
		bool inMenu = true;

		std::cout << "\nHello User #" + myAccount.m_user + "\n";

		while (inMenu)
		{
			// present options
			std::cout << "\nEnter the corresponding command for the following actions: \n" << 
			"'w' : withdraw\n" << 
			"'d' : deposit\n" << 
			"'b' : balance\n" <<
			"'l' : logout\n" <<
			"\n>> ";
			bool waitingForValidInput = true;
			while (waitingForValidInput) 
			{
				char input;
				std::cin >> input;
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

				if (input == 'w')
				{
					waitingForValidInput = false;
					std::cout << "\n\n[withdraw] Enter amount: ";
				}
				else if (input == 'd')
				{
					waitingForValidInput = false;
					std::cout << "\n\n[deposit] Enter amount: ";
				}
				else if (input == 'b')
				{
					waitingForValidInput = false;
				}
				else if (input == 'l')
				{
					waitingForValidInput = false;
				}
				else
				{
					std::cout << "\n\nInvalid option!\n\n>> ";
				}
			}
		}
	}
}