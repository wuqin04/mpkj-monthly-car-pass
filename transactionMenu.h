#include <iostream>
#include <iomanip>
#include "userMenu.h"

using namespace std;

void transactionMenu() {
	system("cls");
	
	int choice;
	
	cout << "====================================================================\n";
	cout << "|                       TRANSACTION HISTORY                        |\n";
	cout << "====================================================================\n";
	cout << "Transaction History here\n";
	cout << "====================================================================\n";
	cout << "|(1) return to user main menu                                      |\n";
	cout << "====================================================================\n";
	cout << "Enter the number of the action you wish to perform: ";
	cin >> choice;
	
	if (choice == 1)
		userMenu();
}
