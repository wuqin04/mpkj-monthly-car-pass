#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <filesystem>
#include <cctype>
#include <algorithm>
#include <limits>
#include "mainMenu.h"
#include "user/userMenu.h"
#include "admin/adminMenu.h"
#include "user/userInfoMenu.h"
#include "admin/adminMenu.h"

using namespace std;

const string adminLogin = "admin";
const string adminPass = "admin";

void mainMenu() {
	string filePath = "data.txt";
    ifstream inputFile(filePath);

    string line = "";
    vector<User> users;
    User user;

    if (!inputFile.is_open()) {
        std::cerr << "ERROR! CANNOT RETRIEVE THE DATA FILE.\n";
        return;
    }

    getline(inputFile, line);

    while (getline(inputFile, line)) {
        stringstream ss(line);
        string token;

        getline(ss, user.username, ',');
        getline(ss, user.password, ',');
        getline(ss, user.name, ',');
        getline(ss, user.studentId, ',');
        getline(ss, user.icNo, ',');
        getline(ss, user.contact, ',');
        getline(ss, user.faculty, ',');
        getline(ss, user.carPlate, ',');
        getline(ss, user.submissionStatus, ',');

        getline(ss, token, ',');
        user.paymentAmount = stod(token);

        getline(ss, user.paymentStatus, ',');
        getline(ss, user.passStatus, ',');

        users.push_back(user);
    }

    cout << "Retrived file successfully!\n";

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

		for (long long unsigned int i = 0; i < users.size(); i++) {
			if (username == users[i].username && password == users[i].password) {
				system("cls");
				userMenu(user);
				break;
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
					break;
				}
				else {
					system("cls");
					clearBuffer();
					cout << "Invalid input, please enter only 'y' or 'n'.\n";
				}
			}
		}
	
		break;
	}
}

void createNewUser() {
	string newUser;
	string newPassword;
	system("cls");
	cout << "=====================================================\n";
	cout << "|                 CREATE NEW USER                   |\n";
	cout << "=====================================================\n";
	cout << "|Enter your personal details to create your account |\n";
	cout << "=====================================================\n";
	cout << "New Username: ";
	cin >> newUser;
	cout << "New password: ";
	cin >> newPassword;

	transform(newUser.begin(), newUser.end(), newUser.begin(), 
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