#include <iostream>

void mainMenu();
void Register();
void Login();

int main()
{      
    std::cout << "Hello World!\n";
}

void mainMenu()
{
    using std::cout;
    char choice = '\0';
    cout << "RLG Bank\n";
    cout << "If you are new , register - 1\n";
    cout << "Already have an account? login - 2\n";
    while(choice != '1' || choice != '2')
        std::cin >> choice;
    if (choice == 1)
        Register();
    if (choice == 2)
        Login();
}