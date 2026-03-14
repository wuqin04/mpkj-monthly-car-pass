#include <iostream>
#include <iomanip>
#include <string>

#include "user/userMenu.h"
using namespace std;

extern string name = "";
extern string studentId = "";
extern string ic = "";
extern string contact = "";
extern string faculty = "";
extern string carPlate = "";

bool infoComplete = (name != "" && studentId != "" && ic != "" && contact != "" && faculty != "" && carPlate != "");

void userInfo(){
    while(true){
        int choice;
	    cout << "===========================================\n";
        cout << "                USER INFOMATION            \n";
        cout << "===========================================\n";
            
        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentId << endl;
        cout << "IC: " << ic << endl;
        cout << "Contact Number: " << contact << endl;
        cout << "Faculty: " << faculty << endl;
        cout << "Car Plate Number: " << carPlate << endl;

        cout << "===========================================\n";
        cout << "          Choose an action (1-2):          \n";
        cout << "===========================================\n";

        if(!infoComplete){
            cout << "PLease update your information.\n";
        }
	    cout << "1. Edit Information\n";
        cout << "2. Back to Main Menu\n";
        cout << "Choose option: ";
        cin >> choice;

            switch(choice){
            case 1:
                system("cls");
                editInfo();
                break;
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
        break;
    }
}

void editInfo() {
    while (true){
        int choice;

        cout << "============================\n";
        cout << "    Information Editing\n";
        cout << "============================\n";

        cout << "Name: " << name << endl;
        cout << "Student ID: " << studentId << endl;
        cout << "IC: " << ic << endl;
        cout << "Contact Number: " << contact << endl;
        cout << "Faculty: " << faculty << endl;
        cout << "Car Plate Number: " << carPlate << endl;

        cout << "=============================\n";
        cout << "     Choose an option :\n";
        cout << "=============================\n";
        cout << "1. Edit name\n";
        cout << "2. Edit Student ID\n";
        cout << "3. Edit IC\n";
        cout << "4. Edit Contact Number\n";
        cout << "5. Edit Faculty\n";
        cout << "6. Edit Car Plate Number\n";
        cout << "7. Back to user menu\n";

        cout << "Choose option: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter name: ";
                cin >> name;
                system("cls");
                continue;;
            case 2:
                cout << "Enter Student ID: ";
                cin >> studentId;
                system("cls");
                continue;
            case 3:
                cout << "Enter IC: ";
                cin >> ic;
                system("cls");
                continue;
            case 4:
                cout << "Enter Contact Number: ";
                cin >> contact;
                system("cls");
                continue;
            case 5:
                cout << "Enter Faculty: ";
                cin >> faculty;
                system("cls");
                continue;
            case 6 : 
                cout << "Enter Car Plate Number: ";
                cin >> carPlate;
                system("cls");
                continue;
            case 7:
                system("cls");
                userMenu();
                break;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalide input, please try again.\n";
            continue;
        }
        break;
    }
}

//void editInfo(){
//	cout << "\nEdit Information\n";
//    inputInfo();
//}

//	  string userName;
//    string userID;
//    string userIC;
//    string userNum;
//    string userFaculty;
//    string userPlate;
//    bool dataExists = false;

    
//void inputInfo(){
//    cout << "\nEnter Your Information\n";
//
//    cout << "Your Name: ";
//    getline(cin, userName);
//    
//    cout << "Your Student ID: ";
//    cin  >> userID;
//
//    cout << "Your IC Number: ";
//    cin  >> userIC;
//
//    cout << "Your Contact Number: ";
//    cin  >> userNum;
//
//    cout << "Your Faculty: ";
//    cin  >> userFaculty;
//
//    cout << "Your Car Plate: ";
//    cin  >> userPlate;
//    
//}


