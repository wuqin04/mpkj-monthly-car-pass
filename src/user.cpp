#include "system.h"

#include <limits>
#include <cstdlib>

using namespace std;

// func definitions
void userMenu(User &user, User users[], int count) {
    bool infoComplete = (user.name != "-" && user.studentId != "-" && user.icNo != "-" && 
                         user.contact != "-" && user.faculty != "-" && user.carPlate != "-");
    if(!infoComplete)
        createInfo(user);
    

    bool rejectionShown = false;

    while (true) { 
        bool hasPaid = (user.paymentStatus.find("Paid_") != string::npos);
        bool hasApproved = (user.submissionStatus.find("Approved_") != string::npos);
        bool hasRejected = (user.submissionStatus.find("Rejected_") != string::npos);
        
        // Only show the payment reminder box if they are approved BUT haven't paid yet
        if (hasApproved && !hasPaid)
            showPaymentBox();

        if (hasRejected && !rejectionShown) 
            showRejectionBox(user);

        // Determine if the pass is Active or Inactive
        string displayStatus = (user.passStatus == "Active") ? "Active" : "Inactive";

        cout << "===========================================\n";
        cout << "|                USER MENU                |\n";
        cout << "===========================================\n";
        
        cout << "  MPKJ Pass Status: [" << displayStatus << "]\n";

        if (user.passStatus == "Active") {
            string expiryDate = calculateExpiryDate(user.submissionStatus, user.paymentAmount);
            cout << "  Valid Until     : [" << expiryDate << "]\n";
        }
        
        cout << "===========================================\n";
        cout << "|(1) view/update personal information     |\n";
        cout << "|(2) apply/renew monthly car parking pass |\n";
        cout << "|(3) view application status              |\n";
        cout << "|(4) payment menu                         |\n";
        cout << "|(5) exit program                         |\n";
        cout << "===========================================\n";

        cout << "Choose an action: ";
        int choice = 0;
        if (!(cin >> choice)) {
            system("cls");
            cout << "invalid input, try again.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        system("cls");
        switch (choice) {
            case 1:
                userInfo(user, users, count);
                break;
            case 2:
                // Lock out option 2 logically if they try to type '2' anyway
                if (hasPaid) {
                    cout << "Our records show the MPKJ car pass has already been paid. A duplicate application is not required.\n";
                    cout << "Press Enter to continue...";
                    clearBuffer();
                    cin.get();
                    system("cls");
                }
                else if (hasApproved) {
                    cout << "Your application has been approved. Please proceed to the payment menu.\n";
                    cout << "Press Enter to continue...";
                    clearBuffer();
                    cin.get();
                    system("cls");
                }
                else {
                    passRenewalMenu(user, users, count);
                }
                break;
            case 3:
                viewStatusMenu(user, users, count);
                break;
            case 4:
                paymentMenu(user, users, count);
                break;
            case 5:
                cout << "Bye!\n";
                return;
            default:
                cout << "Invalid input, try again.\n";
                break;
        }
    }
}

void showPaymentBox() {
    cout << "\n"; 
    cout << "*******************************************\n";
    cout << "*       A C T I O N  R E Q U I R E D      *\n";
    cout << "*******************************************\n";
    cout << "* *\n";
    cout << "* GOOD NEWS: Your monthly pass           *\n";
    cout << "* application has been APPROVED!         *\n";
    cout << "* *\n";
    cout << "* Please proceed to the Payment Menu     *\n"; 
    cout << "* (Option 4) to settle your fee.         *\n";
    cout << "* *\n";
    cout << "*******************************************\n";
    cout << "\nPress Enter to continue to your dashboard...";
    
    clearBuffer();
    cin.get();
    system("cls");
}

void showRejectionBox(User &user) {
    // Extract the reason CODE from the string
    string reasonCode = "0"; 
    size_t pipePos = user.submissionStatus.find('|');
    
    if (pipePos != string::npos) {
        reasonCode = user.submissionStatus.substr(pipePos + 1);
    }

    // Translate the code into a full message
    string displayReason = "Please contact administration.";
    
    if (reasonCode == "1") {
        displayReason = Settings::rejectionReason[0];
    } else if (reasonCode == "2") {
        displayReason = Settings::rejectionReason[1];
    } else if (reasonCode == "3") {
        displayReason = Settings::rejectionReason[2];
    } else if (reasonCode == "4") {
        displayReason = Settings::rejectionReason[3];
    }

    // Display the box
    cout << "\a\n"; 
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    cout << "!              A T T E N T I O N          !\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    cout << "!                                         !\n";
    cout << "!  Your monthly pass application has      !\n";
    cout << "!  been REJECTED.                         !\n";
    cout << "!                                         !\n";
    
    // Print the translated reason
    cout << "!  Reason: " << displayReason << "\n";
    
    cout << "!                                         !\n";
    cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
    cout << "\nPress Enter to continue to your dashboard...";
    
    clearBuffer();
    system("cls");
}

void userInfo(User &user, User users[], int count){    
    while(true){
        int choice;
	    cout << "===========================================\n";
        cout << "|             PERSONAL DETAILS            |\n";
        cout << "===========================================\n";

        cout << "Username: " << user.username << endl;
        cout << "Password: " << user.password << endl;
        cout << "Name: " << user.name << endl;
        cout << "Student ID: " << user.studentId << endl;
        cout << "IC: " << user.icNo << endl;
        cout << "Contact Number: " << user.contact << endl;
        cout << "Faculty: " << user.faculty << endl;
        cout << "Car Plate Number: " << user.carPlate << endl;

        cout << "===========================================\n";
        cout << "|(1) edit information                     |\n";
        cout << "|(2) back to main menu                    |\n";
        cout << "===========================================\n";
        cout << "Choose an action: ";
        cin >> choice;

        switch(choice){
        case 1:
            system("cls");
            editInfo(user, users, count);
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
        break;
    }
}

/* the technique we use here is temp file swap.
basically we open original file to read, create new temp file, if any updates we just copy and update
into temp file and remove original then rename temp file*/
void createInfo(User &user) {
    system("cls");
    cout << "===========================================\n";
    cout << "|             PERSONAL DETAILS            |\n";
    cout << "===========================================\n";
    cout << "Your account is newly created, please fill in your details\n\n";

    cout << "Enter Full Name: ";
    getline(cin, user.name);

    while (true) {
        cout << "Enter Student ID (eg:2402954): ";
        getline(cin, user.studentId);
        if (!validateStudentID(user.studentId)) {
            cout << "Invalid student id, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter IC (eg: 060419-02-0081): ";
        getline(cin, user.icNo);
        if (!validateIC(user.icNo)) {
            cout << "Invalid ic number, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }
    
    while (true) {
        cout << "Enter Contact Number (eg: 018-3224189): ";
        getline(cin, user.contact);
        if (!validateContact(user.contact)) {
            cout << "Invalid contact number, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    while (true) {  
        cout << "Enter Faculty (eg: LKC FES): ";
        getline(cin, user.faculty);
        if (!validateFaculty(user.faculty)) {
            cout << "Invalid faculty, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    while (true) {
        cout << "Enter Car Plate Number (eg: FB5378): ";
        getline(cin, user.carPlate);
        if (!validateCarPlate(user.carPlate)) {
            cout << "Invalid car plate, press enter to try again...";
            clearBuffer();
            continue;
        }
        break;
    }

    ifstream inFile(Settings::FILE_PATH.c_str());
    ofstream tempFile("temp.txt");

    if (!inFile.is_open() || !tempFile.is_open()) {
        cerr << "ERROR: Cannot open file,\n";
        return;
    }

    string line;
    while (getline(inFile, line)) {
        stringstream ss(line);
        string fileUsername;

        getline(ss, fileUsername, ',');

        if (fileUsername == user.username) {
            tempFile << user.username << "," 
                    << user.password << "," 
                    << user.name << "," 
                    << user.studentId << "," 
                    << user.icNo << "," 
                    << user.contact << "," 
                    << user.faculty << "," 
                    << user.carPlate << "," 
                    << user.submissionStatus << "," 
                    << "0.00" << ","
                    << user.paymentStatus << "," 
                    << user.passStatus << "\n";
        }
        else {
            tempFile << line << '\n';
        }
    }

    inFile.close();
    tempFile.close();

    remove(Settings::FILE_PATH.c_str());
    rename("temp.txt", Settings::FILE_PATH.c_str());

    cout << "\n===========================================\n";
    cout << "Information successfully saved!\n";
    cout << "Press Enter to continue...";
    clearBuffer();
    system("cls");
}

void editInfo(User &user, User users[], int count) {
    while (true){
        int choice;

	    cout << "===========================================\n";
        cout << "|           INFORMATION EDITING           |\n";
        cout << "===========================================\n";

        cout << "Username: " << user.username << endl;
        cout << "Password: " << user.password << endl;
        cout << "Name: " << user.name << endl;
        cout << "Student ID: " << user.studentId << endl;
        cout << "IC: " << user.icNo << endl;
        cout << "Contact Number: " << user.contact << endl;
        cout << "Faculty: " << user.faculty << endl;
        cout << "Car Plate Number: " << user.carPlate << endl;

        cout << "=============================\n";
        cout << "|(1) edit Username          |\n";
        cout << "|(2) edit Password          |\n";
        cout << "|(3) edit Contact Number    |\n";
        cout << "|(4) edit Faculty           |\n";
        cout << "|(5) edit Car Plate Number  |\n";
        cout << "|(6) back to user menu      |\n";        
        cout << "=============================\n";

        cout << "Choose an action: ";
        if (!(cin >> choice)) {
            cin.clear();
            clearBuffer();
            system("cls");
            cout << "Invalid input, please enter a number.\n";
            continue;
        }

        switch(choice){
            case 1:
                clearBuffer();
                while (true) {
                    string tempUsername;
                    cout << "Enter New Username: ";
                    getline(cin, tempUsername);
                    if (tempUsername.find(' ') != string::npos) {
                        cout << "Username cannot contain spaces, please try again.\n";
                        cout << "Enter to continue...";
                        clearBuffer();
                        continue;
                    }

                    if (usernameExist(tempUsername, users, count)) {
                        cout << "The username already exist, choose a new one. Press enter to continue...";
                        clearBuffer();
                        continue;
                    }

                    user.username = tempUsername;
                    cout << "Username successfully updated, press enter to continue.\n";
                    cin.get();
                    break;
                }   
                break;
            case 2:
                cout << "Enter New Password: ";
                clearBuffer();
                getline(cin, user.password);
                cout << "Your password has changed, press enter to continue.";
                cin.get();
                system("cls");
                break;
            case 3:
                clearBuffer();
                while (true) {
                    cout << "Enter Contact Number (eg: 018-3224189): ";
                    getline(cin, user.contact);
                    if (!validateContact(user.contact)) {
                        cout << "Invalid contact number, try again...\n";
                        continue;
                    }
                    break;
                }
                break;
            case 4:
                clearBuffer();
                while (true) {  
                    cout << "Enter Faculty (eg: LKC FES): ";
                    getline(cin, user.faculty);
                    if (!validateFaculty(user.faculty)) {
                        cout << "Invalid faculty, try again...\n";
                        continue;
                    }
                    break;
                }
                break;
            case 5 : 
                clearBuffer();
                while (true) {
                    cout << "Enter Car Plate Number (eg: FB5378): ";
                    getline(cin, user.carPlate);
                    if (!validateCarPlate(user.carPlate)) {
                        cout << "Invalid car plate, try again...\n";
                        continue;
                    }
                    break;
                }
                break;
            case 6:
                system("cls");
                return;
            default:
                system("cls");
                clearBuffer();
                cout << "Invalide input, please try again.\n";
                continue;
        }

        saveAllUsers(users, count);
        
        system("cls");
    }
}

bool validateStudentID(const string &studentId) {
    if (studentId.length() < 7 || studentId.length() > 7) return false;
    if (isDigits(studentId)) return true;

    return false;
}

bool validateIC(const string &ic) {
    if (ic.length() != 14) {
        return false;
    }
    
    const int MAX_IC_DIGITS = 14;

    for (size_t i = 0; i < MAX_IC_DIGITS; i++) {
        if (i == 6 || i == 9) {
            // position 6 and 9 must be "-"
            if (ic[i] != '-') return false;
        }
        else {
            // all other position must be digits
            if (!isdigit(ic[i])) return false;
        }
    }
    return true;
}

bool validateContact(const string &contact) {
    // length must be 11 or 12
    size_t len = contact.length();
    if (len != 11 && len != 12) {
        return false;
    }

    // first 3 characters must be digits
    for (size_t i = 0; i < 3; i++) {
        if (!isdigit(contact[i])) return false;
    }

    // 4th characters must be "-"
    if (contact[3] != '-') return false;

    // remaining characters must be digits
    for (size_t i = 4; i < len; i++) {
        if (!isdigit(contact[i])) return false;
    }
    return true;
}

bool validateFaculty(string &faculty) {
    for (size_t i = 0; i < faculty.length(); ++i) {
        faculty[i] = toupper(faculty[i]);
    }

    if (faculty == "LKC FES" || faculty == "LKCFES" || faculty == "FMHS" 
        || faculty == "FAM" || faculty == "FCI")
        return true;
    return false;
}

bool validateCarPlate(string &carPlate) {
    string cleaned = "";

    for (size_t i = 0; i < carPlate.length(); ++i) {
        if (carPlate[i] != ' ') {
            cleaned += toupper((unsigned char)carPlate[i]);
        }
    }

    size_t len = cleaned.length();
    if (len == 0) return false;

    size_t i = 0;

    // Validate 1 to 3 alphabets
    int letterCount = 0;
    while (i < len && isalpha((unsigned char)cleaned[i])) {
        letterCount++;
        i++;
    }
    if (letterCount < 1 || letterCount > 3) return false;

    // Validate 1 to 4 digits
    // The first digit must be between '1' and '9' (no leading zeros)
    int digitCount = 0;
    if (i < len && cleaned[i] >= '1' && cleaned[i] <= '9') {
        digitCount++;
        i++;
    } else {
        return false;
    }

    // Subsequent digits can be '0' to '9'
    while (i < len && isdigit((unsigned char)cleaned[i])) {
        digitCount++;
        i++;
    }
    
    // Total digits cannot exceed 4
    if (digitCount > 4) return false;

    // If we haven't reached the end of the cleaned string, it's invalid
    if (i != len) return false;

    // Modify the referenced string to strictly match the requested format
    carPlate = cleaned.substr(0, letterCount) + " " + cleaned.substr(letterCount);

    return true;
}

bool isDigits(const string &s) {
    if (s.empty()) {
        return false;
    }
    
    for (size_t i = 0; i < s.length(); ++i) {
        if (!isdigit(static_cast<unsigned char>(s[i]))) {
            return false;
        }
    }
    
    return true;
}

bool usernameExist(const string &username, User users[], int count) {
    for (int i = 0; i < count; i++) {
        if (username == users[i].username) return true;
    }
    return false;
}

void saveAllUsers(User users[], int count) {
    ofstream outFile(Settings::FILE_PATH.c_str(), ios::trunc);

    if (!outFile.is_open()) {
        cerr << "ERROR: Cannot open file for saving.\n";
        return;
    }

    outFile << "username,password,name,studentID,ICNo,contact,faculty,carPlate,submissionStatus,paymentAmount,paymentStatus,passStatus\n";

    for (int i = 0; i < count; i++) {
        outFile << users[i].username << ","
                << users[i].password << ","
                << users[i].name << ","
                << users[i].studentId << ","
                << users[i].icNo << ","
                << users[i].contact << ","
                << users[i].faculty << ","
                << users[i].carPlate << ","
                << users[i].submissionStatus << ","
                << fixed << setprecision(2) << users[i].paymentAmount << ","
                << users[i].paymentStatus << ","
                << users[i].passStatus << "\n";
    }

    outFile.close();
}

void clearBuffer() {
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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

string getCurrentTimeStamp() {
    time_t now = time(0);
    tm *t = localtime(&now);
    char buf[32];
    sprintf(buf, "%04d-%02d-%02d_%02d:%02d:%02d",
        1900 + t->tm_year, 1 + t->tm_mon, t->tm_mday,
        t->tm_hour, t->tm_min, t->tm_sec);
    return string(buf);;
}

string getKeyword(const string &status) {
    size_t pos = status.find('_');
    if (pos == string::npos) return status;
    return status.substr(0, pos);
}

bool findUser(const string &username, User users[], int count, int &index) {
    for (int i = 0; i < count; i++) {
        if (users[i].username == username) {
            index = i;
            return true;
        }
    }
    return false;
}

void infoComplete(User &user, User users[], int count){
    // Check if all required fields are filled
    if (user.name != "" && user.studentId != "" &&
        user.icNo != "" && user.contact != "" &&
        user.faculty != "" && user.carPlate != "") {

        // Update BOTH the current active session and the master array
        user.passStatus = Settings::INFO_COMPLETED;
        users[count].passStatus = Settings::INFO_COMPLETED;

        saveAllUsers(users, count);
    }
    else {
        users[count].passStatus = Settings::INFO_INCOMPLETE;
        saveAllUsers(users, count);
    }
}

void passChoice(User &user, User users[], int count, int index) {
    while (true) {
        int choice;

        cout << "===========================================================\n";
        cout << "|            MONTHLY PASS APPLICATION CHOICES             |\n";
        cout << "===========================================================\n";
        cout << "|Choice comparison:                                       |\n";
        cout << "|Monthly                                                  |\n";
        cout << "|  -RM " << Settings::MONTHLY_PRICE << "                                               |\n";
        cout << "|  -lasts only for one month                              |\n";
        cout << "|                                                         |\n";
        cout << "|Per semester                                             |\n";
        cout << "|  -RM " << Settings::SEM_PRICE << "                                             |\n";
        cout << "|  -lasts for 4 months (about a semesters' worth)         |\n";
        cout << "|  -save up to 5% compared to buying monthly for 4 months |\n";
        cout << "===========================================================\n";
        cout << "|(1) one month                                            |\n";
        cout << "|(2) one semester                                         |\n";
        cout << "|(3) cancel                                               |\n";
        cout << "===========================================================\n";
        cout << "Choose the type of pass you wish to apply: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Use the passed array and index – no local redeclaration!
                users[index].submissionStatus = "Submitted_" + getCurrentTimeStamp();
                users[index].paymentAmount = Settings::MONTHLY_PRICE;
                users[index].passStatus = Settings::APPLIED_PASS;
                saveAllUsers(users, count);
                user.passStatus = Settings::APPLIED_PASS;
                system("cls");
                break;

            case 2:
                users[index].submissionStatus = "Submitted_" + getCurrentTimeStamp();
                users[index].paymentAmount = Settings::SEM_PRICE;
                users[index].passStatus = Settings::APPLIED_PASS;
                saveAllUsers(users, count);
                user.passStatus = Settings::APPLIED_PASS;
                system("cls");
                break;

            case 3:
                system("cls");
                break;

            default:
                system("cls");
                cin.clear();
                clearBuffer();
                cout << "Invalid input, please try again.\n";
                continue;
        }
        break;
    }
}

string parseInternalStatus(const string& rawStatus, const User& user) {
    size_t pos = rawStatus.find('_');
    string keyword = (pos != string::npos) ? rawStatus.substr(0, pos) : rawStatus;
    
    // Convert to lowercase for easy comparison
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
    
    if (keyword == "active" || keyword == "approved") {
        return "approved";
    } else if (keyword == "rejected") {
        return "rejected";
    } else if (keyword == "pending" || keyword == "submitted" || rawStatus == "2") { 
        return "pending";
    } else if (keyword == "complete") {
        return Settings::INFO_COMPLETED;
    } else if (keyword == "incomplete") {
        return Settings::INFO_INCOMPLETE;
    } else {
        // Fallback: check if personal info is complete
        if (user.name != "" && user.studentId != "" && user.icNo != "" &&
            user.contact != "" && user.faculty != "" && user.carPlate != "") {
            return Settings::INFO_COMPLETED;
        }
        return Settings::INFO_INCOMPLETE;
    }
}

void passRenewalMenu(User &user, User users[], int count) {
    updateCount(user, users, count);
    
    int index = -1;
    if (!findUser(user.username, users, count, index)) {
        return; // User not found
    }

    while (true) {
        // Re-evaluate status at the start of every loop iteration
        string rawStatus = users[index].submissionStatus;
        string internalStatus = parseInternalStatus(rawStatus, user);
        
        if (internalStatus != rawStatus && internalStatus != "2") {
            users[index].passStatus = internalStatus;
            // Only save if it actually needs an update to prevent spamming data.txt
            saveAllUsers(users, count); 
        }
        user.passStatus = internalStatus;

        system("cls");
        cout << "=====================================================\n";
        cout << "|             MONTHLY PASS APPLICATION              |\n";
        cout << "=====================================================\n";
        
        if (internalStatus == Settings::INFO_INCOMPLETE)
            cout << "WARNING: Your personal information is not complete.\n";
        else if (internalStatus == Settings::INFO_COMPLETED)
            cout << "You are eligible to apply for a monthly car pass.\n";
        else if (internalStatus == "pending")
            cout << "Your application is being processed.\n";
        else if (internalStatus == "approved")
            cout << "Your monthly pass has been approved and is active.\n";
        else if (internalStatus == "rejected")
            cout << "Your application was rejected. You may re-apply.\n";
        else
            cout << "Current pass status: " << internalStatus << "\n";
            
        cout << "=====================================================\n";
        
        // Print menu options dynamically based on status
        if (internalStatus == Settings::INFO_COMPLETED) {
            cout << "|(1) apply for mpkj car pass\n";
            cout << "|(2) application status menu\n";
            cout << "|(3) back to user menu\n";
        } else if (internalStatus == "pending" || internalStatus == "approved") {
            cout << "|(1) view application status\n";
            cout << "|(2) back to user menu\n";
        } else if (internalStatus == "rejected") {
            cout << "|(1) apply for mpkj monthly car pass (re-apply)\n";
            cout << "|(2) view rejection details\n";
            cout << "|(3) back to user menu\n";
        }
        cout << "=====================================================\n";
        cout << "Choose your option: ";
        
        // Handle input centrally
        int choice = 0;
        if (!(cin >> choice)) {
            cout << "Invalid input. Press Enter to continue...";
            clearBuffer();
            continue;
        }

        system("cls");
        bool actionTaken = false; // Flag to check if we need to reload data

        // Route the choice based on the status
        if (internalStatus == Settings::INFO_INCOMPLETE) {
            cout << "Some required fields are missing. Please visit the Edit Information menu to provide the necessary details.\n";
            clearBuffer();
        }
        else if (internalStatus == Settings::INFO_COMPLETED) {
            if (choice == 1) { 
                passChoice(user, users, count, index); 
                actionTaken = true; 
            }
            else if (choice == 2) { 
                viewStatusMenu(user, users, count); 
                actionTaken = true; 
            }
            else if (choice == 3) 
                return;
            else { 
                cout << "Invalid choice. Press Enter..."; 
                cin.ignore(); 
                cin.get(); 
            }
        } 
        else if (internalStatus == "pending" || internalStatus == "approved") {
            if (choice == 1) { 
                viewStatusMenu(user, users, count); 
                actionTaken = true; 
            }
            else if (choice == 2) 
                return;
            else { 
                cout << "Invalid choice. Press Enter..."; 
                cin.ignore(); 
                cin.get(); 
            }
        } 
        else if (internalStatus == "rejected") {
            if (choice == 1) { 
                passChoice(user, users, count, index); 
                actionTaken = true; 
            }
            else if (choice == 2) { 
                viewStatusMenu(user, users, count); 
                actionTaken = true; 
            }
            else if (choice == 3) 
                return;
            else { 
                cout << "Invalid choice. Press Enter..."; 
                cin.ignore(); 
                cin.get(); 
            }
        }

        // Centralized data reload: Only reload if the user actually clicked a menu item
        // that could have changed the data.txt file.
        if (actionTaken) {
            updateCount(user, users, count);
            findUser(user.username, users, count, index); // Update the index in case sorting changed
            return;
        }
    }
}

void paymentMenu(User &user, User users[], int count) {
    int index = -1;
    if (!findUser(user.username, users, count, index)) {
        cout << "ERROR: User not found in data.txt\n";
        return;
    }

    while(true){
        // Check current status
        bool isApproved = (user.submissionStatus.find("Approved_") != string::npos);
        bool isPaid = (user.paymentStatus.find("Paid_") != string::npos) || (user.passStatus == "Active");

        cout << "====================================================================\n";
        cout << "|                            PAYMENT MENU                          |\n";
        cout << "====================================================================\n";
        cout << "ID: " << user.studentId << endl;
        cout << "Name: " << user.name << endl;
        cout << "--------------------------------------------------------------------\n";

        if (isPaid) {
            cout << "Pass Status: " << user.passStatus << endl;

            string expiryDate = calculateExpiryDate(user.submissionStatus, user.paymentAmount);
            cout << "Expiry Date: " << expiryDate << endl;     

            cout << "\nYou have successfully settled your payment.\n";
        } 
        else if (isApproved) {
            cout << "Application Status: APPROVED\n";
            cout << "Amount due: RM " << fixed << setprecision(2) << user.paymentAmount << endl;
            cout << "\nIf there are any problems, please proceed to the Department of \n";
            cout << "Finance for assistance.\n";
        } 
        else {
            cout << "Application Status: PENDING / NOT APPROVED YET\n";
            cout << "\nYou cannot make a payment until an Admin has approved your \n";
            cout << "monthly pass application.\n";
        }
        cout << "====================================================================\n";

        // Display Menu Options based on state
        if (isApproved && !isPaid) {
            cout << "|(1) make payment                                                  |\n";
            cout << "|(2) return to user main menu                                      |\n";
        } else {
            cout << "|(1) return to user main menu                                      |\n";
        }
        cout << "====================================================================\n";
        
        cout << "Choose an action: ";
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            clearBuffer();
            system("cls");
            cout << "Invalid input, please enter a number.\n";
            continue;
        }
        
        if (isApproved && !isPaid) {
            // User can pay OR leave
            switch(choice) {
                case 1: {
                    system("cls");

                    // Process Payment
                    string payTime = "Paid_" + datetime(); // Ensure datetime() returns a string
                    user.paymentStatus = payTime;
                    user.passStatus = "Active";

                    users[index].paymentStatus = payTime;
                    users[index].passStatus = "Active";

                    saveAllUsers(users, count);

                    cout << "=============================\n";
                    cout << "| Payment successfully made |\n";
                    cout << "=============================\n";
                    cout << "Press ENTER to continue...";
                    clearBuffer(); 
                    cin.get();
                    
                    system("cls");
                    continue;
                }
                case 2:
                    system("cls");
                    return;
                default:
                    system("cls");
                    cout << "Invalid input, please try again.\n";
                    continue;
            }
        } 
        else {
            // User has only one choice: Return to main menu
            if (choice == 1) {
                system("cls");
                return;
            } else {
                system("cls");
                cout << "Invalid input, please try again.\n";
                continue;
            }
        }
    }
}

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
	}
	fin.close();
}		

void viewStatusMenu(User &user, User users[], int count) {
    Pass pass;
    loadPassStatus(pass, user.username);

    string statusOnly;
    size_t pos = pass.applyStatus.find('_');
    if (pos != string::npos) {
        statusOnly = pass.applyStatus.substr(0, pos);
        if (statusOnly == "Submitted") statusOnly = "Pending";
    } else {
        statusOnly = pass.applyStatus;
    }

    while (true) {
        int choice;
        cout << "============================================================================\n";
        cout << "|                     APPLICATION STATUS                                   |\n";
        cout << "============================================================================\n";

        if (pass.applyStatus.find("Approved") != string::npos) {
            cout << "\nYour application is approved\n";
            cout << "Approved time: " << pass.applyStatus.substr(pass.applyStatus.find('_') + 1) << endl << endl;
        } 
        else if (pass.applyStatus.find("Rejected") != string::npos) {
            cout << "\nYour submission is rejected.\n";
            cout << "Rejected time: " << pass.applyStatus.substr(pass.applyStatus.find('_') + 1) << endl << endl;
        }
        else if (pass.applyStatus.find("Pending") != string::npos || pass.applyStatus.find("Submitted") != string::npos) {
            cout << "\nYour application is still pending for review\n\n";
        }
        else {
            cout << "You have yet to apply for a car pass\n";
        }

        cout << "============================================================================\n";

        if (statusOnly == "Approved") {
            cout << "|(1) show due payment amount                              \n";
            cout << "|(2) return to main menu                                  \n";
        }
        else if (statusOnly == "Rejected") {
            cout << "|(1) show reason for rejection                            \n";
            cout << "|(2) reapply for car pass                                 \n";
            cout << "|(3) return to main menu                                  \n";
        }
        else if (statusOnly == "Pending") {
            cout << "|(1) return to main menu                                  \n";
        }
        else {
            cout << "|(1) apply for car pass                                   \n";
            cout << "|(2) return to main menu                                  \n";
        }

        cout << "============================================================================\n";
        cout << "Choose an action: ";
        cin >> choice;

        if (statusOnly == "Approved") {
            switch (choice) {
                case 1:
                    system("cls");
                    paymentMenu(user, users, count);
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
        else if (statusOnly == "Rejected") {
            switch (choice) {
                case 1: {
                    system("cls");
                    cout << "============================================================\n";
                    cout << "|                  Reason for rejection                    |\n";
                    cout << "============================================================\n";

                    // Initialize default values
                    string statusStr = user.submissionStatus;
                    string latestTime = "N/A";
                    string reasonCode = "0";
                    string displayReason = "Please contact administration.";

                    // Extract the Time and the Reason Code
                    size_t underscorePos = statusStr.find('_');
                    size_t pipePos = statusStr.find('|');

                    if (underscorePos != string::npos) {
                        if (pipePos != string::npos) {
                            // Extract time between '_' and '|'
                            latestTime = statusStr.substr(underscorePos + 1, pipePos - underscorePos - 1);
                            // Extract the code after '|'
                            reasonCode = statusStr.substr(pipePos + 1);
                        } else {
                            latestTime = statusStr.substr(underscorePos + 1);
                        }
                    }

                    // Translate the code back to the human-readable sentence
                    if (reasonCode == "1") {
                        displayReason = Settings::rejectionReason[0];
                    } else if (reasonCode == "2") {
                        displayReason = Settings::rejectionReason[1];
                    } else if (reasonCode == "3") {
                        displayReason = Settings::rejectionReason[2];
                    } else if (reasonCode == "4") {
                        displayReason = Settings::rejectionReason[3];
                    } else if (reasonCode != "0" && pipePos != string::npos) {
                        displayReason = reasonCode; 
                    }

                    // Display the results
                    cout << "| Reason: " << left << setw(49) << displayReason << "|\n";
                    cout << "| Time:   " << setw(49) << latestTime << "|\n";
                    cout << "============================================================\n";
                    
                    system("pause");
                    system("cls");
                    continue;
                }
                case 2:
                    system("cls");
                    passRenewalMenu(user, users, count);
                    break;
                case 3:
                    system("cls");
                    return;
                default:
                    system("cls");
                    cin.clear();
                    clearBuffer();
                    cout << "Invalid input, please try again.\n";
                    continue;
            }
        }
        else if (statusOnly == "Pending") {
            if (choice == 1) {
                system("cls");
                return;
            } else {
                system("cls");
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input, please try again.\n";
                continue;
            }
        }
        else {
            switch (choice) {
                case 1:
                    system("cls");
                    passRenewalMenu(user, users, count);
                    break;
                case 2:
                    system("cls");
                    return;
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
	
void mainMenu() {
    User users[Settings::MAX_USERS];
    User user;
    int count = 0;

	while (true) {
        updateCount(user, users, count);

		string username = "";
		string password = "";
		char ch;

		cout << "=======================================================\n";
		cout << "|                     MAIN MENU                       |\n";
		cout << "=======================================================\n";
		cout << "|      Welcome to MPKJ Monthly Car Pass System        |\n";
		cout << "|Input 'new' to create new user or 'q' to exit program|\n";
		cout << "=======================================================\n";

		cout << "Username: ";
		getline(cin, username);

		// convert every characters into lowercase
		for (size_t i = 0; i < username.length(); i++) {
            username[i] = tolower(username[i]);
        }

		if (username == "q") {
			cout << "Bye!";
			return;
		}

		if (username == "new") {
			createNewUser(users, count);
			continue;
		}

		cout << "Password: ";
		getline(cin, password);

		if (username == Settings::ADMIN_LOGIN && password == Settings::ADMIN_PASS) {
			system("cls");
			adminMenu();
			break;
		}

		// check if user's login and password are store into our data.txt file
		for (int i = 0; i < count; i++) {
			if (username == users[i].username && password == users[i].password) {
				system("cls");
				userMenu(users[i], users, count);
				return;
			}
		}
		
		cout << "Account not found. Would you like to create one? (y/n): ";
		cin >> ch;
		ch = static_cast<char>(tolower(ch));

		if (ch == 'y') {
            clearBuffer();
			createNewUser(users, count);
            continue;
		}
		else if(ch == 'n') {
			cout << "Terminated account creation.\n";
			cout << "Press Enter to return...";
			cin.get();
            clearBuffer();
			system("cls");
			continue;
		}
		else {
			cout << "Invalid input, please enter only 'y' or 'n'.\n";
			cout << "Press Enter to continue...";
			cin.get();
			clearBuffer();
			system("cls");
			continue;
		}
		break;
	}
}

void updateCount(User &user, User users[], int &count) {
    count = 0;
    ifstream inputFile(Settings::FILE_PATH.c_str());
    string line = "";
    
    if (!inputFile.is_open()) {
        cerr << "ERROR! CANNOT RETRIEVE THE DATA FILE.\n";
        return;
    }
	
	// ignore the first header line
    getline(inputFile, line);

	// get every single user information and store them into array
    while (getline(inputFile, line)) {
        if (count >= Settings::MAX_USERS) {
            cerr << "WARNING: Maximum users limit reached. Some records were not loaded.\n";
            break;
        }

        stringstream ss(line);
        string token;
        
        User tempUser;

        getline(ss, tempUser.username, ',');
        getline(ss, tempUser.password, ',');
        getline(ss, tempUser.name, ',');
        getline(ss, tempUser.studentId, ',');
        getline(ss, tempUser.icNo, ',');
        getline(ss, tempUser.contact, ',');
        getline(ss, tempUser.faculty, ',');
        getline(ss, tempUser.carPlate, ',');
        getline(ss, tempUser.submissionStatus, ',');

		// convert string into double data type
        getline(ss, token, ',');
		if (!token.empty())
        	tempUser.paymentAmount = atof(token.c_str());

        getline(ss, tempUser.paymentStatus, ',');
        getline(ss, tempUser.passStatus, ',');

        users[count] = tempUser;
        count++;

        if (tempUser.username == user.username) user = tempUser;
    }
    inputFile.close();
}

void createNewUser(User users[], int count) {
	while (true) {
		string newUser;
		string newPassword;

		system("cls");
		cout << "=====================================================\n";
		cout << "|                 CREATE NEW USER                   |\n";
		cout << "=====================================================\n";
		cout << "|Enter your new username and new password           |\n";
		cout << "|or 'q' to terminate account creation.              |\n";
		cout << "=====================================================\n";
		cout << "New Username: ";
		getline(cin, newUser);

        if (newUser.find(' ') != string::npos) {
            cout << "Username cannot contain spaces, please try again.\n";
            cout << "Enter to continue...";
			clearBuffer();
			system("cls");
			continue;
        }

        if (newUser.empty()) {
            cout << "Username cannot be empty, please try again.\n";
            cout << "Enter to continue...";
            clearBuffer();
            system("cls");
            continue;
        }

		for (int i = 0; i < count; i++) {
            newUser[i] = tolower(newUser[i]);
        }

		if (newUser == "q") {
			system("cls");
			return;
		}

		if (containInvalidChar(newUser)) {
			cout << "Username cannot contain special characters, please try again.\n";
			cout << "Enter to continue...";
			clearBuffer();
			cin.get();
			system("cls");
			continue;
		}

		cout << "New password: ";
		cin >> newPassword;

		// check whether the username already exist
		if (isUserPassExist(newUser, users, count)) {
			cout << "The username is already taken, please try again.\n";
			cout << "Enter to continue...";
			clearBuffer();
			cin.get();
			system("cls");
			continue;
		}
		else {
			ofstream newLogin(Settings::FILE_PATH.c_str(), ios::app);

			if (!newLogin.is_open()){
				cerr << "ERROR: CANNOT OPEN FILE FOR APPENDING.\n";
				return;
			}

			newLogin << newUser << "," << newPassword << ",-,-,-,-,-,-,-_-,0.00,-_-,-" << "\n";
			newLogin.close();

			cout << "Your account is already created,\nPlease login now.\n";

			clearBuffer();

			cout << "Press Enter to return to main menu...";
			cin.get();

			system("cls");
			return;
		}		
	}
}

// check whether the newUser is already exist in our system
bool isUserPassExist(string newUser, User users[], int count) {
	for (int i = 0; i < count; i++) {
		if (newUser == users[i].username)
			return true;
	}
	return false;
}

// check if string contains special chars
bool containInvalidChar(string username) {
    for (size_t i = 0; i < username.length(); ++i) {
        if (!isalnum(static_cast<unsigned char>(username[i]))) {
            return true;
        }
    }

    return false;
}

// check for leap years (needed for feb)
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// get correct numbers of days in a given month
int getDaysInMonth(int year, int month) {
    // we ensure the index is same as month so we assign index 0 to 0;
    int daysInMonth[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year)) {
        return 29;
    }
    return daysInMonth[month];
}

// get the expiry date based on given applied mpkj car pass
string calculateExpiryDate(string submissionStatus, double paymentAmount) {
    size_t firstUnderscore = submissionStatus.find('_');
    if (firstUnderscore == string::npos) return "Unknown Date";

    // Grab exactly 10 characters right after "Approved_" (which is the YYYY-MM-DD)
    string dateStr = submissionStatus.substr(firstUnderscore + 1, 10);

    int year = atoi(dateStr.substr(0, 4).c_str());
    int month = atoi(dateStr.substr(5, 2).c_str());
    int day = atoi(dateStr.substr(8, 2).c_str());

    int monthsToAdd = 0;
    if (abs(paymentAmount - 31.80) < 0.01) {
        monthsToAdd = 1;
    }
    else {
        monthsToAdd = 4;
    }

    month += monthsToAdd;

    if (month > 12) {
        year += 1;
        month -= 12;
    }

    int maxDays = getDaysInMonth(year, month);
    if (day > maxDays) {
        day = maxDays;
    }

    ostringstream oss;
    oss << year << "-"
        << setfill('0') << setw(2) << month << "-"
        << setfill('0') << setw(2) << day;

    return oss.str();
}