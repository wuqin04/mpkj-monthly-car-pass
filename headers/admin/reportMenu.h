#ifndef REPORT_MENU_H
#define REPORT_MENU_H

void printReport(const string &title, const string &filterType, const string &filterValue);
void reportMenuByYear(int selectedYear);
void reportMenuByFaculty(const string &selectedFaculty);
void selectReport();
void selectYear();
void selectFaculty();
int extractYear(const string &date);

#endif