#include <iostream>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <string>
#include "admin/adminMenu.h"
#include "user/userInfoMenu.h"
#include "admin/paymentHistory.h"
#include "admin/adminMenu.h"
#include "admin/statusMenu.h"
#include "admin/reportMenu.h"

using namespace std;

void extractStatusDate(string input, string &status, string &date) {
    if (input == "-" || input.empty()) {
        status = "-";
        date = "-";
        return;
    }
    stringstream ss(input);  
        getline(ss, status, '_');  
        getline(ss, date, '_');
}

void reportMenu() {

    ifstream file("data.txt");
    string line;

    cout << "=============================================================================================================================================================================================================================\n";
    cout << "|                                                                              MONTHLY REPORT                                                                                                                               |\n";
    cout << "=============================================================================================================================================================================================================================\n";
    cout << "|          Name             |     Student ID       |     Faculty     |   Car Plate   |     Submission Status    |      Date Applied     |    Pass Status    |   Payment Status  |  Payment Amount(RM) |      Date Issued    |\n";
    cout << "|---------------------------|----------------------|-----------------|---------------|--------------------------|-----------------------|-------------------|-------------------|---------------------|---------------------|\n";

    getline(file, line);

    while (getline(file, line)) {
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
        getline(ss, passStatus, ',');

        string subStatus, dateApplied;
        string payStatus, dateIssued;

        extractStatusDate(submissionStatus, subStatus, dateApplied);
        extractStatusDate(paymentStatus, payStatus, dateIssued);


    cout << "| "
             << setw(7)  << left << studentID << " | "
             << setw(30) << left << name << " | "
             << setw(15) << left << faculty << " | "
             << setw(13) << left << carPlate << " | "
             << setw(20) << left << subStatus << " | "
             << setw(21) << left << dateApplied << " | "  
             << setw(17) << left << passStatus << " | "
             << setw(17) << left << payStatus << " | "
             << setw(10) << left << paymentAmount << " | "
             << setw(12) << left << dateIssued << " | "   
             << endl;
    cout << "=============================================================================================================================================================================================================================\n";
    
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
            cout << "Report printed successfully.\n";
            system("cls");
            break;
        case 2:
            system("cls");
            adminMenu();
            break;
        default:
            cout << "Invalid input, try again.\n";
            reportMenu();
            break;
    }
}
}