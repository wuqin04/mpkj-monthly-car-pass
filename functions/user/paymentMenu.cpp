#include <iostream>
#include <iomanip>
#include <string>
#include "mainMenu.h"
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/passRenewalMenu.h"

using namespace std;

bool paymentMade; 

void paymentMenu(User &user) {

	Pass pass;

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
		if (paymentMade == false && pass.choice == "month"){
			cout << "Amount due: RM " << pass.monthPrice << endl;
		}
		if (paymentMade == false && pass.choice == "sem"){
			cout << "Amount due: RM " << pass.semPrice << endl;
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
		cout << "Choose an action: ";
		cin >> choice;
	
		if (paymentMade == true){
			switch (choice){
				case 1:
					system("cls");
					return;
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
					cout << "=============================\n";
					cout << "| Payment successfully made |\n";
					cout << "|   Press ENTER to return   |\n";
					cout << "=============================\n";
					paymentMade = true;
					system("pause");
					system("cls");
					continue;
				case 2:
					system("cls");
					return;
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