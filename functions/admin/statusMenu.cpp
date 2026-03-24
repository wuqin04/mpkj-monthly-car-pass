#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include "user/userInfoMenu.h"
#include "admin/adminMenu.h"
#include <fstream>

using namespace std;

struct PassStatus {
    string studentId;
    int hour, minute, day, month, year;
    string status;
};

void statusMenu() {
    string reason;
    PassStatus ps[100]; 
    int n = 0;

    ifstream fin("passStatus.txt");
    while (fin >> ps[n].studentId >> ps[n].hour >> ps[n].minute
               >> ps[n].day >> ps[n].month >> ps[n].year >> ps[n].status) {
        n++;
    }
    fin.close();

    while (true) {
        cout << "================================================================\n";
        cout << "| No | User ID   |   Time   |    Date    | Monthly Pass Status |\n";
        cout << "================================================================\n";

        for (int i = 0; i < n; i++) {
            cout << "| " << setw(2) << i+1 
                 << "| " << setw(8) << ps[i].studentId 
                 << "| " << setw(2) << setfill('0') << ps[i].hour << ":" << setw(2) << ps[i].minute << setfill(' ')
                 << "| " << setw(2) << ps[i].day << "/" << setw(2) << ps[i].month << "/" << ps[i].year
                 << "| " << setw(18) << ps[i].status << " |\n";
        }

        cout << "================================================================\n";
        cout << "|(1) Approve monthly pass                                      |\n" ;
        cout << "|(2) Reject monthly pass                                       |\n";   
        cout << "|(3) Exit                                                      |\n";
        cout << "================================================================\n";
        cout << "Enter your choice: ";

        int choice, userNo;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                system("cls");
                cout << "Enter user number to approve: ";
                cin >> userNo;
                if (userNo > 0 && userNo <= n) {
                    ps[userNo - 1].status = "Approved";
                    cout << "Monthly pass approved for user " << ps[userNo - 1].studentId << ".\n";
                } else {
                    cout << "Invalid user number.\n";
                    cin.clear();            
                    cin.ignore(10000, '\n');
                    continue;
                }
        cout<<"===============================================================\n";
        cout<<"|User ID : "<<ps[userNo-1].studentId;
        cout<<"|Time : "<<setw(2)<<setfill('0')<<ps[userNo-1].hour<<":"<<setw(2)<<ps[userNo-1].minute<<setfill(' ');
        cout<<"|Date : "<<setw(2)<<ps[userNo-1].day<<"/"<<setw(2)<<ps[userNo-1].month<<"/"<<ps[userNo-1].year;
        cout<<"|Status : Approved\n";
        cout<<"===============================================================\n";
                break;
            case 2:
                system("cls");
                cout << "Enter user number to reject: ";
                cin >> userNo;
                if (userNo > 0 && userNo <= n) {
                    ps[userNo - 1].status = "Rejected";
                    cout << "Monthly pass rejected for user " << ps[userNo - 1].studentId << ".\n";
                    cout << "Enter reason for rejection: ";
                    
                    cin.ignore();
                    getline(cin, reason);
                 //   ps[userNo - 1].reason = reason;

                } else {
                    cout << "Invalid user number.\n";
                    cin.clear();            
                    cin.ignore(10000, '\n');
                    continue;

                }
        cout<<"===============================================================\n";
        cout<<"|User ID : " <<ps[userNo-1].studentId;
        cout<<"|Time    : " <<setw(2)<<setfill('0')<<ps[userNo-1].hour<<":"<<setw(2)<<ps[userNo-1].minute<<setfill(' ');
        cout<<"|Date    : " <<setw(2)<<ps[userNo-1].day<<"/"<<setw(2)<<ps[userNo-1].month<<"/"<<ps[userNo-1].year;
        cout<<"|Status  : Rejected\n";
        cout<<"|Reason  : " <<reason<<"|\n";
        cout<<"===============================================================\n";
                break;
            case 3:
                system("cls");
                adminMenu();
                system("pause");
                return;
            default:
                cout << "Invalid choice. Please try again.\n";
        }


       
    }
}