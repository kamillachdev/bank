#include <iostream>
#include <regex>
#include <string>
#include <fstream>
#include "user.h"

//function prototypes
void mainMenu(user user);
void loginMenu(user user);
void Register();
void Login(user user);

bool run = true;

int main()
{ 
    user emptyUser("", "", 0);
    while (run)
    {
        system("COLOR 3F");
        mainMenu(emptyUser);
    }
    return 0;
}


void mainMenu(user user)
{
    using std::cout;

    char choice = '1';

    //menu visuals
    char charLinesUp[40], charLinesMid[40], charLinesBottom[40];

    charLinesUp[0] = char(201);
    for (int i = 1; i < 36; i++) charLinesUp[i] = char(205);
    charLinesUp[36] = char(187);

    charLinesMid[0] = char(204);
    for (int i = 1; i < 36; i++) charLinesMid[i] = char(205);
    charLinesMid[36] = char(185);

    charLinesBottom[0] = char(200);
    for (int i = 1; i < 36; i++) charLinesBottom[i] = char(205);
    charLinesBottom[36] = char(188);

    for (int i = 0; i < 38; i++) cout << charLinesUp[i]; cout << std::endl;
    cout << char(186) << "            RLG Bank               " << char(186) << "\n";
    for (int i = 0; i < 38; i++) cout << charLinesMid[i]; cout << std::endl;
    cout << char(186) << "If you are new, register - 1       " << char(186) << "\n";
    for (int i = 0; i < 38; i++) cout << charLinesMid[i]; cout << std::endl;
    cout << char(186) << "Already have an account ? login - 2" << char(186) << "\n";
    for (int i = 0; i < 38; i++) cout << charLinesMid[i]; cout << std::endl;
    cout << char(186) << "Close the app - 3                  " << char(186) << "\n";
    for (int i = 0; i < 38; i++) cout << charLinesBottom[i]; cout << std::endl;

    bool looprun = 1;
    while (looprun)
    {
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            Register();
            looprun = 0;
            break;
        case '2':
            Login(user);
            looprun = 0;
            break;
        case '3':
            run = false;
            looprun = 0;
            return;
        default:
            cout << "Wrong number, enter again\n";
        }
    }
}


void loginMenu(user user)
{
    char choice = '1';
    std::cout << "\n~Choose action~ \nShow account details - 1 \nDeposit funds - 2 \nWithdraw funds - 3 \nTransfer funds - 4 \nChange your password - 5 \nLog out - 6\n";
    
    bool looprun = 1;
    while (looprun)
    {
        std::cin >> choice;
        switch (choice)
        {
        case '1':
            user.showDetails();
            break;
        case '2':
            user.deposit();
            break;
        case '3':
            user.withdraw();
            break;
        case '4':
            user.transfer();
            break;
        case '5':
            user.changePassword();
            break;
        case '6':
            looprun = 0;
            mainMenu(user);
            break;
        default:
            std::cout << "Wrong number, enter again\n";
        }
    }
}


void Register()
{
    using namespace std;

    string username = "", password = "";
    int pin = 0;
    double funds = 0;
    regex unRegex ("^[a-zA-Z0-9\_\.]{3,}$");
    regex pwRegex ("^[a-zA-Z0-9\_\.\-]{8,}$");
    regex pinRegex ("^[0-9]{4}");
    string temp = "";
    bool validation = 1;

    cout << "~Registration process~\n";
    while (validation)
    {
        cout << "Enter your name: ";
        cin >> username;
        if (!regex_match(username, unRegex))
        {
            cout << "Username must be at least 3 characters long(letters, numbers, '_', '.')!\n";
        }
        else
            validation = 0; //closing the loop, going to the next phase
    }

    while (!validation)
    {
        std::cout << "Enter your password: ";
        std::cin >> password;
        if (!regex_match(password, pwRegex))
        {
            cout << "Password must be minimum eight characters, at least one letter, one number and one special character!\n";
        }
        else
            validation = 1;
    }

    while (validation)
    {
        std::cout << "Enter your PIN: ";
        std::cin >> pin;
        temp = to_string(pin);
        if (!regex_match(temp, pinRegex))
        {
            cout << "PIN must be 4 characters long(only numbers 0-9)!\n";
        }
    else
        validation = 0;
    }

    user user1(username, password, pin);
    cout << "Account created successfully! Now you can login.\n\n";

    //saving data(username, encrypted password, pin, funds) into the file
    ofstream file;
    file.open("data" + username + ".txt");
    string encryptedPassword = user1.passwordEncryptionDecryption(password);
    file << username << endl << encryptedPassword << endl << pin << endl << funds;
    file.close();

    mainMenu(user1);
}

void Login(user user)
{
    std::string username = "";
    std::string password = "";

    std::cout << "~Login process~\n";
    std::cout << "Enter your name: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    if (user.loginvalidation(username, password))
    {
        loginMenu(user);
    }
    else
    {
        mainMenu(user);
    }
}