#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <chrono>
#include <algorithm>
#include "user/userInfoMenu.h"
#include "admin/adminMenu.h"
#include "user/userInfoMenu.h"

#include <fstream>

using namespace std;

string datetime() {
    time_t now = time(0);
    tm *t = localtime(&now);
    char buf[32];
    sprintf(buf, "%04d-%02d-%02d_%02d:%02d:%02d",
        1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
    return string(buf);;
}

void statusMenu() {

    User user;
    const char* readFileName = "data.txt";
    const char* tempFileName = "temp.txt";
    ifstream fin(readFileName);

    if(!fin.is_open()){
        cerr << "Error opening file.\n";
        return;
    }
    
    vector<int>found_sub_index = {};
    vector<vector<string>>userInfo;
    string info;

    while(getline(fin, info)){
        vector<string>temp;
        string line;
        stringstream ss(info);

        while(getline(ss, line, ',')){
            temp.push_back(line);
        }

        userInfo.push_back(temp);
    }

    fin.close();

    bool run = false;
    bool noKeyFound = found_sub_index.empty();
    int username_col = 0;
    int password_col = 1;
    int name_col = 2;
    int sID_col = 3;
    int ic_col = 4;
    int contact_col = 5;
    int faculty_col = 6;
    int carPlate_col = 7;
    int subStat_col = 8;
    int payAmount_col = 9;
    int payStatus_col = 10;
    int passStat_col = 11;

    while(true){
        cout << "==============================================================================\n";
        cout << "| No  | File Index | User ID   |   Time   |    Date    | Monthly Pass Status |\n";
        cout << "==============================================================================\n";

        int indexT = 1;
        int indexF = 1;

        if(run == true && noKeyFound){
                cout << "There are no pending submissions to review.\n";
        }

        else{
            for(size_t i = 1; i != userInfo.size(); i++){
                string submission = userInfo[i][subStat_col];

                if(submission.find("Submitted_") != string::npos){
                    if(run == false){
                        found_sub_index.push_back(i);   
                        if(i == userInfo.size()){
                            run = true;
                        }
                    }

                    string temp = submission.substr(10);
                    string date = temp.substr(0,10);
                    string time = temp.substr(11,8);

                    string status = userInfo[i][passStat_col];
                    size_t pos = status.find('_');
                    if(pos != string::npos){
                        status = status.substr(0, pos);
                    }
            
                
                    cout << "| " << left << setw(3) << indexT << " "
                         << "| " << setw(10) << indexF << " "
                         << "| " << setw(10) << userInfo[i][sID_col]
                         << "| " << setw(9) << time
                         << "| " << setw(11) << date
                         << "| " << setw(20) << status << "|\n"; 
                
                    indexT++;
                }
                indexF++;
            }
        }
        
        cout << "==============================================================================\n";
        cout << "|(1) Approve monthly pass                                                    |\n" ;
        cout << "|(2) Reject monthly pass                                                     |\n";   
        cout << "|(3) Back to admin menu                                                      |\n";
        cout << "==============================================================================\n";

        cout << "Enter your choice: ";
        
        string reason;

        int choice, Findex;
        cin >> choice;

        switch (choice) {
            case 1:{
                cout << "Enter user file index number to approve: ";
                cin >> Findex;

                auto subFound = find(found_sub_index.begin(), found_sub_index.end(), Findex);
                bool foundSub;
                if(subFound != found_sub_index.end()){
                    foundSub = true;
                    found_sub_index.erase(subFound);
                }

                if (foundSub) {
                    userInfo[Findex][subStat_col] = "Approved_" + datetime();
                    cout << "Monthly pass approved for user:\n";
                    cout << "==============================================================================\n";
                    cout << setw(77) << left << "|User ID: " + userInfo[Findex][sID_col] << right << "|" << '\n';
                    cout << setw(77) << left << "|Date and Time: " + datetime() << right << "|" << '\n';
                    cout << setw(77) << left << "|Status: Approved" << right << "|" << '\n';
                    cout << "==============================================================================\n";
                    ofstream fout(tempFileName, ios::trunc);
                    if (!fout.is_open()) {
                        system("cls");
                        cerr << "Error opening temporary file.\n";
                        continue;
                    }
                    fout << "username,password,name,studentID,ICNo,contact,faculty,carPlate,"
                         << "submissionStatus,paymentAmount,paymentStatus,PassStatus\n";
                    for(size_t i = 1; i != userInfo.size(); i++){
                        fout << userInfo[i][username_col] << ",";
                        fout << userInfo[i][password_col] << ",";
                        fout << userInfo[i][name_col] << ",";
                        fout << userInfo[i][sID_col] << ",";
                        fout << userInfo[i][ic_col] << ",";
                        fout << userInfo[i][contact_col] << ",";
                        fout << userInfo[i][faculty_col] << ",";
                        fout << userInfo[i][carPlate_col] << ",";
                        fout << userInfo[i][subStat_col] << ",";
                        fout << userInfo[i][payAmount_col] << ",";
                        fout << userInfo[i][payStatus_col] << ",";
                        fout << userInfo[i][passStat_col] << "," << '\n';
                    }
                    fout.close();
                    
                    ifstream tempIn(tempFileName);
                    ofstream dataOut(readFileName, ios::trunc);
                    if (tempIn.is_open() && dataOut.is_open()) {
                        string line;
                        while (getline(tempIn, line)) {
                            dataOut << line << '\n';
                        }
                        tempIn.close();
                        dataOut.close();
                        remove(tempFileName);
                    } else {
                        system("cls");
                        cerr << "Error updating file.\n";
                        continue;
                    }
                    system("pause");
                    system("cls");
                    continue;
                }
                else {
                    system("cls");
                    cout << "Invalid user index file number, please try again.\n";
                    cin.clear();            
                    cin.ignore();
                    continue;
                }}
            case 2:{
                cout << "Enter user file index number to reject: ";
                cin >> Findex;

                auto subFound = find(found_sub_index.begin(), found_sub_index.end(), Findex);
                bool foundSub;
                if(subFound != found_sub_index.end()){
                    foundSub = true;
                    found_sub_index.erase(subFound);
                }

                if (foundSub) {
                    userInfo[Findex][subStat_col] = "Rejected_" + datetime();
                    cout << "Enter reason for rejection: ";
                    cin.ignore();
                    getline(cin, reason);
                    cout << "Monthly pass rejected for user:\n";
                    cout << "==============================================================================\n";
                    cout << setw(77) << left << "|User ID: " + userInfo[Findex][sID_col] << right << "|" << '\n';
                    cout << setw(77) << left << "|Date and Time: " + datetime() << right << "|" << '\n';
                    cout << setw(77) << left << "|Status: Rejected" << right << "|" << '\n';
                    cout << setw(77) << left << "|Reason: " + reason << right << "|" << '\n';
                    cout << "==============================================================================\n";
                    ofstream fout(tempFileName, ios::trunc);
                    if (!fout.is_open()) {
                        system("cls");
                        cerr << "Error opening temporary file.\n";
                        continue;
                    }
                    fout << "username,password,name,studentID,ICNo,contact,faculty,carPlate,"
                         << "submissionStatus,paymentAmount,paymentStatus,PassStatus\n";
                    for(size_t i = 1; i != userInfo.size(); i++){
                        fout << userInfo[i][username_col] << ",";
                        fout << userInfo[i][password_col] << ",";
                        fout << userInfo[i][name_col] << ",";
                        fout << userInfo[i][sID_col] << ",";
                        fout << userInfo[i][ic_col] << ",";
                        fout << userInfo[i][contact_col] << ",";
                        fout << userInfo[i][faculty_col] << ",";
                        fout << userInfo[i][carPlate_col] << ",";
                        fout << userInfo[i][subStat_col] << ",";
                        fout << userInfo[i][payAmount_col] << ",";
                        fout << userInfo[i][payStatus_col] << ",";
                        fout << userInfo[i][passStat_col] << "," << '\n';
                    }
                    fout.close();
                    
                    ifstream tempIn(tempFileName);
                    ofstream dataOut(readFileName, ios::trunc);
                    if (tempIn.is_open() && dataOut.is_open()) {
                        string line;
                        while (getline(tempIn, line)) {
                            dataOut << line << '\n';
                        }
                        tempIn.close();
                        dataOut.close();
                        remove(tempFileName);
                    } else {
                        system("cls");
                        cerr << "Error updating file.\n";
                        continue;
                    }
                    system("pause");
                    system("cls");
                    continue;
                } 
                else {
                    system("cls");
                    cout << "Invalid user index file number, please try again.\n";
                    cin.clear();            
                    cin.ignore();
                    continue;
                }}
            case 3:
                system("cls");
                adminMenu();
                break;
            default:
                system("cls");
                cin.clear();
                cin.ignore();
                cout << "Invalid choice. Please try again.\n";
                continue;
        }
        break;
    }        
}