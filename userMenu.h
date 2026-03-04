#include <iostream>
#include <limits>
using namespace std;

void userMenu() {
    while (true) {
        cout << "===========================================\n";
        cout << "                USER MENU                  \n";
        cout << "===========================================\n";

        cout << "===========================================\n";
        cout << "|(1) view/update personal information     |\n";
        cout << "|(2) apply/renew monthly car parking pass |\n";
        cout << "|(3) view application status              |\n";
        cout << "|(4) track transaction history            |\n";
        cout << "|(5) exit program                         |\n";
        cout << "===========================================\n";

        cout << "Choose an action (1-5):";
        int choice = 0;
        if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        system("cls");
        switch (choice) {
            case 1:
                cout << "entering personalInfoMenu()";
                break;
            case 2:
                cout << "entering passRenewalMenu()";
                break;
            case 3:
                cout << "entering viewStatusMenu()";
                break;
            case 4:
                cout << "entering paymentMenu()";
                break;
            case 5:
                cout << "exiting program";
                break;
            default:
                cout << "Invalid input, try again.\n";
                continue;
        }

        break;
    }
    
}