#include <iostream>
#include <iomanip>
#include "user/userMenu.h"
#include "user/paymentMenu.h"

using namespace std;

void viewStatusMenu() {
	system("cls");
	
	int choice;
	bool applicationStatus = true;
	
	cout << "====================================================================\n";
	cout << "|                        APPLICATION STATUS                        |\n";
	cout << "====================================================================\n";

	if (applicationStatus == true)
		cout << "Your application is approved\n";

	cout << "====================================================================\n";
	cout << "|(1) return to user main menu                                      |\n";

	if (applicationStatus ==true)
		cout << "|(2) show due payment amount                                       |\n";
	if (applicationStatus == false)
		cout << "|(2) show reason for rejection                                     |\n";

	cout << "====================================================================\n";
	cout << "Enter the number of the action you wish to perform: ";
	cin >> choice;
	
	if (choice == 1)
		userMenu();
	else if (choice == 2 && applicationStatus == true)
		paymentMenu();
	else if (choice == 2 && applicationStatus == false)
		cout << "reason";
}
