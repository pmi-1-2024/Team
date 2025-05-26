#include <iostream>
#include <string>
#include <vector>
#include <limits>    
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Genre.h"
#include "BookManager.h"
#include "User.h"
#include "PhysicalLibrary.h"
#include "LibraryStockItem.h"
#include "PhysicalLibraryManager.h"
#include "LibraryStockManager.h"

using namespace std;

void showAuthMainMenu() {
    cout << "\n========== MAIN PROGRAM MENU ==========" << endl;
    cout << "1. Login" << endl;
    cout << "2. Register" << endl;
    cout << "0. Exit Program" << endl;
    cout << "======================================" << endl;
    cout << "Select an option: ";
}

void showRoleMenu() {
    cout << "\n--- Role Selection ---" << endl;
    cout << "1. Customer" << endl;
    cout << "2. Librarian" << endl;
    cout << "3. Admin" << endl;
    cout << "Select role: ";
}

string getRoleFromChoice(int choice) {
    switch (choice) {
    case 1: return "Customer";
    case 2: return "Librarian";
    case 3: return "Admin";
    default: return "";
    }
}

void registerUser(const string& filename = "users.txt") {
    int roleChoice;
    cout << "\n==== User Registration ====\n";
    showRoleMenu();
    cin >> roleChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid role choice.\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string role = getRoleFromChoice(roleChoice);
    if (role.empty()) {
        cout << "Invalid role." << endl;
        return;
    }

    string surname_reg, name_reg, email_reg, password_reg;
    cout << "Enter surname: "; getline(cin, surname_reg);
    cout << "Enter name: "; getline(cin, name_reg);
    cout << "Enter email: "; getline(cin, email_reg);
    cout << "Enter password: "; getline(cin, password_reg);

    User newUser = User(User::generateID(), surname_reg, name_reg, email_reg, password_reg, role);

    if (User::exists(filename, newUser.getEmail())) {
        cout << "User with this email already exists.\n";
        return;
    }
    newUser.saveToFile(filename);
    cout << "Registration successful!\n";
}

bool loginUser(User& loggedInUser, const string& filename = "users.txt") {
    int roleChoice;
    string email, password;

    cout << "\n==== User Login ====\n";
    showRoleMenu();
    cin >> roleChoice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid role choice.\n";
        return false;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    string role = getRoleFromChoice(roleChoice);
    if (role.empty()) {
        cout << "Invalid role." << endl;
        return false;
    }

    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter password: ";
    getline(cin, password);

    if (User::authenticate(filename, role, email, password)) {
        loggedInUser = User::loadByEmail(filename, email);
        if (loggedInUser.getId().empty() || loggedInUser.getRole() != role) {
            cout << "Login failed: Could not retrieve user data or role mismatch after authentication." << endl;
            return false;
        }
        cout << "Successfully logged in as " << role << "!" << endl;
        return true;
    }
    else {
        cout << "Incorrect email, password, or role.\n";
        return false;
    }
}


int main() {

    BookManager bookManager;

    vector<PhysicalLibrary> physicalLibrariesList;
    PhysicalLibraryManager physicalLibraryManager(&physicalLibrariesList);

    vector<LibraryStockItem> stockItemsList;
    LibraryStockManager stockManager(&stockItemsList, bookManager);

    User currentUser;
    bool isLoggedIn = false;
    int authChoice;

    do {
        showAuthMainMenu();
        cin >> authChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            authChoice = -1;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (authChoice) {
        case 1:
            isLoggedIn = loginUser(currentUser);
            if (isLoggedIn) {
                cout << "\nWelcome, " << currentUser.getName() << " (" << currentUser.getRole() << ")!\n";

                if (currentUser.getRole() == "Librarian") {
                    bookManager.run();
                }
                else if (currentUser.getRole() == "Admin") {
                    int adminChoice;
                    do {
                        cout << "\n--- Administrator Menu ---\n"
                            << "1. Manage Book Catalog (BookManager)\n"
                            << "2. Manage Physical Libraries\n"
                            << "3. Manage Library Stock\n"
                            << "0. Exit Administrator Menu\n"
                            << "Your choice: ";
                        cin >> adminChoice;
                        if (cin.fail()) {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            adminChoice = -1;
                        }
                        else {
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        }

                        switch (adminChoice) {
                        case 1: bookManager.run(); break;
                        case 2: physicalLibraryManager.runPhysicalLibraryMenu(); break;
                        case 3: stockManager.runStockManagementMenu(physicalLibraryManager); break;
                        case 0: cout << "Exiting Administrator Menu.\n"; break;
                        default: cout << "Invalid choice.\n";
                        }
                        if (adminChoice != 0) {
                            cout << "Press Enter to continue...";
                            string dummy; getline(cin, dummy);
                        }
                    } while (adminChoice != 0);
                }
                else if (currentUser.getRole() == "Customer") {
                    cout << "Customer menu is not yet implemented in this integration.\n";
                }
                else {
                    cout << "No menu defined for your role.\n";
                }
                isLoggedIn = false;
            }
            break;
        case 2:
            registerUser();
            break;
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
        if (authChoice != 0) {
            if (!isLoggedIn || (authChoice == 1 && !isLoggedIn) || authChoice == 2 || authChoice == -1) {
                cout << "Press Enter to continue...";
                string dummy; getline(cin, dummy);
            }
        }
    } while (authChoice != 0);

    return 0;
}