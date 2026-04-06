#ifndef	MAIN_MENU_H
#define MAIN_MENU_H
#include <vector>
#include "user/userInfoMenu.h"

void mainMenu();
<<<<<<< HEAD
void createNewUser(vector<User> &users);
bool isUserExist(string newUser, vector<User> users);
=======
void createNewUser(vector<User> users);
void clearBuffer();
bool isUserPassExist(string newUser, vector<User> users);
>>>>>>> parent of 42a0cc8 (Modify alot of files, fixes: mainMenu, userinfo, creates: globals.h)
bool containInvalidChar(string username);

#endif