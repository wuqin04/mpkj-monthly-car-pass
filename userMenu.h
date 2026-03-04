#include <iostream>
using namespace std;

void userMenu() {
    cout << "===========================================\n";
	cout << "                USER MENU                  \n";
    cout << "===========================================\n";

    cout << "===========================================\n";
    cout << "|(1) view/update personal information     |\n";
    cout << "|(2) apply/renew monthly car parking pass |\n";
    cout << "|(3) view application status              |\n";
    cout << "|(4) track transaction history            |\n";
    cout << "===========================================\n";

    cout << "Choose an action (1-4):";
    int choice = 0;
    cin >> choice;

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
        default:
            cout << "Invalid input, try again.";
            break;
    }
}