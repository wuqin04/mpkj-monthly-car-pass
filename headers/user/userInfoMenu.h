#ifndef USER_INFO_H
#define USER_INFO_H

#include <string>
#include <vector>
using namespace std;

struct User{
    string username = "";
    string password = "";
    string name = "";
    string studentId = "";
    string icNo = "";
    string contact = "";
    string faculty = "";
    string carPlate = "";
    string submissionStatus = "";
    double paymentAmount = 0.0;
    string paymentStatus = "";
    string passStatus = "";
};

void userInfo(User &user, vector<User> &users);
void createInfo(User &user);
void editInfo(User &user, vector<User> &users);
bool validateStudentID(const string &studentId);
bool validateIC(const string &ic);
bool validateContact(const string &contact);
bool validateFaculty(string &faculty);
bool validateCarPlate(string &carPlate);
bool usernameExist(const string &username, vector<User> &users);
bool isDigits(const string &s);
void saveAllUsers(vector<User> &users);
void clearBuffer();

#endif