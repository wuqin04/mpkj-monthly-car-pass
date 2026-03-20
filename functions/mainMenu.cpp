#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <limits>
#include "mainMenu.h"
#include "user/userMenu.h"
#include "admin/adminMenu.h"
#include "user/userInfoMenu.h"
using namespace std;

const string adminLogin = "admin";
const string adminPass = "admin";
string userLogin = "user";
string userPass = "user";

void mainMenu() {
	while (true) {
		string username = "";
		string password = "";
		char ch;

		cout << "=======================================================\n";
		cout << "|                     MAIN MENU                       |\n";
		cout << "=======================================================\n";
		cout << "|      Welcome to MPKJ Monthly Car Pass System        |\n";
		cout << "|Input 'new' to create new user or 'q' to exit program|\n";
		cout << "=======================================================\n";

		cout << "Username: ";
		getline(cin, username);

		transform(username.begin(), username.end(), username.begin(), 
			[] (char ch) { return tolower(ch); });

		if (username == "q") {
			cout << "Bye!";
			break;
		}

		if (username == "new")
			createNewUser();

		cout << "Password: ";
		getline(cin, password);

		if (username == adminLogin && password == adminPass) {
			system("cls");
			adminMenu();
		}
		else if (username == userLogin && password == userPass) {
			system("cls");
			userMenu();
		}
		else {
			cout << "Account not found. Would you like to create one? (y/n): ";
			cin >> ch;
			ch = static_cast<char>(tolower(ch));

			if (ch == 'y') {
				createNewUser();
			}
			else if(ch == 'n') {
				system("cls");
				clearBuffer();
				cout << "Terminated account creation.\n";
			}
			else {
				system("cls");
				clearBuffer();
				cout << "Invalid input, please enter only 'y' or 'n'.\n";
			}
		}
		
		break;
	}
}

void createNewUser() {
	system("cls");
	cout << "=====================================================\n";
	cout << "|                 CREATE NEW USER                   |\n";
	cout << "=====================================================\n";
	cout << "|Enter your personal details to create your account |\n";
	cout << "=====================================================\n";
	cout << "New Username: ";
	cin >> userLogin;
	cout << "New password: ";
	cin >> userPass;

	transform(userLogin.begin(), userLogin.end(), userLogin.begin(), 
		[] (char ch) { return tolower(ch); });

	cout << "Your account is already created,\nPlease login now.\n";

	clearBuffer();

	system("cls");
	mainMenu();
}

void clearBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}