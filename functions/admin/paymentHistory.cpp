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

        try {
            p.amount = stod(paymentAmountStr);
        } catch (...) {
            p.amount = 0.0;
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
            string inputId;
            cout << "Enter User ID to view payment history: ";
            cin >> inputId;

            bool found = false;
            for (auto &p : payments) {
                if (p.studentId == inputId) {
                    found = true;
                    system("cls");
                    cout << "===========================================================\n";
                    cout << "| User ID : " << p.studentId << endl;
                    cout << "| Amount  : RM " << fixed << setprecision(2) << p.amount << endl;
                    cout << "| Date    : " << p.date << endl;
                    cout << "| Faculty : " << p.faculty << endl;
                    cout << "===========================================================\n";
                    cout << "| (1) Back to payment history menu                      |\n";
                    cout << "===========================================================\n";
                    int subChoice;
                    cout << "Choose an option: ";
                    while(true){
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
                }}
            }

            if (!found) {
                system("cls");
                cout << "User ID not found.\n";
            }

        } else if (choice == 2) {
            system("cls");
            adminMenu();
            return;
        } else {
            cout << "Invalid input, try again.\n";
        }
    }
}
