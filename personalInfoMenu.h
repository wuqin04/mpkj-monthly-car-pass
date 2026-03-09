#include <iostream>
#include <iomanip>
using namespace std;

int personalInfoMenu (void){
	cout << "============================\n";
	cout << "PERSONAL INFOMATION\n";
	cout << "============================\n";
	
	string userName;
    string userID;
    string userIC;
    string userNum;
    string userFaculty;
    string userPlate;
    bool dataExists = false;
    
    void inputInfo(){
    cout << "\nEnter Your Information\n";

    cout << "Your Name: ";
    getline(cin, userName);
    
    cout << "Your Student ID: ";
    cin  >> userID;

    cout << "Your IC Number: ";
    cin  >> userIC;

    cout << "Your Contact Number: ";
    cin  >> userNum;

    cout << "Your Faculty: ";
    cin  >> userFaculty;

    cout << "Your Car Plate: ";
    cin  >> userPlate;
    
}

void displayInfo(){
	cout << "\n===== USER INFORMATION =====\n";
	
    cout << "Name: " << userName << endl;
    cout << "Student ID: " << userID << endl;
    cout << "IC: " << userIC << endl;
    cout << "Contact: " << userNum << endl;
    cout << "Faculty: " << userFaculty << endl;
    cout << "Car Plate: " << userPlate << endl;
	
}

void editInfo;(){
	cout << "\nEdit Information\n";
    inputInfo();
}

void menu(){
	cout << "============================\n";
	cout << "CHANGING MENU\n";
	cout << "============================\n";
	
	cout << "1. Enter Information\n";
    cout << "2. Display Information\n";
    cout << "3. Edit Information\n";
    cout << "4. Exit\n";
    cout << "Choose option: ";
    cin >> choice;
}

