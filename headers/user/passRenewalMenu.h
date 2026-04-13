#ifndef PASSRENEWALMENU_H
#define PASSRENEWALMENU_H

#include <string>
using namespace std;

struct Pass{
    string choice = "";
    string monthPrice = "";
    string semPrice = "";
    string passStatus;
    string applyStatus;
};
struct UserRecord;
void getPassStatus();
void infoComplete(User &user, UserRecord users[], int count, int index);
void passRenewalMenu(User &user);
void passChoice();

#endif