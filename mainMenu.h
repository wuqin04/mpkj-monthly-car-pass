#include <iostream>
#include <string>
#include "userMenu.h"
using namespace std;


void mainMenu() {
	const string adminLogin = "admin";
	const string adminPass = "admin";
	const string userLogin = "user";
	const string userPass = "user";

	string name = "";
	string password = "";

	cout << "==========================\n";
	cout << "	MAIN MENU	  \n";
	cout << "==========================\n";

	cout << "\n\n";
	
	cout << "Username: ";
	getline(cin, name);

	cout << "Password: ";
	getline(cin, password);

	if (name == adminLogin && password == adminPass) {
		cout << "Welcome Admin!";
	}
	
	if (name == userLogin && password == userPass) {
		system("cls");
		userMenu();
	}
}

