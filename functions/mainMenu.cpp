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
#include "globals.h"

using namespace std;

void mainMenu() {
    ifstream inputFile(Settings::filePath);

    string line = "";
    vector<User> users;
    User user;

    if (!inputFile.is_open()) {
        cerr << "ERROR! CANNOT RETRIEVE THE DATA FILE.\n";
        return;
    }
	
	// ignore the first header line
    getline(inputFile, line);

	// get every single user information and store them into vector
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

		// convert string into double data type
        getline(ss, token, ',');
        user.paymentAmount = stod(token);

        getline(ss, user.paymentStatus, ',');
        getline(ss, user.passStatus, ',');

        users.push_back(user);
    }

	inputFile.close();

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

		// convert every characters into lowercase
		transform(username.begin(), username.end(), username.begin(), 
			[] (char ch) { return tolower(ch); });

		if (username == "q") {
			cout << "Bye!";
			return;
		}

		if (username == "new") {
			createNewUser(users);
			continue;
		}

		cout << "Password: ";
		getline(cin, password);

		if (username == Settings::adminLogin && password == Settings::adminPass) {
			system("cls");
			adminMenu();
			break;
		}
 
		// check if user's login and password are store into our data.txt file
		for (long long unsigned int i = 0; i < users.size(); i++) {
			if (username == users[i].username && password == users[i].password) {
				system("cls");
				userMenu(users[i], users);
				return;
			}
		}

		cout << "Account not found. Would you like to create one? (y/n): ";
		cin >> ch;
		ch = static_cast<char>(tolower(ch));

		if (ch == 'y') {
			createNewUser(users);
			continue; 
		}
		else if(ch == 'n') {
			system("cls");
			clearBuffer(); 
			cout << "Terminated account creation.\n";
			cout << "Press Enter to return...";
			cin.get();
			system("cls");
			continue;
		}
		else {
			system("cls");
			clearBuffer();
			cout << "Invalid input, please enter only 'y' or 'n'.\n";
			cout << "Press Enter to continue...";
			cin.get();
			system("cls");
			continue;
		}
		break;
	}
}

void createNewUser(vector<User> &users) {
	while (true) {
		string newUser;
		string newPassword;

		system("cls");
		cout << "=====================================================\n";
		cout << "|                 CREATE NEW USER                   |\n";
		cout << "=====================================================\n";
		cout << "|Enter your new username and new password           |\n";
		cout << "|or 'q' to terminate account creation.              |\n";
		cout << "=====================================================\n";
		cout << "New Username: ";
		cin >> newUser;

		transform(newUser.begin(), newUser.end(), newUser.begin(), 
			[] (char ch) { return tolower(ch); });

		if (newUser == "q") {
			clearBuffer();
			system("cls");
			return;
		}

		if (containInvalidChar(newUser)) {
			cout << "Username cannot contain special characters, please try again.\n";
			cout << "Enter to continue...";
			clearBuffer();
			cin.get();
			system("cls");
			continue;
		}

		cout << "New password: ";
		cin >> newPassword;

		// check whether the username already exist
		if (isUserExist(newUser, users)) {
			cout << "The username is already taken, please try again.\n";
			cout << "Enter to continue...";
			clearBuffer();
			cin.get();
			system("cls");
			continue;
		}
		else {
			ofstream newLogin(Settings::filePath, ios::app);

			if (!newLogin.is_open()){
				cerr << "ERROR: CANNOT OPEN FILE FOR APPENDING.\n";
				return;
			}

			newLogin << newUser << "," << newPassword << ",-,-,-,-,-,-,-_-,0.00,-_-,-" << "\n";
			newLogin.close();
			User u;
			u.username = newUser;
			u.password = newPassword;
			u.name = "-";
			u.studentId = "-";
			u.icNo = "-";
			u.contact = "-";
			u.faculty = "-";
			u.carPlate = "-";
			u.submissionStatus = "-_-";
			u.paymentAmount = 0.00;
			u.paymentStatus = "-_-";
			u.passStatus = "-";
			users.push_back(u);
			cout << u.username << u.password;

			cout << "Your account is already created,\nPlease login now.\n";

			clearBuffer();

			cout << "Press Enter to return to main menu...";
			cin.get();

			system("cls");
			break;
		}	
		break;	
	}
	return;
}

// check whether the newUser is already exist in our system
bool isUserExist(string newUser, vector<User> users) {
	for (long long unsigned int i = 0; i < users.size(); i++) {
		if (newUser == users[i].username)
			return true;
	}
	return false;
}

// check if string contains special chars
bool containInvalidChar(string username) {
	for (unsigned char c : username) {
		if (!isalnum(c)) {
			return true;
		}
	}
	return false;
}