#ifndef USER_INFO_H
#define USER_INFO_H

#include <string>
using namespace std;

struct User{
    string name = "";
    string studentId = "";
    string ic = "";
    string contact = "";
    string faculty = "";
    string carPlate = "";

    void userInfo();
    void editInfo();
};

#endif