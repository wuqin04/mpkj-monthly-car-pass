#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <cctype>
#include <algorithm>
#include <cstdio>
#include <regex>

#include "user/userInfoMenu.h"
#include "user/userMenu.h"
#include "../globals.h"
using namespace std;

void userInfo(User &user, vector<User> &users){    
    while(true){
        int choice;
	    cout << "===========================================\n";
        cout << "|             PERSONAL DETAILS            |\n";
        cout << "===========================================\n";

        cout << "Username: " << user.username << endl;
        cout << "Password: " << user.password << endl;
        cout << "Name: " << user.name << endl;
        cout << "Student ID: " << user.studentId << endl;
        cout << "IC: " << user.icNo << endl;
        cout << "Contact Number: " << user.contact << endl;
        cout << "Faculty: " << user.faculty << endl;
        cout << "Car Plate Number: " << user.carPlate << endl;

        cout << "===========================================\n";
        cout << "|(1) edit information                     |\n";
        cout << "|(2) back to main menu                    |\n";
        cout << "===========================================\n";
        cout << "Choose an action: ";
        cin >> choice;

        switch(choice){
        case 1:
            system("cls");
            editInfo(user, users);
            break;
        case 2:
            system("cls");
            return;
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
    cout << "Your account is newly created, please fill in your details\n\n";

    cout << "Enter Full Name: ";
    getline(cin, user.name);

    while (true) {
        cout << "Enter Student ID (eg:2402954): ";
        getline(cin, user.studentId);
        if (!validateStudentID(user.studentId)) {
            cout << "Invalid student id, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter IC (eg: 060419-02-0081): ";
        getline(cin, user.icNo);
        if (!validateIC(user.icNo)) {
            cout << "Invalid ic number, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }
    
    while (true) {
        cout << "Enter Contact Number (eg: 018-3224189): ";
        getline(cin, user.contact);
        if (!validateContact(user.contact)) {
            cout << "Invalid contact number, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Faculty (eg: LKC FES): ";
        getline(cin, user.faculty);
        if (!validateFaculty(user.faculty)) {
            cout << "Invalid faculty, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Car Plate Number (eg: FB5378): ";
        getline(cin, user.carPlate);
        if (!validateCarPlate(user.carPlate)) {
            cout << "Invalid car plate, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

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

void editInfo(User &user, vector<User> &users) {
    while (true){
        int choice;

	    cout << "===========================================\n";
        cout << "|           INFORMATION EDITING           |\n";
        cout << "===========================================\n";

        cout << "Username: " << user.username << endl;
        cout << "Password: " << user.password << endl;
        cout << "Name: " << user.name << endl;
        cout << "Student ID: " << user.studentId << endl;
        cout << "IC: " << user.icNo << endl;
        cout << "Contact Number: " << user.contact << endl;
        cout << "Faculty: " << user.faculty << endl;
        cout << "Car Plate Number: " << user.carPlate << endl;

        cout << "=============================\n";
        cout << "|(1) edit Username          |\n";
        cout << "|(2) edit Password          |\n";
        cout << "|(3) edit Contact Number    |\n";
        cout << "|(4) edit Faculty           |\n";
        cout << "|(5) edit Car Plate Number  |\n";
        cout << "|(6) back to user menu      |\n";        
        cout << "=============================\n";

        cout << "Choose an action: ";
        cin >> choice;
        switch(choice){
            case 1:
                clearBuffer();
                while (true) {
                    string tempUsername;
                    cout << "Enter New Username: ";
                    getline(cin, tempUsername);
                    if (usernameExist(tempUsername, users)) {
                        cout << "The username already exist, choose a new one. Press enter to continue...";
                        clearBuffer();
                        continue;
                    }

                    user.username = tempUsername;
                    cout << "Username successfully updated!\n";
                    break;
                }   
                break;
            case 2:
                cout << "Enter New Password: ";
                clearBuffer();
                getline(cin, user.password);
                cout << "Your password has changed, press enter to continue.";
                cin.get();
                system("cls");
                break;
            case 3:
                cout << "Enter New Contact Number: ";
                getline(cin, user.contact);
                cout << "Your contact number has changed, press enter to continue.";
                cin.get();
                system("cls");
                break;
            case 4:
                cout << "Enter Faculty: ";
                getline(cin, user.faculty);
                cout << "Your faculty has changed, press enter to continue.";
                cin.get();
                system("cls");
                break;
            case 5 : 
                cout << "Enter Car Plate Number: ";
                getline(cin, user.carPlate);
                cout << "Your car plate has changed, press enter to continue.";
                cin.get();
                system("cls");
                break;
            case 6:
                system("cls");
                return;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalide input, please try again.\n";
                continue;
        }

        saveAllUsers(users);
        
        system("cls");
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