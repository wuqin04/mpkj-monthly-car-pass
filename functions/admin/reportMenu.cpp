#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "admin/adminMenu.h"
#include "user/userMenu.h"
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
    cout << "Date: " << "01/01/2024" << " | Amount Paid: RM 31,80" << endl;
    cout << "===================================================\n";
}
