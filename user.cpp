#include "user.h"
#include <iostream>
#include <fstream>
#include <regex>

std::ofstream dataFile("bankdata.txt");

user::user(std::string un, std::string pw, int p)
{
	username = un;
	password = pw;
	PIN = p;
	funds = 0;
}

bool user::loginvalidation(std::string unCheck, std::string pwCheck)
{
	if (username == unCheck && password == pwCheck)
		return true;
	else
		return false;
}

void user::showDetails()
{
	using std::cout;
	cout << "Username: " << username << "\n";
	cout << "Funds: " << funds << "\n";
}

void user::deposit()
{
	double amount = 0;
	int pinCheck = 0;
	std::cout << "Enter amount of money you want to deposit: ";
	std::cin >> amount;
	std::cout << "Enter your PIN: ";
	std::cin >> pinCheck;
	if (pinCheck == PIN)
	{
		funds += amount;
		std::cout << "Deposited successfully!\n";
	}
	else
		std::cout << "Wrong PIN, action failed";
}

void user::withdraw()
{
	double amount = 0;
	int pinCheck = 0;
	std::cout << "Enter amount of money you want to withdraw: ";
	std::cin >> amount;
	if (funds - amount < 0)
		std::cout << "Action failed: You don't have enough funds to withdraw!\n";
	else
	{
		std::cout << "Enter your PIN: ";
		std::cin >> pinCheck;
		if (pinCheck == PIN)
		{
		funds -= amount;
		std::cout << "Withdrawed successfully!\n";
		}
		else
			std::cout << "Wrong PIN, action failed";
	}
}

void user::changePassword()
{
	std::regex pwRegex("^[a-zA-Z0-9\_\.\-]{8,}$");
	std::string newPassword = "";
	std::cout << "Enter your old password: ";
	while (password != newPassword)
	{
		std::cin >> newPassword;
		if (newPassword == password)
		{
			bool validation = 1;
			while (validation)
			{
				std::cout << "Enter your new password: ";
				std::cin >> newPassword;
				if (!regex_match(newPassword, pwRegex))
				{
					std::cout << "Password must be minimum eight characters, at least one letter, one number and one special character!\n";
				}
				else
				{
					password = newPassword;
					std::cout << "Password changed successfully\n";
					validation = 0;
				}
			}
		}
		else
		{
			std::cout << "Wrong password!";
		}
	}
}

std::string user::passwordEncryptionDecryption(std::string password) //divide the password in half, reverse the halves, and stick them together in the reverse order
{
	//makes abcde12345 to 54321edcba
	std::string firstHalf, secondHalf, returnPassword;
	int passwordLength = password.length();
	for (int i = 0; i < passwordLength / 2; i++)
		firstHalf += password[i];
	for (int i = passwordLength / 2; i < passwordLength; i++)
		secondHalf += password[i];
	for (int i = secondHalf.length() - 1; i >= 0; i--)
		returnPassword += secondHalf[i];
	for (int i = firstHalf.length() - 1; i >= 0; i--)
		returnPassword += firstHalf[i];
	return returnPassword;
}