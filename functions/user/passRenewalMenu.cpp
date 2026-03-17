#include <iostream>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/viewStatusMenu.h"
using namespace std;

const int INFO_INCOMPLETE = 0;
const int INFO_COMPLETED = 1;
const int APPLIED_PASS = 2;
int passStatus = 0;

void getPassStatus(){
	if (passStatus == INFO_INCOMPLETE) 
        cout << "WARNING: Your personal information is not complete.\nPlease update your information." << endl;
    else if (passStatus == INFO_COMPLETED)
        cout << "You are eligible to apply for a monthly car pass." << endl;
    else if (passStatus == APPLIED_PASS)
        cout << "Your application is being processed.\nCheck your application in Status Menu." << endl;
}

 void infoComplete(User &user){
     if (user.name != "" && user.studentId != "" && user.ic != "" && user.contact != "" && user.faculty != "" && user.carPlate != "")
         passStatus = INFO_COMPLETED;
     else
         passStatus = INFO_INCOMPLETE;
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
		cout << "         MONTHLY PASS APPLICATION          \n";
		cout << "===========================================\n";
        getPassStatus();

		cout << "===========================================\n";
		cout << "(1) apply for monthly car pass\n";
        cout << "(2) application status menu\n";
		cout << "(3) update information\n";
        cout << "(4) back to main menu\n";
        cout << "===========================================\n";
		cout << "Choose an action (1-4): ";       
		cin >> choice;

		switch(choice){
            case 1:
                system("cls");
                passStatus = 2;
                continue;;
            case 2:
                system("cls");
                viewStatusMenu(user);
                break;
            case 3:
                system("cls");
                user.userInfo();
                break;
            case 4:
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