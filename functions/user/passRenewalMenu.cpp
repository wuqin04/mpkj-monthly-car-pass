#include <iostream>
#include "user/userInfoMenu.h"
using namespace std;

void passStatus getPassStatus(){
	if (userInfoMenu::userInfoComplete == 0)
		cout << "EXPIRED! Please renew your monthly pass." << endl;
	else if (renewalStatus == 1)
		cout << "ACTIVE. Your monthly pass is valid." << endl;
	return Active;
}

void passApplyRenewal(){
	cout << "Your application is being processed. Please wait for the result." << endl;
	renewalStatus = 1;
}

void passRenewalMenu(){
	while(true){
		int choice;

		cout << "===========================================\n";
		cout << "            MONTHLY PASS STATUS            \n";
		cout << "===========================================\n";

		cout << "Pass Status: " << getPassStatus() << "\n";

		cout << "===========================================\n";
        cout << "          Choose an action (1-2):          \n";
        cout << "===========================================\n";
		cout << "1. Pass apply/renewal application\n";
		cout << "2. Back to user menu\n";
		cout << "Choose an option: ";
		cin >> choice;

		switch(choice){
            case 1:
                system("cls");
                passRenewal();
                break;
            case 2:
                system("cls");
                mainMenu();
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