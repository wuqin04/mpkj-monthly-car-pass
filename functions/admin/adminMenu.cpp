#include <iostream>
#include <limits>
#include "admin/adminMenu.h"
#include "admin/statusMenu.h"
#include "admin/paymentHistory.h"
using namespace std;
void paymentHistory();
void adminMenu() {
    while (true) {
        cout << "===========================================\n";
        cout << "                ADMIN MENU                 \n";
        cout << "===========================================\n";

        cout << "===========================================\n";
        cout << "|(1) view user payment history             |\n";
        cout << "|(2) view user monthly pass status         |\n";
        cout << "|(3) exit program                          |\n";
        cout << "===========================================\n";

        cout << "Choose an action: ";
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
                paymentHistory();
                break;
            case 2:
                statusMenu();
                break;
            case 3:
                cout << "Bye!";
                return;
            default:
                cout << "Invalid input, try again.\n";
                continue;
        }
        break;
    }
}