#include <iostream>
#include <string>
#include "mainMenu.h"
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
using namespace std;

void mainMenu() {
	const string adminLogin = "admin";
	const string adminPass = "admin";
	const string userLogin = "user";
	const string userPass = "user";

	string name = "";
	string password = "";

	cout << "===========================================\n";
	cout << "                MAIN MENU                  \n";
	cout << "===========================================\n";
	cout << "Welcome to MPKJ Monthly Car Pass System.   \n";
	cout << "===========================================\n";

	cout << "Username: ";
	getline(cin, name);

	cout << "Password: ";
	getline(cin, password);

	if (name == adminLogin && password == adminPass) {
		cout << "Welcome Admin!";
	}
	else if (name == userLogin && password == userPass) {
		system("cls");
		userMenu();
	}
	else {
		cout << "Account not found. Would you like to create one? (y/n): \n";
		cout << "You can't create new user yet xd.";
	}
}
