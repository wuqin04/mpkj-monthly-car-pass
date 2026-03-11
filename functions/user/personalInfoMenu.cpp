#include <iostream>
#include <iomanip>

#include "user/userMenu.h"
using namespace std;

std::string name = "";

void userInfo(){
	
	int choice;
	
	cout << "===========================================\n";
    cout << "                USER INFOMATION            \n";
    cout << "===========================================\n";
	
    cout << "Name: " << "BEN" << endl;
    cout << "Student ID: " << 123 << endl;
    cout << "IC: " << 000000000000 << endl;
    cout << "Contact: " << 123456789 << endl;
    cout << "Faculty: " << "LKCFES" << endl;
    cout << "Car Plate: " << "WWW123" << endl;
    cout << "===========================================\n";
    cout << "          Choose an action (1-2):          \n";
    cout << "===========================================\n";
	cout << "1. Edit Information\n";
    cout << "2. Back to Main Menu\n";
    cout << "Choose option: ";
	cin >> choice;

    if (choice == 2) {
        userMenu();
    }
}

bool hasName() {
    return name != "";
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


