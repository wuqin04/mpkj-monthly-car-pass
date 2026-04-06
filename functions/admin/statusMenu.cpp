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
    /*string reason;
    PassStatus ps[100]; 
    int n = 0;

    ifstream fin("passStatus.txt");
    while (fin >> ps[n].studentId >> ps[n].hour >> ps[n].minute
               >> ps[n].day >> ps[n].month >> ps[n].year >> ps[n].status) {
        n++;
    }
    fin.close();*/
    User user;
    while (true) {
        ifstream fin("data.txt");
        ofstream fout("temp.txt");

        if(!fin.is_open() || !fout.is_open()){
            cerr << "Error opening file.\n";
            return;
        }

        string info;
        vector<string>userInfo;

        getline(fin, info);

        while(getline(fin, info)){
            stringstream ss(info);
            string token;
    
            getline(ss, user.username, ',');
            getline(ss, user.password, ',');
            getline(ss, user.name, ',');
            getline(ss, user.studentId, ',');
            getline(ss, user.icNo, ',');
            getline(ss, user.contact, ',');
            getline(ss, user.faculty, ',');
            getline(ss, user.carPlate, ',');
            getline(ss, user.submissionStatus, ',');

            getline(ss, token, ',');
            user.paymentAmount = stod(token);

            getline(ss, user.passStatus, ',');
            getline(ss, user.username, ',');

            userInfo.push_back(info);
        }

        fin.close();
        
        cout << "================================================================\n";
        cout << "| No | User ID   |   Time   |    Date    | Monthly Pass Status |\n";
        cout << "================================================================\n";

        bool foundSubmission = false;

    do{
        foundSubmission = true;

        if(foundSubmission == true){
            cout << "======================================================";
            cout << "Name: " << user.name << '\n';
            cout << "ID: " << user.studentId << '\n';
            cout << "Car Plate: " << user.carPlate << '\n';
            cout << "Submission Status: " << user.submissionStatus << '\n';
            cout << "======================================================";
        }
        cin.get();
    }while(user.submissionStatus.find("Submitted_") != string::npos);
    break;
    }
}
        /*if()
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
        cout << "|(3) Back to admin menu                                        |\n";
        cout << "================================================================\n";
        cout << "Enter your choice: ";

        int choice, userNo;
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                cout << "Enter user number to approve: ";
                cin >> userNo;
                if (userNo > 0 && userNo <= n) {
                    ps[userNo - 1].status = "Approved";
                    cout << "Monthly pass approved for user " << ps[userNo - 1].studentId << ".\n";
                } else {
                    system("cls");
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
                    system("cls");
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
                return ;
            default:
                cout << "Invalid choice. Please try again.\n";
        }


       
    }
}

ifstream fin("data.txt");
ofstream fout("temp.txt");

if(!fin.is_open() || !fout.is_open()){
    cerr << "Error opening file.\n";
    return;
}

string info;
vector<User>userInfo;

getline(fin, info);

while(getline(fin, info)){
    stringstream ss(info);
    string token;
    
    getline(ss, user.username, ',');
    getline(ss, user.password, ',');
    getline(ss, user.name, ',');
    getline(ss, user.studentId, ',');
    getline(ss, user.icNo, ',');
    getline(ss, user.contact, ',');
    getline(ss, user.faculty, ',');
    getline(ss, user.carPlate, ',');
    getline(ss, user.submissionStatus, ',');

    getline(ss, token, ',');
    user.paymentAmount = stod(token);

    getline(ss, user.passStatus, ',');
    getline(ss, user.username, ',');

    userInfo.push_back(user);
}

fin.close();

bool foundSubmission;

do{
    foundSubmission = true;

    cout << "======================================================";
    cout << "Name: " << user.name '\n';
    cout << "ID: " << user.studentId << '\n';
    cout << "Car Plate: " << user.carPlate << '\n';
    cout << "Submission Status: " << user.submissionStatus << '\n';
    cout << "======================================================";

}while(userInfo.submissionStatus.find("Submitted_") != string::npos);*/
