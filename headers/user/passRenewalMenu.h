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

void getPassStatus();
void infoComplete(User &user);
void passRenewalMenu(User &user);
void passChoice();

#endif