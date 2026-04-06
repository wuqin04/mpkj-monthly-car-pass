#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

#include "user/userInfoMenu.h"
#include "user/userMenu.h"
using namespace std;

void User::userInfo(){
    bool infoComplete = (this->name != "" && this->studentId != "" && this->icNo != "" && this->contact != "" && this->faculty != "" && this->carPlate != "");
    
    while(true){
        int choice;
	    cout << "===========================================\n";
        cout << "|             PERSONAL DETAILS            |\n";
        cout << "===========================================\n";
            
        cout << "Name: " << this->name << endl;
        cout << "Student ID: " << this->studentId << endl;
        cout << "IC: " << this->icNo << endl;
        cout << "Contact Number: " << this->contact << endl;
        cout << "Faculty: " << this->faculty << endl;
        cout << "Car Plate Number: " << this->carPlate << endl;

        cout << "===========================================\n";

        if(!infoComplete){
            cout << "WARNING: PLease update your information!\n";
            cout << "===========================================\n";
        }

        cout << "|(1) edit information                     |\n";
        cout << "|(2) back to main menu                    |\n";
        cout << "===========================================\n";

        
	    
        cout << "Choose an action: ";
        cin >> choice;

        switch(choice){
        case 1:
            system("cls");
            editInfo();
            break;
        case 2:
            system("cls");
            userMenu(*this);
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

void User::editInfo() {
    while (true){
        int choice;

	    cout << "===========================================\n";
        cout << "|           INFORMATION EDITING           |\n";
        cout << "===========================================\n";

        cout << "Name: " << this->name << endl;
        cout << "Student ID: " << this->studentId << endl;
        cout << "IC: " << this->icNo << endl;
        cout << "Contact Number: " << this->contact << endl;
        cout << "Faculty: " << this->faculty << endl;
        cout << "Car Plate Number: " << this->carPlate << endl;

        cout << "=============================\n";
        cout << "|(1) edit Name              |\n";
        cout << "|(2) edit Student ID        |\n";
        cout << "|(3) edit IC                |\n";
        cout << "|(4) edit Contact Number    |\n";
        cout << "|(5) edit Faculty           |\n";
        cout << "|(6) edit Car Plate Number  |\n";
        cout << "|(7) back to user menu      |\n";        
        cout << "=============================\n";


        cout << "Choose an action: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter Name: ";
                getline(cin >> ws, this->name);
                system("cls");
                continue;   
            case 2:
                cout << "Enter Student ID: ";
                getline(cin >> ws, this->studentId);
                system("cls");
                continue;
            case 3:
                cout << "Enter IC: ";
                getline(cin >> ws, this->icNo);
                system("cls");
                continue;
            case 4:
                cout << "Enter Contact Number: ";
                getline(cin >> ws, this->contact);
                system("cls");
                continue;
            case 5:
                cout << "Enter Faculty: ";
                getline(cin >> ws, this->faculty);
                system("cls");
                continue;
            case 6 : 
                cout << "Enter Car Plate Number: ";
                getline(cin >> ws, this->carPlate);
                system("cls");
                continue;
            case 7:
                system("cls");
                userMenu(*this);
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