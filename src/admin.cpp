#include "system.h"

#include <limits>
#include <cstdlib>

using namespace std;

//function to display the admin menu
void adminMenu() {
    while (true) {
        cout << "===========================================\n";
        cout << "                ADMIN MENU                 \n";
        cout << "===========================================\n";

        cout << "===========================================\n";
        cout << "|(1) view user payment history            |\n";
        cout << "|(2) view user monthly pass status        |\n";
        cout << "|(3) view user report                     |\n";
        cout << "|(4) exit program                         |\n";
        cout << "===========================================\n";

        cout << "Choose an action: ";
        int choice = 0;
        if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        system("cls");
        switch (choice) {
            case 1:
                paymentHistoryMenu();
                break;
            case 2:
                statusMenu();
                break;
            case 3:               
                reportMenu();
                break;
            case 4:
                system("cls");
                cout << "Bye!\n";
                break;
            default:
                cout << "Invalid input, try again.\n";
                continue;
        }
    break;
    }
}

int loadPayments(Payment payment[]) {
    int count = 0;
    

    ifstream fin(Settings::FILE_PATH.c_str());
    if (!fin) {
        cout << "File not found!\n";
        return count;
    }

    string line;
    getline(fin, line); 

    while (getline(fin, line)) {
        if (count >= Settings::MAX_PAYMENTS) {
            cout << "Already hit maximum payment, stopping loading...\n";
            break;
        }

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

        if (!paymentAmountStr.empty()) {
            p.amount = atof(paymentAmountStr.c_str());
        }
        else {
            p.amount = 0.0f;
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

        payment[count] = p;
        count++;
    }

    fin.close();
    return count;
}

void paymentHistoryMenu() {
    Payment payment[Settings::MAX_PAYMENTS];
    int paymentCount = loadPayments(payment);

    while (true) {
        cout << "===========================================================\n";
        cout << "|                      PAYMENT HISTORY                    |\n";
        cout << "===========================================================\n";
        cout << "|  No.  | User ID    | Amount Paid | Date                 |\n";
        cout << "===========================================================\n";

        bool noKeyFound = (paymentCount == 0);
        if (noKeyFound) {
            cout << "There are no payment history to review.\n";
        }

        for (int i = 0; i < paymentCount; i++) {
            cout << "| " << setw(3) << i+1<< "   | " << setw(10) << payment[i].studentId << " | RM " 
            << setw(8) << fixed << setprecision(2) << payment[i].amount<< "  | " << setw(19) 
            << payment[i].date << " |\n";
        }

        cout << "===========================================================\n";
        cout << "| (1) View payment details                                |\n";
        cout << "| (2) Back to admin menu                                  |\n";
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

    if (no >= 1 && no <= paymentCount) {
        Payment &p = payment[no - 1];

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

    } else { 
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

//assign month name for number digits
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
    return atof(mm.c_str());
}

int extractYear(const string &date) {
    if (date == "-" || date.size() < 4) return -1;
    return atof(date.substr(0, 4).c_str());
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
        cout << "|(4) CFS                                            |\n";
        cout << "|(5) ICS                                            |\n";
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
            string faculties[] = {"FAM","FMHS","FCI","CFS","ICS","LKCFES"};
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
            matchesFilter = (extractMonth(dateApplied) == atof(filterValue.c_str()));
        }
        else if (filterType == "year") 
        {
            matchesFilter = (extractYear(dateApplied) == atof(filterValue.c_str()));
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

void reportMenu(int selectedMonth) {
    printReport(getMonthName(selectedMonth), "month", toString(selectedMonth));
    
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
    printReport(toString(selectedYear), "year", toString(selectedYear));

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

void reportMenu() {
    selectReport();
}

string datetime() {
    time_t now = time(0);
    tm *t = localtime(&now);
    char buf[32];
    sprintf(buf, "%04d-%02d-%02d_%02d:%02d:%02d",
        1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
    return string(buf);;
}

void statusMenu() {
    User user;
    const char* tempFileName = "temp.txt";
    ifstream fin(Settings::FILE_PATH.c_str());

    if(!fin.is_open()){
        cerr << "Error opening file.\n";
        return;
    }
    
    const int MAX_INFO = 12;
    string userInfo[Settings::MAX_USERS][MAX_INFO];
    int foundSubIndex[Settings::MAX_USERS];
    
    int userCount = 0;
    string info;

    // Read the file once
    while(getline(fin, info) && userCount < Settings::MAX_USERS){
        string line;
        stringstream ss(info);
        int col = 0;

        // BUG FIX 1: Changed ' ' to ',' to properly parse CSV format
        while(getline(ss, line, ',') && col < MAX_INFO) {
            userInfo[userCount][col] = line;
            col++;
        }
        userCount++;
    }
    fin.close();

    int username_col = 0;
    int password_col = 1;
    int name_col = 2;
    int sID_col = 3;
    int ic_col = 4;
    int contact_col = 5;
    int faculty_col = 6;
    int carPlate_col = 7;
    int subStat_col = 8;
    int payAmount_col = 9;
    int payStatus_col = 10;
    int passStat_col = 11;

    while(true){
        // This ensures the menu instantly updates when a pass is approved/rejected
        int foundSubCount = 0;
        for (int i = 1; i < userCount; i++) { 
            string submission = userInfo[i][subStat_col];
            // Check for "Submitted_" or "1" 
            if(submission.find("Submitted_") != string::npos || submission == "1") {
                foundSubIndex[foundSubCount] = i;
                foundSubCount++;
            }
        }

        cout << "==============================================================================\n";
        cout << "| No  | File Index | User ID   |   Time   |    Date    | Monthly Pass Status |\n";
        cout << "==============================================================================\n";

        if (foundSubCount == 0) {
            cout << "| There are no pending submissions to review.                                |\n";
        } else {
            for(int i = 0; i < foundSubCount; i++) {
                int actualIndex = foundSubIndex[i];
                string submission = userInfo[actualIndex][subStat_col];
                
                string date = "N/A";
                string time = "N/A";

                // Safe substring extraction to prevent out_of_range crash
                if (submission.length() > 10 && submission.find("Submitted_") != string::npos) {
                    string temp = submission.substr(10);
                    if (temp.length() >= 10) date = temp.substr(0, 10);
                    if (temp.length() >= 19) time = temp.substr(11, 8);
                }

                string status = userInfo[actualIndex][passStat_col];
                size_t pos = status.find('_');
                if(pos != string::npos){
                    status = status.substr(0, pos);
                }  
                
                cout << "| " << left << setw(3) << (i + 1) << " "
                     << "| " << setw(10) << actualIndex << " "
                     << "| " << setw(10) << userInfo[actualIndex][sID_col]
                     << "| " << setw(8) << time << " "
                     << "| " << setw(10) << date << " "
                     << "| " << setw(19) << status << " |\n"; 
            }
        }
        
        cout << "==============================================================================\n";
        cout << "|(1) Approve monthly pass                                                    |\n" ;
        cout << "|(2) Reject monthly pass                                                     |\n";   
        cout << "|(3) Back to admin menu                                                      |\n";
        cout << "==============================================================================\n";

        cout << "Enter your choice: ";
        
        string reason;
        int choice = 0, Findex = 0;
        
        if (!(cin >> choice)) {
            clearBuffer();
            choice = 0;
        }

        if (choice == 3) {
            system("cls");
            adminMenu();
            break;
        }

        if (choice == 1 || choice == 2) {
            cout << "Enter user file index number to " << (choice == 1 ? "approve" : "reject") << ": ";
            if (!(cin >> Findex)) {
                clearBuffer();
                cout << "Invalid input.\n";
                system("pause");
                system("cls");
                continue;
            }

            // Verify the entered index is actually one of our pending submissions
            bool isValidIndex = false;
            for (int i = 0; i < foundSubCount; i++) {
                if (foundSubIndex[i] == Findex) {
                    isValidIndex = true;
                    break;
                }
            }

            if (!isValidIndex) {
                system("cls");
                cout << "Invalid user index file number, please try again.\n";
                continue;
            }

            // Process the Approval or Rejection
            if (choice == 1) {
                userInfo[Findex][subStat_col] = "Approved_" + datetime();
                cout << "Monthly pass approved for user:\n";
            } else {
                int reasonChoice = 0;
                string reasonCode = "0";

                while(true) {
                    cout << "Select a reason for rejection:\n";
                    cout << "  (1) Maximum capacity reached. No additional parking slots available.\n";
                    cout << "  (2) Information mismatch (eg: IC/ID does not match)\n";
                    cout << "  (3) Car plate already registered to an active pass\n";
                    cout << "  (4) Outstanding MPKJ fines\n";
                    cout << "Reason choice: ";
                    
                    if (!(cin >> reasonChoice) || reasonChoice < 1 || reasonChoice > 4) {
                        clearBuffer();
                        cout << "Invalid choice. Please select 1-4.\n";
                        continue;
                    }
                    break;
                }

                // Convert the choice into a string code (e.g., "1", "2")
                reasonCode = toString(reasonChoice);

                // Pack the NUMBER into the submissionStatus 
                // Result looks like: Rejected_2026-04-17_19:26:49|2
                userInfo[Findex][subStat_col] = "Rejected_" + datetime() + "|" + reasonCode;
            }

            cout << "==============================================================================\n";
            cout << setw(77) << left << ("|User ID: " + userInfo[Findex][sID_col]) << "|" << '\n';
            cout << setw(77) << left << ("|Date and Time: " + datetime()) << "|" << '\n';
            cout << setw(77) << left << ("|Status: " + string(choice == 1 ? "Approved" : "Rejected")) << "|" << '\n';
            cout << "==============================================================================\n";

            // Save to File
            ofstream fout(tempFileName, ios::trunc);
            if (!fout.is_open()) {
                system("cls");
                cerr << "Error opening temporary file.\n";
                continue;
            }
            
            fout << "username,password,name,studentID,ICNo,contact,faculty,carPlate,"
                 << "submissionStatus,paymentAmount,paymentStatus,PassStatus\n";

            // Rejection block was using foundSubCount instead of userCount!
            for(int i = 1; i < userCount; i++){
                fout << userInfo[i][username_col] << ","
                     << userInfo[i][password_col] << ","
                     << userInfo[i][name_col] << ","
                     << userInfo[i][sID_col] << ","
                     << userInfo[i][ic_col] << ","
                     << userInfo[i][contact_col] << ","
                     << userInfo[i][faculty_col] << ","
                     << userInfo[i][carPlate_col] << ","
                     << userInfo[i][subStat_col] << ","
                     << userInfo[i][payAmount_col] << ","
                     << userInfo[i][payStatus_col] << ","
                     << userInfo[i][passStat_col] << "\n"; // Removed extra comma at the end
            }
            fout.close();

            ifstream tempIn(tempFileName);
            ofstream dataOut(Settings::FILE_PATH.c_str(), ios::trunc);
            
            if (tempIn.is_open() && dataOut.is_open()) {
                string line;
                while (getline(tempIn, line)) {
                    dataOut << line << '\n';
                }
                tempIn.close();
                dataOut.close();
                remove(tempFileName);
            } else {
                system("cls");
                cerr << "Error updating data file.\n";
                tempIn.close();
                dataOut.close();
                continue;
            }
            
            system("pause");
            system("cls");
        } else {
            system("cls");
            cout << "Invalid choice. Please try again.\n";
        }
    }        
}