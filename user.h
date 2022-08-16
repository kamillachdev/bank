#include <string>

class user
{
private:
	std::string username;
	std::string password;
	int PIN;
	double funds;
public:
	user(std::string un, std::string pw, int PIN);
	void showDetails();
	void deposit(double amount);
	void withdraw(double amount);
	void changePassword();
};

