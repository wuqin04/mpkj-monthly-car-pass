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

struct Payment {
    string studentId;
    double amount;
    string date;
    string faculty;
};
void paymentHistory() {
    Payment p[100];
    while(true) {
        int n = 1;
        string inputId;
        
        cout<<"===================================================\n";
        cout<<"                   PAYMENT HISTORY                 \n";
        cout<<"===================================================\n";
        cout<<"===================================================\n";
        cout<<"|  No.  | User ID  | Amount Paid    |    Date     |\n";
        for(int i=0; i<n; i++){
            cout<<"|  "<<fixed<<right<<setw(2)<<i+1
                <<"   |"<<setw(10)<<p[i].studentId
                <<"| RM "<<setw(8)<<fixed<<setprecision(2)<<p[i].amount
                <<"    | "<<setw(12)<<p[i].date<<"|\n"; }

        cout<<"===================================================\n";
        cout<<"| (1) View payment                                |\n";
        cout<<"| (2) Back to admin menu                          |\n";
        cout<<"===================================================\n";
        int choice;
        cout << "Choose an option: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1: {
                cout << "Enter User ID to view payment history: ";
                cin >> inputId;
                bool found = false;
                for (int i = 0; i < n; i++) {
                if (p[i].studentId == inputId) {
                found = true;
                break;}
                }

                if (!found) {
                cout << "User ID not found. Please try again.\n";
                continue;}
                
                cout << "=================================================\n";
                cout << "| User ID : " << p[0].studentId << endl;
                cout << "| Amount  : RM " << fixed << setprecision(4) << p[0].amount << endl;
                cout << "| Date    : " << p[0].date << endl;
                cout << "| Faculty : " << p[0].faculty << endl;
                cout << "=================================================\n";
                continue;

                break;
            }    
            case 2:
                system("cls");
                adminMenu();
                return ;
            default:
                cout << "Invalid input, try again.\n";
                continue;
                
        }break;
        }
        }
