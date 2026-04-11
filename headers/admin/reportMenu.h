#ifndef REPORT_MENU_H
#define REPORT_MENU_H

#include <string>
using namespace std;

void extractStatusDate(const string& input, string& status, string& date);
string getMonthName(int month);
int extractMonth(const string &date);
int extractYear(const string &date);
void selectReport();
void selectMonth();
void selectYear();
void selectFaculty();
string getPassKeyword(const string &passStatus);
void reportMenu(int selectedMonth);
void reportMenuByYear(int selectedYear);
void reportMenuByFaculty(const string &selectedFaculty);
void printReport(const string &title, const string &filterType, const string &filterValue);

#endif