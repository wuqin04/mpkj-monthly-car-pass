#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include <limits>
#include <sstream>
#include "admin/adminMenu.h"
#include "user/userInfoMenu.h"
#include "admin/paymentHistory.h"
#include "admin/adminMenu.h"
#include "admin/statusMenu.h"
#include "admin/reportMenu.h"

using namespace std;

void extractStatusDate(const string& input, string& status, string& date) {
    if (input == "-" || input.empty()) {
        status = "-";
        date = "-";
        return;
    }
    stringstream ss(input);
    getline(ss, status, '_');
    getline(ss, date, '_');
}

string getMonthName(int month) {
    const string months[] = {"January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};
    if (month < 1 || month > 12) return "Unknown";
    return months[month - 1];
}

int extractMonth(const string &date) {
    if (date == "-" || date.size() < 7) return -1;
    string mm = date.substr(5, 2);
    return stoi(mm);
}

void selectMonth() { 
    while (true) { 
        cout << "====================================================\n";
        cout << "|                   REPORT MENU                    |\n";
        cout << "====================================================\n";
        cout << "|Enter the month for which you want to view report |\n";
        cout << "|(1) January                                       |\n";
        cout << "|(2) February                                      |\n";
        cout << "|(3) March                                         |\n";
        cout << "|(4) April                                         |\n";
        cout << "|(5) May                                           |\n";
        cout << "|(6) June                                          |\n";
        cout << "|(7) July                                          |\n";
        cout << "|(8) August                                        |\n";
        cout << "|(9) September                                     |\n";
        cout << "|(10) October                                      |\n";
        cout << "|(11) November                                     |\n";
        cout << "|(12) December                                     |\n";
        cout << "|(0) Back to admin menu                            |\n";
        cout << "====================================================\n";
        cout << "Choose a month: ";
        int monthChoice = 0;   
        if (!(cin >> monthChoice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        system("cls");

        if (monthChoice == 0) {
            adminMenu();
            break;
        } else if (monthChoice >= 1 && monthChoice <= 12) {
            reportMenu(monthChoice);
            break;
        } else {
            cout << "Invalid input, try again.\n";
        }
    }
}

string getPassKeyword(const string &passStatus) {
    if (passStatus == "-") return "-";
    string keyword = passStatus.substr(0, passStatus.find('_'));
    if (keyword == "Expired") return "Expired"; 
    return keyword; 
}

void reportMenu(int selectedMonth) {

    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open data.txt\n";
        return;
    }
    string line;

    string monthName = getMonthName(selectedMonth);
    cout << "=================================================================================================================================================================================================\n";
    cout << "|                                                                                              " << monthName << " REPORT                                                                                     |\n";
    cout << "=================================================================================================================================================================================================\n";
    cout << "|  Student ID  |            Name              |     Faculty     |   Car Plate   |   Sub Status   |    Date Applied    |     Pass Status    |  Payment Status  | Amount(RM) |     Date Issued    |\n";
    cout << "|--------------|------------------------------|-----------------|---------------|----------------|--------------------|--------------------|------------------|------------|--------------------|\n";    
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string temp;

        string name, studentID, faculty, carPlate;
        string submissionStatus, paymentAmount, paymentStatus, passStatus;

        getline(ss, temp, ',');
        getline(ss, temp, ',');

        getline(ss, name, ',');
        getline(ss, studentID, ',');

        getline(ss, temp, ',');
        getline(ss, temp, ',');

        getline(ss, faculty, ',');
        getline(ss, carPlate, ',');
        getline(ss, submissionStatus, ',');
        getline(ss, paymentAmount, ',');
        getline(ss, paymentStatus, ',');
        getline(ss, passStatus);

        string subStatus, dateApplied;
        string payStatus, dateIssued;

        extractStatusDate(submissionStatus, subStatus, dateApplied);
        extractStatusDate(paymentStatus, payStatus, dateIssued);

        int rowMonth = extractMonth(dateApplied);
        if (rowMonth != selectedMonth) continue;

        cout << "| "
             << setw(12)  << left << studentID << " | "
             << setw(28) << left << name << " | "
             << setw(15) << left << faculty << " | "
             << setw(13) << left << carPlate << " | "
             << setw(14) << left << subStatus << " | "
             << setw(18) << left << dateApplied << " | "  
             << setw(18) << left << getPassKeyword(passStatus) << " | "
             << setw(16) << left << payStatus << " | "
             << setw(10) << left << paymentAmount << " | "
             << setw(18) << left << dateIssued << " | "   
             << endl;
    cout << "=================================================================================================================================================================================================\n";
    }

    file.close();

    cout << "=========================================================================================\n";
    cout << "| (1) Print Report                                                                      |\n";
    cout << "| (2) Back to admin menu                                                                |\n";
    cout << "=========================================================================================\n";
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice; 
    switch (choice) {
        case 1:
            system("cls");
            cout << "Report printed successfully.\n";
            reportMenu(selectedMonth);
            break;
        case 2:
            system("cls");
            adminMenu();
            break;
        default:
            cout << "Invalid input, try again.\n";
            reportMenu(selectedMonth);
            break;
    }
}

void reportMenu() {
    selectMonth();
}