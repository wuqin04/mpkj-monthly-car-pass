#include <iostream>
#include <iomanip>
#include <limits>
#include "user/userMenu.h"

using namespace std;

void transactionMenu() {
	while (true) {
		int choice = 0;
		cout << "===========================================\n";
        cout << "           TRANSACTION HISTORY             \n";
        cout << "===========================================\n";
		cout << "===========================================\n";
		cout << "|(1) return to main menu            |\n";
		cout << "===========================================\n";
		cout << "Choose an action (1): ";
				
        if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

		system("cls");
		switch (choice) {
			case 1:
				userMenu();
				break;
			default:
				cout << "Invalid input, try again.\n";
				continue;
		}

		break;
	}
	
}