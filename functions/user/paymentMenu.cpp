#include <iostream>
#include <iomanip>
#include <string>
#include "mainMenu.h"
#include "user/userMenu.h"
#include "user/userInfoMenu.h"

using namespace std;

	bool paymentMade = false; 

void paymentMenu(User &user) {
	while(true){
		int choice;

		cout << "====================================================================\n";
		cout << "|                           PAYMENT MENU                           |\n";
		cout << "====================================================================\n";
		cout << "ID: " << user.studentId << endl;
		cout << "Name: " << user.name << endl;

		if (paymentMade == true){
			cout << "You have settled your payment.\n";
		}
		if (paymentMade == false){
			cout << "Amount due: RM" << endl;
		}

		cout << "If there are any problems or if you wish to settle your payment,\n";
		cout << "please proceed to the Department of Finance for assistance.\n";
		cout << "====================================================================\n";

		if (paymentMade == true){
			cout << "|(1) return to user main menu                                      |\n";
		}
		else if (paymentMade == false){
			cout << "|(1) make payment                                                  |\n";
			cout << "|(2) return to user main menu                                      |\n";
		}
		
		cout << "====================================================================\n";
		cout << "Enter your choice: ";
		cin >> choice;
	
		if (paymentMade == true){
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
		}
		else if (paymentMade == false){
			switch(choice){
				case 1:
					system("cls");
					cout << "====================================================================\n";
					cout << "Payment successfully made.\n";
					cout << "Press ENTER to return.\n";
					cout << "====================================================================\n";
					paymentMade = true;
					system("pause");
					system("cls");
					continue;
				case 2:
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
		}
		break;
	}
}