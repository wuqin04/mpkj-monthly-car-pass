#include <iostream>
#include <iomanip>
#include <string>
#include "user/userMenu.h"
#include "user/personalInfoMenu.h"

using namespace std;

void paymentMenu() {
	while(true){
		int choice;

		cout << "====================================================================\n";
		cout << "|                           PAYMENT MENU                           |\n";
		cout << "====================================================================\n";
		cout << "ID: " << studentId << endl;
		cout << "Name: " << name << endl;
		cout << "Amount due: RM" << endl;
		cout << "If there are any problems or if you wish to settle your payment,\n";
		cout << "please proceed to the Department of Finance for assistance.\n";
		cout << "====================================================================\n";
		cout << "|(1) return to user main menu                                      |\n";
		cout << "====================================================================\n";
		cout << "Enter the number for the action you wish to perform: ";
		cin >> choice;
	
		switch (choice){
			case 1:
				system("cls");
				userMenu();
				break;
			default:
				system("cls");
				cin.clear();
				cin.ignore();
				cout << "Invalid input, please try again.\n";
				continue;
		}
		break;
	}
}