#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "user/userMenu.h"
#include "user/userInfoMenu.h"
#include "user/viewStatusMenu.h"
#include "user/passRenewalMenu.h"
using namespace std;

const string INFO_INCOMPLETE = "0";
const string INFO_COMPLETED = "1";
const string APPLIED_PASS = "2";

Pass pass;

//define the header from the data.txt
struct UserRecord {
    string username, password, name, studentId, icNo, contact, faculty, carPlate;
    string submissionStatus, paymentAmount, paymentStatus, passStatus;
};

//getting month from extracted date
void extractStatusDate(string input, string &status, string &date) {
    if (input == "-" || input.empty()) {
        status = "-";
        date = "-";
        return;
    }
    stringstream ss(input);  
        getline(ss, status, '_');  
        getline(ss, date, '_');
}

//gettig current timestamp for submission status
string getCurrentTimeStamp() {
    time_t now = time(0);
    tm *t = localtime(&now);
    char buf[32];
    sprintf(buf, "%04d-%02d-%02d_%02d:%02d:%02d",
        1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
    return string(buf);;
}

//function to extract keyword from the pass status for printing in the report
string getKeyword(const string &status) {
    size_t pos = status.find('_');
    if (pos == string::npos) return status;
    return status.substr(0, pos);
}

//reading user data from data.txt
int readUserData(UserRecord users[]) {
    ifstream fin("data.txt");
    if (!fin.is_open()) return 0;

    string line;
    getline(fin, line);
    int count = 0;

     while (getline(fin, line) && count < 200) {
        if (line.empty()) continue;
        stringstream ss(line);
        string fields[12];
        int i = 0;
        while (getline(ss, fields[i], ',') && i < 12) i++;
        if (i < 12) continue;

        //order of the headings in data.txt
        users[count].username         = fields[0];
        users[count].password         = fields[1];
        users[count].name             = fields[2];
        users[count].studentId        = fields[3];
        users[count].icNo             = fields[4];
        users[count].contact          = fields[5];
        users[count].faculty          = fields[6];
        users[count].carPlate         = fields[7];
        users[count].submissionStatus = fields[8];
        users[count].paymentAmount    = fields[9];
        users[count].paymentStatus    = fields[10];
        users[count].passStatus       = fields[11];
        count++;
        }
    fin.close ();
    return count;
}

//rewrite user infomation to data.txt after update the pass status and submission status
bool writeAllUsers(UserRecord users[], int count) {
    ofstream fout("data.txt");
    if (!fout.is_open()) return false;

    fout << "username,password,name,studentID,ICNo,contact,faculty,carPlate,"
         << "submissionStatus,paymentAmount,paymentStatus,PassStatus\n";

    for (int i = 0; i < count; i++) {
        fout << users[i].username         << ","
             << users[i].password         << ","
             << users[i].name             << ","
             << users[i].studentId        << ","
             << users[i].icNo             << ","
             << users[i].contact          << ","
             << users[i].faculty          << ","
             << users[i].carPlate         << ","
             << users[i].submissionStatus << ","
             << users[i].paymentAmount    << ","
             << users[i].paymentStatus    << ","
             << users[i].passStatus       << "\n";
    }
    fout.close();
    return true;
}

//function to find the user in the data.txt according to the username
bool findUser(const string &username, UserRecord users[], int count, int &index) {
    for (int i = 0; i < count; i++) {
        if (users[i].username == username) {
            index = i;
            return true;
        }
    }
    return false;
}

//function to identify the infomation of the users whether it is complete or not for the pass application
void getPassStatus(){
	if (pass.passStatus == INFO_INCOMPLETE) 
        cout << "WARNING: Your personal information is not complete.\nPlease update your information." << endl;
    else if (pass.passStatus == INFO_COMPLETED)
        cout << "You are eligible to apply for a monthly car pass." << endl;
    else if (pass.passStatus == APPLIED_PASS)
        cout << "Your application is being processed.\nCheck your application in Status Menu." << endl;
}

//function that define the information is complete or not for the pass application
void infoComplete(User &user){
    if (user.name != "" && user.studentId != "" && user.icNo != "" && user.contact != "" && user.faculty != "" && user.carPlate != "")
        pass.passStatus = INFO_COMPLETED;
    else
        pass.passStatus = INFO_INCOMPLETE;
}

//navigation for the pass application menu
void passChoice(User &user){

    while(true){
        int choice;

        //defining the pass price for monthly and semester and the discount for semester pass
        double monthPrice = 31.80, semPrice = (monthPrice * 4) * 95 / 100;

        cout << "===========================================================\n";
	    cout << "|            MONTHLY PASS APPLICATION CHOICES             |\n";
	    cout << "===========================================================\n";
        cout << "|Choice comparison:                                       |\n";
        cout << "|Monthly                                                  |\n";
        cout << "|  -RM " << monthPrice << "                                               |\n";
        cout << "|  -lasts only for one month                              |\n";
        cout << "|                                                         |\n";
        cout << "|Per semester                                             |\n";
        cout << "|  -RM " << semPrice << "                                             |\n";
        cout << "|  -lasts for 4 months (about a semesters' worth)         |\n";
        cout << "|  -save up to 5% compared to buying monthly for 4 months |\n";
        cout << "===========================================================\n";
	    cout << "|(1) one month                                            |\n";
        cout << "|(2) one semester                                         |\n";
        cout << "|(3) cancel                                               |\n";
        cout << "===========================================================\n";
        cout << "Choose the type of pass you wish to apply: ";
        cin >> choice;

        switch(choice){
            // update the submission status and payment amount in data.txt according to the pass choice
            case 1:
                system("cls");
                pass.choice = "month";
                pass.passStatus = APPLIED_PASS; 
                pass.applyStatus = "3";
                {
                    UserRecord users[200];
                    int count = readUserData(users);
                    int index = -1;
                    if (findUser(user.username, users, count, index)) {
                        users[index].submissionStatus = "Submitted_" + getCurrentTimeStamp() + "_month";
                        users[index].paymentAmount    = "0.00";
                        writeAllUsers(users, count);
                    }
                }
                break;

            case 2:
                system("cls");
                pass.choice = "sem";
                pass.passStatus = APPLIED_PASS; 
                pass.applyStatus = "3";
                {
                    UserRecord users[200];
                    int count = readUserData(users);
                    int index = -1;
                    if (findUser(user.username, users, count, index)) {
                        users[index].submissionStatus = "Submitted_" + getCurrentTimeStamp() + "_sem";
                        users[index].paymentAmount    = "0.00";
                        writeAllUsers(users, count);
                    }
                }
                break;

            case 3:
                system("cls");
                break;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalid input, please try again.\n";
                continue;
        }
    break;
    }
}

void passRenewalMenu(User &user){

    //read user data from data.txt
    ifstream file("data.txt");
    string line, temp;

    infoComplete(user);
	while(true){
		int choice;

        //print the pass application menu according to the pass status of the user
		cout << "=====================================================\n";
		cout << "|              MONTHLY PASS APPLICATION             |\n";
		cout << "=====================================================\n";
        getPassStatus();

		cout << "=====================================================\n";

        if (pass.passStatus != "2"){
		    cout << "|(1) apply for monthly car pass                     |\n";
            cout << "|(2) application status menu                        |\n";
            cout << "|(3) back to main menu                              |\n";
            cout << "=====================================================\n";
		    cout << "Choose an action: ";       
		    cin >> choice;

		    switch(choice){
            case 1:
                system("cls");
                passChoice(user);      
                continue;
            case 2:
                system("cls");
                viewStatusMenu(user);
                break;
            case 3:
                system("cls");
                return;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalid input, please try again.\n";
                continue;
            }
        }

        else if(pass.passStatus == "2"){
            cout << "|(1) application status menu                        |\n";
            cout << "|(2) back to main menu                              |\n";
            cout << "=====================================================\n";
		    cout << "Choose an action: ";       
		    cin >> choice;

		    switch(choice){
            case 1:
                system("cls");
                viewStatusMenu(user);
                break;
            case 2:
                system("cls");
                return;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalid input, please try again.\n";
                continue;
            }
        }
    break;
    }       
}