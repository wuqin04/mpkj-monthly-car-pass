#include <iostream>
#include <iomanip>
#include <limits>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/paymentMenu.h"

using namespace std;

void viewStatusMenu(User &user) {
	bool applicationStatus = true;
	
	while (true) {
		int choice;
		
		cout << "===========================================\n";
		cout << "            APPLICATION STATUS             \n";
		cout << "===========================================\n";

		if (applicationStatus == true)
			cout << "Your application is approved\n";

		cout << "===========================================\n";
		if (applicationStatus ==true)
			cout << "|(1) show due payment amount              |\n";
		if (applicationStatus == false)
			cout << "|(1) show reason for rejection            |\n";
			
		cout << "|(2) return to main menu                  |\n";



		cout << "===========================================\n";
		cout << "Choose an action (1-2): ";

		if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
		
		system("cls");

		if (choice == 1) {
			userMenu();
		}
		else if (choice == 2 && applicationStatus == true) {
			paymentMenu(user);
		}
		else if (choice == 2 && applicationStatus == false) {
			cout << "reason";
		}
		else {
			cout << "Invalid input, try again.\n";
			continue;
		}

		break;
	}	
	
}
