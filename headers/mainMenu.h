#ifndef	MAIN_MENU_H
#define MAIN_MENU_H
#include <vector>
#include "user/userInfoMenu.h"

void mainMenu();
void createNewUser(vector<User> users);
void clearBuffer();
bool isUserPassExist(string newUser, vector<User> users);
bool containInvalidChar(string username);

#endif