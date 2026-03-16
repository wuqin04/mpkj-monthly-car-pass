#include <iostream>
#include <iomanip>

#include "user/userMenu.h"
using namespace std;

int choice;
string userName;
string userID;
string userIC;
string userNum;
string userFaculty;
string userPlate;

void userInfo(){

	cout << "===========================================\n";
    cout << "                USER INFOMATION            \n";
    cout << "===========================================\n";
	
    cout << "Name: " << userName << endl;
    cout << "Student ID: " << userID << endl;
    cout << "IC: " << userIC << endl;
    cout << "Contact: " << userNum << endl;
    cout << "Faculty: " << userFaculty << endl;
    cout << "Car Plate: " << userPlate << endl;
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
    else if (choice == 1) {
        editInfo();
    }
    else {
        cout << "Invalid choice. Please select between (1-2).\n";
        userInfo();
    }
}

bool hasName() {
    return userName != "";
}
bool hasID() {
    return userID != "";
}
bool hasIC() {
    return userIC != "";
}
bool hasNum() {
    return userNum != "";
}
bool hasFaculty() {
    return userFaculty != "";
}
bool hasPlate() {
    return userPlate != "";
}

void editInfo(){
	cout << "===========================================\n";
    cout << "           EDIT USER INFOMATION            \n";
    cout << "===========================================\n";
    inputInfo();
}

    
void inputInfo(){
    cout << "\nEnter Your Information\n";

    cout << "Your Name: ";
    getline(cin,userName);
    
    cout << "Your Student ID: ";
    getline(cin,userID);

    cout << "Your IC Number: ";
    getline(cin,userIC);

    cout << "Your Contact Number: ";
    getline(cin,userNum);

    cout << "Your Faculty: ";
    getline(cin,userFaculty);

    cout << "Your Car Plate: ";
    getline(cin,userPlate);
    
}
