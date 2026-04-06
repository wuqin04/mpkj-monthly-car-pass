#ifndef USER_INFO_H
#define USER_INFO_H

#include <string>
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

void userInfo(User &user);
void createInfo(User &user);
void editInfo(User &user);
void clearBuffer();

#endif