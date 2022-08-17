#include <iostream>
#include "user.h"

void mainMenu();
void loginMenu();
void Register();
void Login(user user);

bool run = true;

int main()
{      
    while (run)
    {
        mainMenu();
    }
}

void mainMenu()
{
    using std::cout;
    char choice = '\0';
    cout << "RLG Bank\n";
    cout << "If you are new , register - 1\n";
    cout << "Already have an account? login - 2\n";
    cout << "Close the app - 3\n";
    while (choice != '1' || choice != '2' || choice != '3');
        std::cin >> choice;
    if (choice == 1)
        Register();
    if (choice == 2)
        Login(user1);
    if (choice == 3)
    {
        run = false;
        return;
    }
}

void Register()
{
    std::string username = "";
    std::string password = "";
    int pin = 0;
    std::cout << "Enter your name: ";
    std::cin >> username;
    std::cout << "Enter your password";
    std::cin >> password;
    std::cout << "Enter your PIN: ";
    user user1(username, password, pin);
    std::cout << "Account created successfully! Now you can login.\n";
    mainMenu();
}

void Login(user user)
{
    std::string username = "";
    std::string password = "";
    std::cout << "Enter your name: ";
    std::cin >> username;
    std::cout << "Enter your password";
    std::cin >> password;
    if (user.loginvalidation(username, password))
    {
        std::cout << "You logged in!" << std::endl;
        loginMenu();
    }
    else
    {
        std::cout << "Wrong data entered!";
    }
}

void loginMenu()
{
    std::cout << "TO DO";
}