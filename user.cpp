#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <iomanip>
#include "user.h"


using namespace std;

vector<string> lines;
string username = "", unCheck, pwCheck, pinCheck, fundsCheck;

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

	if (read.fail())
	{
		cout << "There is no user named " << un << "!" << endl;
		return false;
	}

	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	lines.push_back(unCheck);
	lines.push_back(pwCheck);
	lines.push_back(pinCheck);
	lines.push_back(fundsCheck);
	read.close();

	username = un; // setting username to let other functions use it

	if (unCheck == un && pwCheck == passwordEncryptionDecryption(pw))
	{
		cout << "You logged in!" << endl;
		return true;
	}
	else
	{
		cout << "Wrong password!" << endl;
		return false;
	}
}


void user::showDetails()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	double fundsCheckDouble = std::stod(fundsCheck);
	read.close();

	cout << "Username: " << unCheck << "\n";
	cout << "Funds: " << fixed << setprecision(2) << fundsCheckDouble << " USD" << "\nSelect action again: ";
}


void user::deposit()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	double fundsCheckDouble = std::stod(fundsCheck);
	read.close();

	double amount = 0;
	string pinInput = "";

	while (std::cout << "Enter amount of money you want to deposit: " && !(std::cin >> amount))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input! Please re-enter.\n";
	}

	cout << "Enter your PIN: ";
	cin >> pinInput;
	if (pinCheck == pinInput)
	{
		fundsCheckDouble += amount;
		cout << "Deposited successfully!\n";

		//changing funds into data file
		ofstream write;
		write.open("data" + username + ".txt");
		string fundsString = to_string(fundsCheckDouble);
		for (int i = 0; i < lines.size(); i++)
		{
			if (i != 3) //3 is funds line in data file
				write << lines[i] << endl;
			else
				write << fundsString << endl;
		}
		write.close();

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
	double fundsCheckDouble = std::stod(fundsCheck);
	read.close();

	double amount = 0;
	string pinInput = "";

	while (std::cout << "Enter amount of money you want to withdraw: " && !(std::cin >> amount))
	{
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid input! Please re-enter.\n";
	}

	if (fundsCheckDouble - amount < 0)
		cout << "Action failed: You don't have enough funds to withdraw! \nSelect action again: ";
	else
	{
		cout << "Enter your PIN: ";
		cin >> pinInput;
		if (pinCheck == pinInput)
		{
			fundsCheckDouble += amount;
			cout << "Withdrawed successfully!\nSelect action again: ";

			//changing funds into data file
			ofstream write;
			write.open("data" + username + ".txt");
			string fundsString = to_string(fundsCheckDouble);
			for (int i = 0; i < lines.size(); i++)
			{
				if (i != 3) //3 is funds line in data file
					write << lines[i] << endl;
				else
					write << fundsString << endl;
			}
			write.close();

		}
		else
			cout << "Wrong PIN, select action again: \n";
	}
}


void user::changePassword()
{
	ifstream read("data" + username + ".txt");
	getline(read, unCheck);
	getline(read, pwCheck);
	getline(read, pinCheck);
	getline(read, fundsCheck);
	read.close();

	regex pwRegex("^[a-zA-Z0-9\_\.\-]{8,}$");
	string newPassword = "";
	cout << "Enter your old password: ";
	while (pwCheck != newPassword)
	{
		cin >> newPassword;
		if (newPassword == passwordEncryptionDecryption(pwCheck))
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
					cout << "Password changed successfully! \nSelect action again: ";

					//saving password into data file
					ofstream write;
					write.open("data" + username + ".txt");
					for (int i = 0; i < lines.size(); i++)
					{
						if (i != 1)
							write << lines[i] << endl;
						else
							write << passwordEncryptionDecryption(pwCheck) << endl;
					}
					write.close();

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