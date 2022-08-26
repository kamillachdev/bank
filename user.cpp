#include "user.h"
#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;

string username = "", unCheck, pwCheck, pinCheck, fundsCheck;
int fileLine = 0;
vector<string> lines;

user::user(string un, string pw, int p)
{
	username = un;
	password = pw;
	PIN = p;
	funds = 0;
}

bool user::loginvalidation(string un, string pw)
{
	ifstream read("data" + un + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	lines.push_back(unCheck);
	lines.push_back(pwCheck);
	lines.push_back(pinCheck);
	lines.push_back(fundsCheck);
	username = un;

	if (unCheck == un && pwCheck == passwordEncryptionDecryption(pw))
		return true;
	else
		return false;
}

void user::showDetails()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	cout << "Username: " << unCheck << "\n";
	cout << "Funds: " << fundsCheck << "\n";
}

void user::deposit()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	double amount = 0;
	string pinInput = "";
	cout << "Enter amount of money you want to deposit: ";
	cin >> amount;
	cout << "Enter your PIN: ";
	cin >> pinInput;
	if (pinCheck == pinInput)
	{
		funds += amount;
		cout << "Deposited successfully!\n";

		//changing funds into data file
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != fileLine)
				read << lines[i] << endl;
			else
				read << (string)funds << endl;
		}

	}
	else
		cout << "Wrong PIN, choose action again: \n";
}

void user::withdraw()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	double amount = 0;
	string pinInput = "";
	cout << "Enter amount of money you want to withdraw: ";
	cin >> amount;
	if (funds - amount < 0)
		cout << "Action failed: You don't have enough funds to withdraw!\n";
	else
	{
		cout << "Enter your PIN: ";
		cin >> pinInput;
		if (pinCheck == pinInput)
		{
		funds -= amount;
		cout << "Withdrawed successfully!\n";
		}
		else
			cout << "Wrong PIN, choose action again: \n";
	}
}

void user::changePassword()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	regex pwRegex("^[a-zA-Z0-9\_\.\-]{8,}$");
	string newPassword = "";
	cout << "Enter your old password: ";
	while (pwCheck != newPassword)
	{
		cin >> newPassword;
		if (newPassword == pwCheck)
		{
			bool validation = 1;
			while (validation)
			{
				cout << "Enter your new password: ";
				cin >> newPassword;
				if (!regex_match(newPassword, pwRegex))
				{
					cout << "Password must be minimum eight characters, at least one letter, one number and one special character!\n";
				}
				else
				{
					pwCheck = newPassword;
					cout << "Password changed successfully\n";
					validation = 0;
				}
			}
		}
		else
		{
			std::cout << "Wrong password, write password again: \n";
		}
	}
}

std::string user::passwordEncryptionDecryption(string password) //divide the password in half, reverse the halves, and stick them together in the reverse order
{
	//makes abcde12345 to 54321edcba
	string firstHalf, secondHalf, returnPassword;
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