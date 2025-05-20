#include <iostream>
#include "DataManager.h"
using namespace std;

void showAdminMenu(DataManager& dataManager);
void showLibrarianMenu(DataManager& dataManager);
void showUserMenu(DataManager& dataManager, User& user);

int main() {
    DataManager dataManager;
    dataManager.loadData();

    string email, password;
    cout << "Email: ";
    cin >> email;
    cout << "Password: ";
    cin >> password;

    User* user = dataManager.loginUser(email, password);
    if (user) {
        cout << "Welcome, " << user->getName() << "!\n";
        if (user->getRole() == "Admin") {
            showAdminMenu(dataManager);
        }
        else if (user->getRole() == "Librarian") {
            showLibrarianMenu(dataManager);
        }
        else if (user->getRole() == "User") {
            showUserMenu(dataManager, *user);
        }
    }
    else {
        cout << "Invalid credentials.\n";
    }

    dataManager.saveData();
    return 0;
}

void showAdminMenu(DataManager& dataManager) {
    int choice;
    do {
        cout << "Admin Menu:\n";
        cout << "1. Change User Role\n";
        cout << "2. View All Users\n";
        cout << "3. Add Library\n";
        cout << "4. View Libraries\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int userID;
            string newRole;
            cout << "Enter User ID: ";
            cin >> userID;
            cout << "Enter New Role (Admin, Librarian, User): ";
            cin >> newRole;

            for (auto& user : dataManager.getUsers()) {
                if (user.getId() == userID) {
                    user.setRole(newRole);
                    cout << "User role updated successfully.\n";
                    break;
                }
            }
            break;
        }
        case 2: {
            cout << "Users:\n";
            for (const auto& user : dataManager.getUsers()) {
                cout << user.getId() << " " << user.getSurname() << " " << user.getName() << " " << user.getRole() << " " << user.getEmail() << "\n";
            }
            break;
        }
        case 3: {
            int id;
            string name, address;
            cout << "Enter Library ID: ";
            cin >> id;
            cout << "Enter Library Name: ";
            cin >> name;
            cout << "Enter Library Address: ";
            cin >> address;
            dataManager.getLibraries().emplace_back(id, name, address);
            cout << "Library added successfully.\n";
            break;
        }
        case 4: {
            cout << "Libraries:\n";
            for (const auto& library : dataManager.getLibraries()) {
                cout << library.getID() << " " << library.getName() << " " << library.getAddress() << "\n";
            }
            break;
        }
        case 5:
            cout << "Exiting Admin Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void showLibrarianMenu(DataManager& dataManager) {
    int choice;
    do {
        cout << "Librarian Menu:\n";
        cout << "1. Add Book\n";
        cout << "2. View All Books\n";
        cout << "3. Add Book to Library\n";
        cout << "4. View Orders\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id, authorID, year, pageCount, publisherID;
            string title, format;
            cout << "Enter Book ID: ";
            cin >> id;
            cout << "Enter Author ID: ";
            cin >> authorID;
            cout << "Enter Year: ";
            cin >> year;
            cout << "Enter Title: ";
            cin >> title;
            cout << "Enter Page Count: ";
            cin >> pageCount;

            string genre;
            cout << "Enter Genre: ";
            cin >> genre;

            cout << "Enter Publisher ID: ";
            cin >> publisherID;
            cout << "Enter Format (Physical/Digital): ";
            cin >> format;

            dataManager.getBooks().emplace_back(id, title, authorID, genre, year, pageCount, publisherID, format);
            cout << "Book added successfully.\n";
            break;
        }
        case 2: {
            cout << "Books:\n";
            for (const auto& book : dataManager.getBooks()) {
                cout << book.getId() << " " << book.getTitle() << " by Author ID " << book.getAuthorID()
                    << " (" << book.getYear() << ")\n";
            }
            break;
        }
        case 3: {
            int libraryID, bookID, quantity;
            cout << "Enter Library ID: ";
            cin >> libraryID;
            cout << "Enter Book ID: ";
            cin >> bookID;
            cout << "Enter Quantity: ";
            cin >> quantity;

            dataManager.getLibraryBooks().emplace_back(libraryID, bookID, quantity);
            cout << "Book added to library successfully.\n";
            break;
        }
        case 4: {
            cout << "Orders:\n";
            for (const auto& order : dataManager.getOrders()) {
                cout << order.getID() << " Book ID: " << order.getBookID() << " User ID: " << order.getUserID()
                    << " Borrow Date: " << order.getBorrowDate() << " Return Date: " << order.getReturnDate() << "\n";
            }
            break;
        }
        case 5:
            cout << "Exiting Librarian Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void showUserMenu(DataManager& dataManager, User& user) {
    int choice;
    do {
        cout << "User Menu:\n";
        cout << "1. View My Books\n";
        cout << "2. View Borrow History\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "My Books:\n";
            for (const auto& order : dataManager.getOrders()) {
                if (order.getUserID() == user.getId()) {
                    cout << "Book ID: " << order.getBookID() << " Borrow Date: " << order.getBorrowDate()
                        << " Return Date: " << order.getReturnDate() << "\n";
                }
            }
            break;
        }
        case 2: {
            cout << "Borrow History:\n";
            for (const auto& order : dataManager.getOrders()) {
                if (order.getUserID() == user.getId()) {
                    cout << "Order ID: " << order.getID() << " Book ID: " << order.getBookID()
                        << " Borrow Date: " << order.getBorrowDate() << " Return Date: " << order.getReturnDate() << "\n";
                }
            }
            break;
        }
        case 3:
            cout << "Exiting User Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}