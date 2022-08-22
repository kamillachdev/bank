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
	bool loginvalidation(std::string unCheck, std::string pwCheck); //un - username, pw - password
	void showDetails();
	void deposit();
	void withdraw();
	void changePassword();
	std::string passwordEncryptionDecryption(std::string password);
};

