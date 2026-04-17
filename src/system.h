#ifndef SYSTEM_H
#define SYSTEM_H

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <ctime>
#include <cmath>

using namespace std;

// globals
namespace Settings{
    // filepath and admin login criteria are always constant 
    const string FILE_PATH = "data.txt";
    const string ADMIN_LOGIN = "admin";
    const string ADMIN_PASS = "admin";

    // monthly car pass status
    const string INFO_INCOMPLETE = "Info_Not_Complete";
    const string INFO_COMPLETED = "Info_Complete";
    const string APPLIED_PASS = "Pass_Applied";

    // array capacity limits 
    const int MAX_USERS = 200;
    const int MAX_PAYMENTS = 200;

    // fixed price for mpkj car pass
    const double MONTHLY_PRICE = 31.80;
    const double SEM_PRICE = (MONTHLY_PRICE * 4) * 95 / 100;

    const string rejectionReason[4] = {
        "Maximum parking slots reached.",
        "Information mismatch.",
        "Car plate is already registered.",
        "Outstanding MPKJ fines detected."
    };
}

// ===============DECLARATION====================
// users parts
struct User{
    string username;
    string password;
    string name;
    string studentId;
    string icNo;
    string contact;
    string faculty;
    string carPlate;
    string submissionStatus;
    double paymentAmount;
    string paymentStatus;
    string passStatus;
};

struct Pass{
    string choice;
    string monthPrice;
    string semPrice;
    string passStatus;
    string applyStatus;
};

void userMenu(User &user, User users[], int count);
void userInfo(User &user, User users[], int count);
void showPaymentBox();
void showRejectionBox(User &user);
void createInfo(User &user);
void editInfo(User &user, User users[], int count);
bool validateStudentID(const string &studentId);
bool validateIC(const string &ic);
bool validateContact(const string &contact);
bool validateFaculty(string &faculty);
bool validateCarPlate(string &carPlate);
bool usernameExist(const string &username, User users[], int count);
bool isDigits(const string &s);
bool findUser(const string &username, User users[], int count, int &index);
void saveAllUsers(User users[], int count);
void clearBuffer();
void viewStatusMenu(User &user, User users[], int count);
void transactionMenu(User &user);
void paymentMenu(User &user, User users[], int count);
void infoComplete(User &user, User users[], int count);
void passRenewalMenu(User &user, User users[], int count);
void passChoice(User &user, User users[], int count);
string parseInternalStatus(const string& rawStatus, const User& user);
bool isLeapYear(int year);
int getDaysInMonth(int year, int month);
string calculateExpiryDate(string submissionStatus, double paymentAmount);

// main parts
void mainMenu();
void updateCount(User &user, User users[], int &count);
void createNewUser(User users[], int count);
void clearBuffer();
bool isUserPassExist(string newUser, User users[], int count);
bool containInvalidChar(string username);

template <typename T>
std::string toString(const T& value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

// ==============END OF DECLARATION===============

// admin parts
struct Payment {
    string studentId;
    string name;
    string IC;
    string contact;
    double amount;
    string date;
    string faculty;
};

void adminMenu();
int loadPayments(Payment payment[]);
void paymentHistoryMenu();
void selectMonth();
void selectYear();
void selectFaculty();
void reportMenu(int selectedMonth);
void reportMenuByYear(int selectedYear);
void reportMenuByFaculty(const string &selectedFaculty);
void printReport(const string &title, const string &filterType, const string &filterValue);
void reportMenu();
string datetime();
void statusMenu();

#endif
