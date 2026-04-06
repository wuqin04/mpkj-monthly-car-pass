#include <iostream>
#include <iomanip>
#include <limits>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/paymentMenu.h"
#include "user/passRenewalMenu.h"
#include <fstream>
#include <sstream>
using namespace std;

void loadPassStatus(Pass &pass, string userId) {
    ifstream fin("data.txt");

	if (!fin) {
    cout << "File not found!\n";
	return;}

    string line;

    
    getline(fin, line);

    while (getline(fin, line)) {
        stringstream ss(line);
        string field;

        string username, password, name, studentID, ICNo;
        string contact, faculty, carPlate, submissionStatus;
        string paymentAmount, paymentStatus, passStatus;

		
        getline(ss, username, ',');
        getline(ss, password, ',');
        getline(ss, name, ',');
        getline(ss, studentID, ',');
        getline(ss, ICNo, ',');
        getline(ss, contact, ',');
        getline(ss, faculty, ',');
        getline(ss, carPlate, ',');
        getline(ss, submissionStatus, ',');
        getline(ss, paymentAmount, ',');
        getline(ss, paymentStatus, ',');
        getline(ss, passStatus, ',');

username.erase(0, username.find_first_not_of(" \t\r\n"));
username.erase(username.find_last_not_of(" \t\r\n") + 1);

userId.erase(0, userId.find_first_not_of(" \t\r\n"));
userId.erase(userId.find_last_not_of(" \t\r\n") + 1);

 if (username == userId) {
    submissionStatus.erase(0, submissionStatus.find_first_not_of(" \t\r\n"));
    submissionStatus.erase(submissionStatus.find_last_not_of(" \t\r\n") + 1);

    pass.applyStatus = submissionStatus;
    break;
}
	
        }fin.close();}
		




void viewStatusMenu(User &user) {
	
	Pass pass;
	loadPassStatus(pass, user.username);

	string statusOnly;

size_t pos = pass.applyStatus.find('_');

if (pos != string::npos)
    statusOnly = pass.applyStatus.substr(0, pos);
else
    statusOnly = pass.applyStatus;

	while (true){

		int choice;
		
		cout << "============================================================================\n";
		cout << "|        		     APPLICATION STATUS               	    	   |\n";
		cout << "============================================================================\n";	
		
		
	if (pass.applyStatus.find("Approved") != string::npos) {
    cout << "\nYour application is approved\n";
    cout << "Submission time: " << pass.applyStatus.substr(pass.applyStatus.find('_') + 1) << endl << endl;
	} 
	else if (pass.applyStatus.find("Rejected") != string::npos) {
    cout << "\nyour submission is rejected, pls contact XXX-XXXXXX to know more details.\n";
    cout << "Submission time: " << pass.applyStatus.substr(pass.applyStatus.find('_') + 1) << endl << endl;
	}
	else if (pass.applyStatus.find("Pending") != string::npos || pass.applyStatus.find("Submitted") != string::npos) {
    cout << "\nYour application is still pending for review\n\n";
	}
	else {
    cout << "You have yet to apply for a car pass\n";
	}

		cout << "============================================================================\n";
		
		
	if (statusOnly == "Approved") {
    cout << "|(1) show due payment amount                              |\n";
    cout << "|(2) return to main menu                                  |\n";
	}
	else if (statusOnly == "Rejected") {
    cout << "|(1) show reason for rejection          				   |\n";
    cout << "|(2) reapply for car pass               				   |\n";
    cout << "|(3) return to main menu                 				   |\n";
	}
	else if (statusOnly == "Pending") {
    cout << "|(1) return to main menu                				   |\n";
	}
	else {
    cout << "|(1) apply for car pass                   |\n";
    cout << "|(2) return to main menu                  |\n";
	}
		
		cout << "============================================================================\n";
		cout << "Choose an action: ";
		cin >> choice;

		if (statusOnly == "Approved"){
			switch(choice){
					case 1:
						system("cls");
						paymentMenu(user);
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
		}
		
		else if (statusOnly == "Rejected"){
			switch (choice){
				case 1: {
			system("cls");
    		
    	cout << "=========================================\n";
    	cout << "|  Reason for rejection:                |\n";
    	cout << "|   ---								 |" "\n";
    	cout << "=========================================\n";

    	system("pause");
    	system("cls");
    	continue;
		}
				case 2:
					system("cls");
					passRenewalMenu(user);
					break;
				case 3:
					system("cls");
					userMenu(user);
					break;
				default:
					system("cls");
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input, please try again.\n";
					continue;
			}
		}
		
		else if (statusOnly == "Pending"){
			switch (choice){
				case 1:
					system("cls");
					userMenu(user);
					break;

			default:
					system("cls");
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Invalid input, please try again.\n";
					continue;
			}
		}
	

		else {
			switch(choice){
				case 1:
					system("cls");
					passRenewalMenu(user);
					break;
				case 2:
					system("cls");
					userMenu(user);
					break;
				default:
						system("cls");
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Invalid input, please try again.\n";
						continue;
			}
		}
		break;
	}
}	
	
