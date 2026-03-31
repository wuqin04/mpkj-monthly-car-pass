#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/paymentMenu.h"
#include "user/passRenewalMenu.h"

using namespace std;

void viewStatusMenu(User &user) {

	Pass pass;

	while (true){

		int choice;
		
		cout << "===========================================\n";
		cout << "|           APPLICATION STATUS            |\n";
		cout << "===========================================\n";	
		
		if (pass.applyStatus == "1"){
			cout << "\nYour application is approved\n\n";
		}

		else if (pass.applyStatus == "2"){
			cout << "\nYour application is rejected\n\n";
		}

		else if (pass.applyStatus == "3"){
			cout << "\nYour application is still pending for review\n\n";
		}
		
		else {
			cout << "You have yet to apply for a car pass\n";
		}

		cout << "===========================================\n";
		
		if (pass.applyStatus == "1"){
			cout << "|(1) show due payment amount              |\n";
			cout << "|(2) return to main menu                  |\n";
		}

		else if (pass.applyStatus == "2"){
			cout << "|(1) show reason for rejection            |\n";
			cout << "|(2) reapply for car pass                 |\n";
			cout << "|(3) return to main menu                  |\n";
		}

		else if (pass.applyStatus == "3"){
			cout << "|(1) return to main menu                  |\n";
		}
		
		else {
				cout << "|(1) apply for car pass                   |\n";
				cout << "|(2) return to main menu                  |\n";
		}
		
		cout << "===========================================\n";
		cout << "Choose an action: ";
		cin >> choice;

		if (pass.applyStatus == "1"){
			switch(choice){
					case 1:
						system("cls");
						paymentMenu(user);
						break;
					case 2:
						system("cls");
						userMenu(user);
						break;
					default:
						system("cls");
						cin.clear();
						cin.ignore();
						cout << "Invalid input, please try again.\n";
						continue;
			}
		}
		
		else if (pass.applyStatus == "2"){
			switch (choice){
				case 1:
					system("cls");
					cout << "===========================\n";
					cout << "|  Reason for rejection:  |\n";
					cout << "|  Press ENTER to return  |\n";
					cout << "===========================\n";
					system("pause");
					system("cls");
					continue;
				case 2:
					system("cls");
					passRenewalMenu(user);
					break;
				case 3:
					system("cls");
					userMenu(user);
					break;
				default:
					system("cls");
					cin.clear();
					cin.ignore();
					cout << "Invalid input, please try again.\n";
					continue;
			}
		}
		
		else if (pass.applyStatus == "3"){
			switch (choice){
				case 1:
					system("cls");
					userMenu(user);
					break;

			default:
					system("cls");
					cin.clear();
					cin.ignore();
					cout << "Invalid input, please try again.\n";
					continue;
			}
		}
	

		else {
			switch(choice){
				case 1:
					system("cls");
					passRenewalMenu(user);
					break;
				case 2:
					system("cls");
					userMenu(user);
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
	
