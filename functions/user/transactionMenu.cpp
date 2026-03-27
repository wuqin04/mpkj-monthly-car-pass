#include <iostream>
#include <iomanip>
#include <limits>
#include "user/userMenu.h"

using namespace std;

void transactionMenu(User &user) {
	while (true) {
		int choice = 0;
		cout << "===========================================\n";
        cout << "|          TRANSACTION HISTORY            |\n";
        cout << "===========================================\n";

		cout << "Transaction history: \n";

		cout << "===========================================\n";
		cout << "|(1) return to main menu                  |\n";
		cout << "===========================================\n";
		cout << "Choose an action: ";
				
        if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

		system("cls");
		switch (choice) {
			case 1:
				userMenu(user);
				break;
			default:
				cout << "Invalid input, try again.\n";
				continue;
		}

		break;
	}
	
}