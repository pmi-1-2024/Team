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
#include "Order.h"
#include "OrderManager.h"
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
    try {
        int roleChoice;
        cout << "\n==== User Registration ====\n";
        showRoleMenu();
        cin >> roleChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid role choice.");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string role = getRoleFromChoice(roleChoice);
        if (role.empty()) {
            throw runtime_error("Invalid role.");
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
    catch (const exception& e) {
        cerr << "Registration error: " << e.what() << endl;
    }
}

bool loginUser(User& loggedInUser, const string& filename = "users.txt") {
    try {
        int roleChoice;
        string email, password;

        cout << "\n==== User Login ====\n";
        showRoleMenu();
        cin >> roleChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            throw runtime_error("Invalid role choice.");
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        string role = getRoleFromChoice(roleChoice);
        if (role.empty()) {
            throw runtime_error("Invalid role.");
        }

        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter password: ";
        getline(cin, password);

        if (User::authenticate(filename, role, email, password)) {
            loggedInUser = User::loadByEmail(filename, email);
            if (loggedInUser.getId().empty() || loggedInUser.getRole() != role) {
                throw runtime_error("Login failed: Could not retrieve user data or role mismatch.");
            }
            cout << "Successfully logged in as " << role << "!" << endl;
            return true;
        }
        else {
            cout << "Incorrect email, password, or role.\n";
            return false;
        }
    }
    catch (const exception& e) {
        cerr << "Login error: " << e.what() << endl;
        return false;
    }
}

void customerMenu(BookManager& bookManager, OrderManager& orderManager, const User& currentUser) {
    int customerChoice;

    do {
        cout << "\n--- Customer Menu ---"
            << "\n1. View Available Books"
            << "\n2. Borrow a Book"
            << "\n3. Return a Book"
            << "\n4. Buy a Book"
            << "\n5. View Order History"
            << "\n0. Logout"
            << "\nYour choice: ";

        cin >> customerChoice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            customerChoice = -1;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        switch (customerChoice) {
        case 1:
            cout << "\n=== Available Books ===" << endl;
            bookManager.viewBooks();
            break;
        case 2:
            orderManager.borrowBook(currentUser);
            break;
        case 3:
            orderManager.returnBook(currentUser);
            break;
        case 4:
            orderManager.buyBook(currentUser);
            break;
        case 5:
            orderManager.viewOrderHistory(currentUser);
            break;
        case 0:
            cout << "Logging out..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        if (customerChoice != 0) {
            cout << "\nPress Enter to continue...";
            string dummy; getline(cin, dummy);
        }

    } while (customerChoice != 0);
}

void changeUserRole(const string& filename = "users.txt") {
    string emailToFind;
    cout << "Enter email of the user whose role you want to change: ";
    getline(cin, emailToFind);

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Could not open user file.\n";
        return;
    }

    vector<User> users;
    string tempId, tempSurname, tempName, tempEmail, tempPassword, tempRole, emptyLine;

    while (getline(file, tempId) &&
        getline(file, tempSurname) &&
        getline(file, tempName) &&
        getline(file, tempEmail) &&
        getline(file, tempPassword) &&
        getline(file, tempRole)) {
        users.emplace_back(tempId, tempSurname, tempName, tempEmail, tempPassword, tempRole);
        getline(file, emptyLine);
    }
    file.close();

    bool found = false;
    for (auto& user : users) {
        if (user.getEmail() == emailToFind) {
            found = true;
            cout << "Current role: " << user.getRole() << "\n";
            cout << "Choose new role:\n1. Customer\n2. Librarian\n3. Admin\nChoice: ";
            int choice;
            cin >> choice;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (choice) {
            case 1: user.setRole("Customer"); break;
            case 2: user.setRole("Librarian"); break;
            case 3: user.setRole("Admin"); break;
            default: cout << "Invalid choice.\n"; return;
            }

            cout << "Role updated successfully.\n";
            break;
        }
    }

    if (!found) {
        cout << "User with this email not found.\n";
        return;
    }

    User::saveAllUsers(filename, users);
}



int main() {
    try {
        BookManager bookManager;
        OrderManager orderManager(&bookManager);
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
                                << "1. Manage Physical Libraries\n"
                                << "2. Manage Library Stock\n"
                                << "3. Change User Role\n"
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
                            case 1: physicalLibraryManager.runPhysicalLibraryMenu(); break;
                            case 2: stockManager.runStockManagementMenu(physicalLibraryManager); break;
                            case 3: changeUserRole(); break;
                            case 0: cout << "Exiting Administrator Menu.\n"; break;
                            default: cout << "Invalid choice.\n";
                            }
                            if (adminChoice != 0) {
                                cout << "Press Enter to continue..."; string dummy; getline(cin, dummy);
                            }
                        } while (adminChoice != 0);
                    }
                    else if (currentUser.getRole() == "Customer") {
                        customerMenu(bookManager, orderManager, currentUser);
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
                    cout << "Press Enter to continue..."; string dummy; getline(cin, dummy);
                }
            }
        } while (authChoice != 0);

        return 0;
    }
    catch (const exception& e) {
        cerr << "Fatal error: " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unknown fatal error occurred." << endl;
        return 1;
    }
}