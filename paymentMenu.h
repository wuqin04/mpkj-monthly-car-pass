#include <iostream>
#include <iomanip>

using namespace std;

void paymentMenu() {
	system("cls");
	
	int choice;
	string Id, Name;
	double payment;

	cout << "====================================================================\n";
	cout << "|                           PAYMENT MENU                           |\n";
	cout << "====================================================================\n";
	cout << "ID: " << Id << endl;
	cout << "Name: " << Name << endl;
	cout << "Amount due: RM" << payment << endl;
	cout << "If there are any problems or if you wish to settle your payment,\n";
	cout << "please proceed to the Department of Finance for assistance.\n";
	cout << "====================================================================\n";
	cout << "|(1) return to user main menu                                      |\n";
	cout << "====================================================================\n";
	cout << "Enter the number for the action you wish to perform: ";
	cin >> choice;
	
	if (choice == 1)
		userMenu();
}
