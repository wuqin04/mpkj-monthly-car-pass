#include <iostream>
#include <iomanip>
#include <limits>
#include "user/userMenu.h"

using namespace std;

void paymentMenu() {
	bool isPaid = false;
	int choice;
	string id, name;
	double payment = 0.0;
	
	while (true) {
		
		string paymentStatus = isPaid? "Received": "Pending";

		cout << "===========================================\n";
		cout << "               PAYMENT MENU                \n";
		cout << "===========================================\n";

		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Amount due: RM" << fixed << setprecision(2)<< payment << endl;
		cout << "Payment status: " << paymentStatus << endl;
		cout << "If there are any problems or if you wish to settle your payment,\n";
		cout << "please proceed to the Department of Finance for assistance.\n";
		cout << "===========================================\n";
		cout << "|(1) Online Banking (FPX)                 |\n";
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
		switch (choice) {
			case 1:
				cout << "Payment succeed.\n";
				isPaid = true;
				continue;
			case 2:
				userMenu();
				break;
			default:
				cout << "Invalid input, try again.";
				continue;
		}
		
		break;
	}	
}
