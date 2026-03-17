#include <iostream>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
using namespace std;

int passStatus = 0;

void getPassStatus(){
	if (passStatus == 0)
        cout << "WARNING: Your personal information is not complete. Please update your information." << endl;
    else if (passStatus == 1)
        cout << "You are eligible to apply for a monthly car pass." << endl;
    else if (passStatus == 2)
        cout << "Your application is being processed. Please wait for the result." << endl;
}

 void infoComplete(User &user){
     if (user.name != "" && user.studentId != "" && user.ic != "" && user.contact != "" && user.faculty != "" && user.carPlate != "")
         passStatus = 1;
     else
         passStatus = 0;
 }

void passRenewalMenu(User &user){
    user.name = "John Doe";
    user.studentId = "123456789";
    user.ic = "900101-01-1234";
    user.contact = "012-3456789";
    user.faculty = "Engineering";
    user.carPlate = "ABC1234";
    infoComplete(user);

	while(true){
		int choice;

		cout << "===========================================\n";
		cout << "            MONTHLY PASS STATUS            \n";
		cout << "===========================================\n";
        getPassStatus();

		cout << "===========================================\n";
        cout << "          Choose an action (1-2):          \n";
        cout << "===========================================\n";
		cout << "1. Apply for monthly car pass\n";
		cout << "2. Back to user info menu\n";
        cout << "3. Back to main menu\n";
		cout << "Choose an option: ";
		cin >> choice;

		switch(choice){
            case 1:
                system("cls");
                passStatus = 2;
                continue;;
            case 2:
                system("cls");
                user.userInfo();
                break;
            case 3:
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