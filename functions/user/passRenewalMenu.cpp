#include <iostream>
#include <string>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/viewStatusMenu.h"
#include "user/passRenewalMenu.h"
using namespace std;

const string INFO_INCOMPLETE = "0";
const string INFO_COMPLETED = "1";
const string APPLIED_PASS = "2";

Pass pass;

void getPassStatus(){
	if (pass.passStatus == INFO_INCOMPLETE) 
        cout << "WARNING: Your personal information is not complete.\nPlease update your information." << endl;
    else if (pass.passStatus == INFO_COMPLETED)
        cout << "You are eligible to apply for a monthly car pass." << endl;
    else if (pass.passStatus == APPLIED_PASS)
        cout << "Your application is being processed.\nCheck your application in Status Menu." << endl;
}

void infoComplete(User &user){
    if (user.name != "" && user.studentId != "" && user.icNo != "" && user.contact != "" && user.faculty != "" && user.carPlate != "")
        pass.passStatus = INFO_COMPLETED;
    else
        pass.passStatus = INFO_INCOMPLETE;
}

void passChoice(){

    while(true){
        int choice;
        double monthPrice = 31.80, semPrice = (monthPrice * 4) * 95 / 100;

        cout << "===========================================================\n";
	    cout << "|            MONTHLY PASS APPLICATION CHOICES             |\n";
	    cout << "===========================================================\n";
        cout << "|Choice comparison:                                       |\n";
        cout << "|Monthly                                                  |\n";
        cout << "|  -RM " << monthPrice << "                                               |\n";
        cout << "|  -lasts only for one month                              |\n";
        cout << "|                                                         |\n";
        cout << "|Per semester                                             |\n";
        cout << "|  -RM " << semPrice << "                                             |\n";
        cout << "|  -lasts for 4 months (about a semesters' worth)         |\n";
        cout << "|  -save up to 5% compared to buying monthly for 4 months |\n";
        cout << "===========================================================\n";
	    cout << "|(1) one month                                            |\n";
        cout << "|(2) one semester                                         |\n";
        cout << "|(3) cancel                                               |\n";
        cout << "===========================================================\n";
        cout << "Choose the type of pass you wish to apply: ";
        cin >> choice;

        switch(choice){
            case 1:
                system("cls");
                pass.choice = "month";
                pass.passStatus = APPLIED_PASS; 
                pass.applyStatus = "3";
                break;
            case 2:
                system("cls");
                pass.choice = "sem";
                pass.passStatus = APPLIED_PASS; 
                pass.applyStatus = "3";
                break;
            case 3:
                system("cls");
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

void passRenewalMenu(User &user){
    user.name = "John Doe";
    user.studentId = "123456789";
    user.icNo = "900101-01-1234";
    user.contact = "012-3456789";
    user.faculty = "Engineering";
    user.carPlate = "ABC1234";
    infoComplete(user);

	while(true){
		int choice;

		cout << "=====================================================\n";
		cout << "|              MONTHLY PASS APPLICATION             |\n";
		cout << "=====================================================\n";
        getPassStatus();

		cout << "=====================================================\n";

        if (pass.passStatus != "2"){
		    cout << "|(1) apply for monthly car pass                     |\n";
            cout << "|(2) application status menu                        |\n";
		    cout << "|(3) update information                             |\n";
            cout << "|(4) back to main menu                              |\n";
            cout << "=====================================================\n";
		    cout << "Choose an action: ";       
		    cin >> choice;

		    switch(choice){
            case 1:
                system("cls");
                passChoice();      
                continue;
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
        }

        else if(pass.passStatus == "2"){
            cout << "|(1) application status menu                        |\n";
		    cout << "|(2) update information                             |\n";
            cout << "|(3) back to main menu                              |\n";
            cout << "=====================================================\n";
		    cout << "Choose an action: ";       
		    cin >> choice;

		    switch(choice){
            case 1:
                system("cls");
                viewStatusMenu(user);
                break;
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
        }
    break;
    }       
}