#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <string>
#include "admin/adminMenu.h"
using namespace std;

struct Payment {
    string studentId;
    string name;
    string IC;
    string contact;
    double amount;
    string date;
    string faculty;
};


vector<Payment> loadPayments() {
    vector<Payment> payments;
    ifstream fin("data.txt");
    if (!fin) {
        cout << "File not found!\n";
        return payments;
    }

    string line;
    getline(fin, line); 

    while (getline(fin, line)) {
        stringstream ss(line);
        string username, password, name, studentID, ICNo, contact, faculty;
        string carPlate, submissionStatus, paymentAmountStr, paymentStatus, passStatus;

        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, studentID, ',');
        getline(ss, ICNo, ',');
        getline(ss, contact, ',');
        getline(ss, faculty, ',');
        getline(ss, carPlate, ',');
        getline(ss, submissionStatus, ',');
        getline(ss, paymentAmountStr, ',');
        getline(ss, paymentStatus, ',');
        getline(ss, passStatus, ',');

        Payment p;
        p.studentId = studentID;
        p.name = name;
        p.IC = ICNo;
        p.contact = contact;
        p.faculty = faculty;

        try {
            p.amount = stod(paymentAmountStr);
        } catch (...) {
            p.amount = 0.0;
        }
        if (paymentStatus.find("Paid_") == string::npos || p.amount <= 0) {
            continue;
        }
        size_t pos = paymentStatus.find('_');
        if (pos != string::npos && pos + 1 < paymentStatus.size()) {
            p.date = paymentStatus.substr(pos + 1);
        } else {
            p.date = "N/A";
        }

        p.faculty = faculty;

        payments.push_back(p);
    }

    fin.close();
    return payments;
}


void paymentHistoryMenu() {
    vector<Payment> payments = loadPayments();
    if (payments.empty()) return;

    while (true) {
        cout << "===========================================================\n";
        cout << "                       PAYMENT HISTORY                     \n";
        cout << "===========================================================\n";
        cout << "|  No.  | User ID    | Amount Paid | Date                |\n";
        cout << "===========================================================\n";

        for (size_t i = 0; i < payments.size(); i++) {
            cout << "| " << setw(3) << i+1<< "   | " << setw(10) << payments[i].studentId<< " | RM " << setw(8) << fixed << setprecision(2) << payments[i].amount<< " | " << setw(19) << payments[i].date << " |\n";
        }

        cout << "===========================================================\n";
        cout << "| (1) View payment details                                 |\n";
        cout << "| (2) Back to admin menu                                   |\n";
        cout << "===========================================================\n";

        int choice;
        cout << "Choose an option: ";
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        if (choice == 1) {
    int no;
    cout << "Enter No. to view payment details: ";

    if (!(cin >> no)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        continue;
    }

    if (no >= 1 && no <= (int)payments.size()) {
        Payment &p = payments[no - 1];

        system("cls");
        cout << "===========================================================\n";
        cout << "| User ID : " << p.studentId << endl;
        cout << "| Name    : " << p.name << endl;
        cout << "| IC      : " << p.IC << endl;
        cout << "| Contact : " << p.contact << endl;
        cout << "| Faculty : " << p.faculty << endl;
        cout << "| Amount  : RM " << fixed << setprecision(2) << p.amount << endl;
        cout << "| Date    : " << p.date << endl;
        cout << "===========================================================\n";
        cout << "| (1) Back to payment history menu                      |\n";
        cout << "===========================================================\n";

        int subChoice;
        cout << "Choose an option: ";

        while (true) {
            if (!(cin >> subChoice)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (subChoice == 1) {
                system("cls");
                break;
            } else {
                cout << "Invalid input, try again.\n";
                cout << "Choose an option: ";
            }
        }

    } else {   // ✅ 这个 else 属于 if (no...)
        system("cls");
        cout << "Invalid No.\n";
    }
}

         else if (choice == 2) {
            system("cls");
            adminMenu();
            return;
        } else {
            system("cls");
            cout << "Invalid input, try again.\n";
            
        }
    }
}
