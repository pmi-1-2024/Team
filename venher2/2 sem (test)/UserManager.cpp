#include "UserManager.h"
#include <iostream>
using namespace std;

UserManager::UserManager(vector<User>* usersList) {
    users = usersList;
}

void UserManager::showAllUsers() {
    cout << "\n===== USER LIST =====\n";
    for (const auto& user : *users) {
        cout << "ID: " << user.getId()
            << " | Name: " << user.getFullName()
            << " | Email: " << user.getEmail()
            << " | Role: ";

        switch (user.getRole()) {
        case Role::ADMIN:
            cout << "Admin";
            break;
        case Role::LIBRARIAN:
            cout << "Librarian";
            break;
        case Role::USER:
            cout << "User";
            break;
        }
        cout << "\n";
    }
}

void UserManager::changeUserRole() {
    string id;
    cout << "Enter user ID to change role: ";
    cin >> id;

    for (auto& user : *users) {
        if (user.getId() == id) {
            int newRole;
            cout << "Choose new role:\n1. Admin\n2. Librarian\n3. User\nYour choice: ";
            cin >> newRole;

            if (newRole < 1 || newRole > 3) {
                cout << "Invalid role.\n";
                return;
            }

            user.setRole(static_cast<Role>(newRole - 1));
            cout << "Role updated successfully.\n";
            return;
        }
    }
    cout << "User not found.\n";
}

void UserManager::deleteUser() {
    string id;
    cout << "Enter user ID to delete: ";
    cin >> id;

    for (auto it = users->begin(); it != users->end(); ++it) {
        if (it->getId() == id) {
            users->erase(it);
            cout << "User deleted successfully.\n";
            return;
        }
    }
    cout << "User not found.\n";
}
