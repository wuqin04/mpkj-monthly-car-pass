#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cctype>
#include <algorithm>
#include <cstdio>

#include "user/userInfoMenu.h"
#include "user/userMenu.h"
using namespace std;

//function to define a complete user information
void userInfo(User &user, vector<User> &users){
    bool infoComplete = (this->name != "" && this->studentId != "" && this->icNo != "" && this->contact != "" && this->faculty != "" && this->carPlate != "");
    
    while(true){
        if(!infoComplete){
            createInfo(user);
        }

        int choice;
	    cout << "===========================================\n";
        cout << "|             PERSONAL DETAILS            |\n";
        cout << "===========================================\n";
        
        cout << "Name: " << user.name << endl;
        cout << "Student ID: " << user.studentId << endl;
        cout << "IC: " << user.icNo << endl;
        cout << "Contact Number: " << user.contact << endl;
        cout << "Faculty: " << user.faculty << endl;
        cout << "Car Plate Number: " << user.carPlate << endl;

        cout << "===========================================\n";

        if(!infoComplete){
            cout << "WARNING: PLease update your information!\n";
            cout << "===========================================\n";
        }

        cout << "|(1) edit information                     |\n";
        cout << "|(2) back to main menu                    |\n";
        cout << "===========================================\n";

        
	    
        cout << "Choose an action: ";
        cin >> choice;

        switch(choice){
        case 1:
            system("cls");
            editInfo(user);
            break;
        case 2:
            system("cls");
            userMenu(user);
            break;
        default:
            system("cls");
            cin.clear();
            cin.ignore();
            cout << "Invalid input, please try again.\n";
            continue;
        }
        break;
    }
}

/* the technique we use here is temp file swap.
basically we open original file to read, create new temp file, if any updates we just copy and update
into temp file and remove original then rename temp file*/
void createInfo(User &user) {
    system("cls");
    cout << "===========================================\n";
    cout << "|             PERSONAL DETAILS            |\n";
    cout << "===========================================\n";
    cout << "Your account is newly created, please fill \nin your details\n\n";

    clearBuffer();

    cout << "Enter Full Name: ";
    getline(cin, user.name);

    cout << "Enter Student ID: ";
    getline(cin, user.studentId);

    cout << "Enter IC: ";
    getline(cin, user.icNo);

    cout << "Enter Contact Number: ";
    getline(cin, user.contact);

    cout << "Enter Faculty: ";
    getline(cin, user.faculty);

    cout << "Enter Car Plate Number: ";
    getline(cin, user.carPlate);

    ifstream inFile(Settings::filePath);
    ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "ERROR: Cannot open file,\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string fileUsername;

        getline(ss, fileUsername, ',');

        if (fileUsername == user.username) {
            tempFile << user.username << "," 
                    << user.password << "," 
                    << user.name << "," 
                    << user.studentId << "," 
                    << user.icNo << "," 
                    << user.contact << "," 
                    << user.faculty << "," 
                    << user.carPlate << "," 
                    << user.submissionStatus << "," 
                    << "0.00" << ","
                    << user.paymentStatus << "," 
                    << user.passStatus << "\n";
        }
        else {
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    remove(Settings::filePath.c_str());
    rename("temp.txt", Settings::filePath.c_str());

    cout << "\n===========================================\n";
    cout << "Information successfully saved!\n";
    cout << "Press Enter to continue...";
    cin.get();
}

void editInfo(User &user) {
    while (true){
        int choice;

	    cout << "===========================================\n";
        cout << "|           INFORMATION EDITING           |\n";
        cout << "===========================================\n";

        cout << "Name: " << user.name << endl;
        cout << "Student ID: " << user.studentId << endl;
        cout << "IC: " << user.icNo << endl;
        cout << "Contact Number: " << user.contact << endl;
        cout << "Faculty: " << user.faculty << endl;
        cout << "Car Plate Number: " << user.carPlate << endl;

        cout << "=============================\n";
        cout << "|(1) edit Name              |\n";
        cout << "|(2) edit Student ID        |\n";
        cout << "|(3) edit IC                |\n";
        cout << "|(4) edit Contact Number    |\n";
        cout << "|(5) edit Faculty           |\n";
        cout << "|(6) edit Car Plate Number  |\n";
        cout << "|(7) back to user menu      |\n";        
        cout << "=============================\n";


        cout << "Choose an action: ";
        cin >> choice;
        switch(choice){
            case 1:
                cout << "Enter name: ";
                cin >> user.name;
                system("cls");
                continue;;
            case 2:
                cout << "Enter Student ID: ";
                cin >> user.studentId;
                system("cls");
                continue;
            case 3:
                cout << "Enter IC: ";
                cin >> user.icNo;
                system("cls");
                continue;
            case 4:
                cout << "Enter Contact Number: ";
                cin >> user.contact;
                system("cls");
                continue;
            case 5:
                cout << "Enter Faculty: ";
                cin >> user.faculty;
                system("cls");
                continue;
            case 6 : 
                cout << "Enter Car Plate Number: ";
                cin >> user.carPlate;
                system("cls");
                continue;
            case 7:
                system("cls");
                userMenu(user);
                break;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalide input, please try again.\n";
            continue;
        }
        break;
    }
}

bool validateStudentID(const string &studentId) {
    if (studentId.length() < 7 || studentId.length() > 7) return false;
    if (isDigits(studentId)) return true;

    return false;
}

bool validateIC(const string &ic) {
    regex icPattern(R"(\d{6}-\d{2}-\d{4})");
    return regex_match(ic, icPattern);
}

bool validateContact(const string &contact) {
    regex contactPattern(R"(\d{3}-\d{7,8})");
    return regex_match(contact, contactPattern);
}

bool validateFaculty(string &faculty) {
    transform(faculty.begin(), faculty.end(), faculty.begin(),
        [](unsigned char c) { return toupper(c);});

    if (faculty == "LKC FES" || faculty == "LKCFES" || faculty == "FEGT" || faculty == "FICT" 
        || faculty == "FMHS" || faculty == "FAM" || faculty == "FCI")
        return true;
    return false;
}

bool validateCarPlate(string &carPlate) {
    std::regex pattern("^[A-Z]{1,3}[1-9][0-9]{0,3}[A-Z]{0,2}$");
    return std::regex_match(carPlate, pattern);
}

bool isDigits(const string &s) {
    return !s.empty() && all_of(s.begin(), s.end(), [](unsigned char c) {
        return isdigit(c);
    });
}

bool usernameExist(const string& username, vector<User> &users) {
    for (long long unsigned int i = 0; i < users.size(); i++) {
        if (username == users[i].username) return true;
    }
    return false;
}

void saveAllUsers(vector<User> &users) {
    ofstream outFile(Settings::filePath, ios::trunc);

    if (!outFile.is_open()) {
        cerr << "ERROR: Cannot open file for saving.\n";
        return;
    }

    outFile << "username,password,name,studentID,ICNo,contact,faculty,carPlate,submissionStatus,paymentAmount,paymentStatus,passStatus\n";

    for (long long unsigned int i = 0; i < users.size(); i++) {
        outFile << users[i].username << ","
                << users[i].password << ","
                << users[i].name << ","
                << users[i].studentId << ","
                << users[i].icNo << ","
                << users[i].contact << ","
                << users[i].faculty << ","
                << users[i].carPlate << ","
                << users[i].submissionStatus << ","
                << users[i].paymentAmount << ","
                << users[i].paymentStatus << ","
                << users[i].passStatus << "\n";
    }

    outFile.close();
}

void clearBuffer() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}