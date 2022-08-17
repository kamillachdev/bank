#include "user.h"
#include <iostream>

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

void user::deposit(double amount)
{
	funds += amount;
}

void user::withdraw(double amount)
{
	if (funds - amount < 0)
		std::cout << "Action failed: You don't have enough funds to withdraw!\n";
	else
		funds -= amount;
}

void user::changePassword()
{
	std::string newPassword = "";
	std::cout << "Enter your old password: ";
	std::cin >> newPassword;
	while (password != newPassword)
	{
		std::cin >> newPassword;
		if (newPassword == password)
		{
			std::cout << "Now enter your new password: ";
			std::cin >> newPassword;
			password = newPassword;
		}
		else
		{
			std::cout << "Wrong password!";
		}
	}
}