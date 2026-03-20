#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include "admin/adminMenu.h"
#include "user/userMenu.h"
#include "admin/paymentHistory.h"
using namespace std;

void paymentHistoryMenu() {
    while(true) {
        int n = 1; //
        string name = "user";   //later will be replaced by actual user name from transaction history data
        double transaction_amount = 100.00; //later will be replaced by actual transaction amount from transaction history data
        string date = "2023-10-01";     //later will be replaced by actual transaction date from transaction history data
        cout<<"=================================================\n";
        cout<<"                 PAYMENT HISTORY                 \n";
        cout<<"=================================================\n";
        cout<<"=================================================\n";
        cout<<"|  No. | User ID | Amount Paid    |    Date     |\n";
        for(int i=0; i<n; i++){
        cout<<"| "<<setw(2)<<i+1<<"   | "<<fixed<<left<<setw(8)<<setprecision(2)<<name<<"| RM "<<fixed<<left<<setw(7)<<transaction_amount<<"     | "<<date<<"  |\n";
        }
        cout<<"=================================================\n";
        cout<<"| (1) View payment                              |\n";
        cout<<"| (2) Back to admin menu                        |\n";
        cout<<"=================================================\n";
        int choice;
        cout << "Choose an option: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice) {
            case 1:
                system("cls");
                cout << "Payment view not implemented yet.\n";
                break;      
            case 2:
                system("cls");
                adminMenu();
                system("pause"); 
                return;
            default:
                cout << "Invalid input, try again.\n";
                system("pause");
                break;
        }
    }
}
