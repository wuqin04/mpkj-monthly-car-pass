#include <iostream>
#include <iomanip>
#include <limits>
#include <fstream>
#include <sstream>
#include "user/userMenu.h"

using namespace std;

void transactionMenu(User &user) {
    while (true) {
        int choice = 0;

        cout << "===========================================\n";
        cout << "|          TRANSACTION HISTORY            |\n";
        cout << "===========================================\n";

        ifstream fin("data.txt");
        string line;

        getline(fin, line); // skip header

        bool found = false;

        while (getline(fin, line)) {
            stringstream ss(line);

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
			

            if (username == user.username) {
    	found = true;

    	string paymentOnly = paymentStatus.substr(0, paymentStatus.find('_'));
    	string paymentTime = paymentStatus.substr(paymentStatus.find('_') + 1);

    	string passOnly = passStatus.substr(0, passStatus.find('_'));


    	cout << "Payment Amount : RM " << paymentAmount << endl;
    	cout << "Payment Status : " << paymentOnly << endl;
    	cout << "Payment Time   : " << paymentTime << endl;
    	cout << "Pass Status    : " << passOnly << endl;

    	break;
		}
        }

        fin.close();

        if (!found) {
            cout << "No transaction record found.\n";
        }

        cout << "===========================================\n";
        cout << "|(1) return to main menu                  |\n";
        cout << "===========================================\n";
        cout << "Choose an action: ";

        if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, please try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        system("cls");

        if (choice == 1) {
            return;
        } 
        else {
            cout << "Invalid input, try again.\n";
            continue;
        }
		break;
	}}