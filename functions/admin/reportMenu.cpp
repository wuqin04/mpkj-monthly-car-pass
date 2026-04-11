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

//extract date from data.txt
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

//asign month name for number digits
string getMonthName(int month) {
    const string months[] = {"January", "February", "March", "April", "May", "June",
                             "July", "August", "September", "October", "November", "December"};
    if (month < 1 || month > 12) return "Unknown";
    return months[month - 1];
}

//getting month from extracted date
int extractMonth(const string &date) {
    if (date == "-" || date.size() < 7) return -1;
    string mm = date.substr(5, 2);
    return stoi(mm);
}

int extractYear(const string &date) {
    if (date == "-" || date.size() < 4) return -1;
    return stoi(date.substr(0, 4));
}

void selectReport() { 
        cout << "====================================================\n";
        cout << "|                  Report Selection                |\n";
        cout << "====================================================\n";
        cout << "|Please select the type of report you want to view.|\n";
        cout << "|(1) Monthly Report                                |\n";
        cout << "|(2) Yearly Report                                 |\n";
        cout << "|(3) Faculty Report                                |\n";
        cout << "====================================================\n";
        cout << "Choose a report type: ";
        int reportChoice = 0;
        if (!(cin >> reportChoice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore();

        switch (reportChoice) {
            case 1:
                system("cls");
                selectMonth();
                break;
            case 2:
                system("cls");
                selectYear();
                break;
            case 3:
                system("cls");
                selectFaculty();
                break;
            default:
                cout << "Invalid input, try again.\n";
        }
    }

void selectYear() {
    while (true){
        cout << "====================================================\n";
        cout << "|                  YEARLY REPORT                   |\n";
        cout << "====================================================\n";
        cout << "|Enter the year for which you want to view report  |\n";
        cout << "|(1) 2025                                          |\n";
        cout << "|(2) 2026                                          |\n";
        cout << "|(0) Back to admin menu                            |\n";
        cout << "====================================================\n";
        cout << "Choose a year: ";
        int yearChoice = 0;
        if (!(cin >> yearChoice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        system("cls");
        if (yearChoice == 0) {
            adminMenu();
            break;
        } else if (yearChoice == 1) {
            system("cls");
            reportMenuByYear(2025);
            break;
        } else if (yearChoice == 2) {
            system("cls");
            reportMenuByYear(2026);
             break;
        } else {
            cout << "Invalid input, try again.\n";
        }
    }
}

void selectFaculty() {
    while (true){
        cout << "=====================================================\n";
        cout << "|                  FACULTY REPORT                   |\n";
        cout << "=====================================================\n";
        cout << "|Enter the faculty for which you want to view report|\n";
        cout << "|(1) FAM                                            |\n";
        cout << "|(2) FMHS                                           |\n";
        cout << "|(3) FCI                                            |\n";
        cout << "|(4) FEGT                                           |\n";
        cout << "|(5) FICT                                           |\n";
        cout << "|(6) LKC FES                                        |\n";
        cout << "|(0) Back to admin menu                             |\n";
        cout << "=====================================================\n";
        cout << "Choose a faculty: ";
        int facultyChoice = 0;
        if (!(cin >> facultyChoice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore();
        system("cls");
        if (facultyChoice == 0) {
            adminMenu();
            break;
        } else if (facultyChoice >= 1 && facultyChoice <= 6) {
            string faculties[] = {"FAM","FMHS","FCI","FEGT","FICT","LKC FES"};
            reportMenuByFaculty(faculties[facultyChoice - 1]);
            break;
        } else {
            cout << "Invalid input, try again.\n";
        }
    }
}

//navigation menu before listing monthly report
void selectMonth() { 
    while (true) { 
        cout << "====================================================\n";
        cout << "|                  MONTHLY REPORT                  |\n";
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

//function to identify pass statuss
string getPassKeyword(const string &passStatus) {
    if (passStatus == "-") return "-";
    string keyword = passStatus.substr(0, passStatus.find('_'));
    if (keyword == "Expired") return "Expired"; 
    return keyword; 
}

//monthly report menu
void printReport(const string &title, const string &filterType, const string &filterValue) {

    //if no data.txt, it can,t open the monthly report
    ifstream file("data.txt");
    if (!file.is_open()) {
        cout << "Error: Cannot open data.txt\n";
        return;
    }
    string line;

    cout << "=================================================================================================================================================================================================\n";
    cout << "|" << setw(97) << right << (title + " REPORT") << setw(96) << right << "|\n";
    cout << "=================================================================================================================================================================================================\n";
    cout << "|  Student ID  |            Name              |     Faculty     |   Car Plate   |   Sub Status   |    Date Applied    |     Pass Status    |  Payment Status  | Amount(RM) |     Date Issued    |\n";
    cout << "|--------------|------------------------------|-----------------|---------------|----------------|--------------------|--------------------|------------------|------------|--------------------|\n";   
    getline(file, line);

    //skip the first header from the data.txt
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string temp;

        //define the strings showing in the report
        string name, studentID, faculty, carPlate;
        string submissionStatus, paymentAmount, paymentStatus, passStatus;

        //skip username and password coloumn
        getline(ss, temp, ',');
        getline(ss, temp, ',');

        getline(ss, name, ',');
        getline(ss, studentID, ',');

        //skip IcNo and contact
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

        //getting dates from submissionStatus and paymentStatus and print in to the selected coloumn
        extractStatusDate(submissionStatus, subStatus, dateApplied);
        extractStatusDate(paymentStatus, payStatus, dateIssued);

        bool matchesFilter = false;
        if (filterType == "month") 
        {
            matchesFilter = (extractMonth(dateApplied) == stoi(filterValue));
        }
        else if (filterType == "year") 
        {
            matchesFilter = (extractYear(dateApplied) == stoi(filterValue));
        }
        else if (filterType == "faculty") 
        {
            matchesFilter = (faculty == filterValue);
        }
        if (!matchesFilter) continue;

        //set width for the data to align the table
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

}

// REPLACED: reportMenu(int selectedMonth)
void reportMenu(int selectedMonth) {
    printReport(getMonthName(selectedMonth), "month", to_string(selectedMonth));
    
    cout << "=========================================================================================\n";
    cout << "| (1) Print Report                                                                      |\n";
    cout << "| (2) Back to admin menu                                                                |\n";
    cout << "| (3) Back to report selection menu                                                     |\n";
    cout << "=========================================================================================\n";
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice; cin.ignore();
    switch (choice) {
        case 1: system("cls"); cout << "Report printed successfully.\n"; reportMenu(selectedMonth);
            break;
        case 2: system("cls"); adminMenu();
            break;
        case 3: system("cls"); selectReport();
            break;
        default: 
            cout << "Invalid input, try again.\n"; reportMenu(selectedMonth); break;
    }
}

void reportMenuByYear(int selectedYear) {
    printReport(to_string(selectedYear), "year", to_string(selectedYear));

    cout << "=========================================================================================\n";
    cout << "| (1) Print Report                                                                      |\n";
    cout << "| (2) Back to admin menu                                                                |\n";
    cout << "| (3) Back to report selection menu                                                     |\n";  
    cout << "=========================================================================================\n";
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice; cin.ignore();
    switch (choice) {
        case 1: 
        system("cls"); cout << "Report printed successfully.\n"; reportMenuByYear(selectedYear);
            break;
        case 2: system("cls"); adminMenu();
            break;
        case 3: system("cls"); selectReport();
            break; 
        default: 
            cout << "Invalid input, try again.\n"; reportMenuByYear(selectedYear); break;
    }
}

void reportMenuByFaculty(const string &selectedFaculty) {
    printReport(selectedFaculty, "faculty", selectedFaculty);

    cout << "=========================================================================================\n";
    cout << "| (1) Print Report                                                                      |\n";
    cout << "| (2) Back to admin menu                                                                |\n";
    cout << "| (3) Back to report selection menu                                                     |\n";
    cout << "=========================================================================================\n";
    int choice = 0;
    cout << "Choose an option: ";
    cin >> choice; cin.ignore();
    switch (choice) {
        case 1: system("cls"); cout << "Report printed successfully.\n"; reportMenuByFaculty(selectedFaculty); 
            break;
        case 2: system("cls"); adminMenu();
            break;
        case 3: system("cls"); selectReport();
            break;
        default: 
            cout << "Invalid input, try again.\n"; reportMenuByFaculty(selectedFaculty); break;
    }
}