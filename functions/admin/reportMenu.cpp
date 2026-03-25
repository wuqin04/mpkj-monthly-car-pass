#include <iostream>
#include <iomanip>
#include "admin/adminMenu.h"
#include "user/userInfoMenu.h"
#include "admin/paymentHistory.h"
#include "admin/adminMenu.h"
#include "admin/statusMenu.h"
#include "admin/reportMenu.h"

using namespace std;

void reportMenu() {
    cout << "===================================================\n";
    cout << "                   USER REPORT                    \n";
    cout << "===================================================\n";
    cout << "User Name: " << "John Doe" << endl;
    cout << "User ID: " << "123456" << endl;    
    cout << "Faculty: " << "Engineering" << endl;
    cout << "Monthly Pass Status: " << "Approved" << endl;
    cout << "Payment History: " << endl;
    cout << "Date: " << "01/01/2024" << " | Amount Paid: RM 31.80" << endl;
    cout << "===================================================\n";
    cout << "| (1) Back to admin menu                          |\n";
    cout << "===================================================\n";
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice; 
    switch (choice) {
        case 1:
            system("cls");
            adminMenu();
            break;
        default:
            cout << "Invalid input, try again.\n";
            reportMenu();
            break;
    }
}
