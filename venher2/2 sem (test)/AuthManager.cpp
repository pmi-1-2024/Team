#include "AuthManager.h"
#include "AuthorManager.h"
#include "UserManager.h"
#include "BookManager.h"
#include "GenreManager.h"
#include "PublisherManager.h"
#include "LibraryManager.h"
#include "LibraryBookManager.h"
#include "OrderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

AuthManager::AuthManager() {
    loadUsers();
}

void AuthManager::loadUsers() {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Could not open " << filename << endl;
        return;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, name, surname, email, password;
        int roleInt;
        if (!(iss >> id >> name >> surname >> email >> password >> roleInt)) {
            continue;
        }
        Role role = static_cast<Role>(roleInt);
        users.push_back(User(id, name, surname, email, password, role));
    }
}

void AuthManager::saveUsers() {
    ofstream outFile(filename);
    for (const auto& u : users) {
        outFile << u.getId() << " "
            << u.getFullName().substr(0, u.getFullName().find(' ')) << " "
            << u.getFullName().substr(u.getFullName().find(' ') + 1) << " "
            << u.getEmail() << " "
            << u.getPassword() << " "
            << static_cast<int>(u.getRole()) << endl;
    }
}

bool AuthManager::registerUser() {
    string id, surname, name, email, password;

    cout << "Enter ID (8 digits): ";
    cin >> id;
    if (id.length() != 8) {
        cout << "Invalid ID length.\n";
        return false;
    }

    cout << "Enter surname: ";
    cin >> surname;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    for (auto& u : users) {
        if (u.getEmail() == email) {
            cout << "User with this email already exists.\n";
            return false;
        }
    }

    User newUser(id, name, surname, email, password, Role::USER);
    users.push_back(newUser);
    saveUsers();
    cout << "Registration successful!\n";
    return true;
}

User* AuthManager::loginUser() {
    string email, password;
    cout << "Enter email: ";
    cin >> email;
    cout << "Enter password: ";
    cin >> password;

    for (auto& u : users) {
        if (u.getEmail() == email && u.getPassword() == password) {
            cout << "Login successful! Welcome, " << u.getFullName() << "\n";
            return &u;
        }
    }

    cout << "Invalid email or password.\n";
    return nullptr;
}

void AuthManager::showMainMenu() {
    int choice;
    while (true) {
        cout << "\n==== LIBRARY SYSTEM ====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            registerUser();
        }
        else if (choice == 2) {
            User* user = loginUser();
            if (user) {
                if (user->getRole() == Role::ADMIN) {
                    UserManager um(&users);
                    int choice;
                    while (true) {
                        cout << "\n--- Admin Panel ---\n";
                        cout << "1. Show all users\n";
                        cout << "2. Change user role\n";
                        cout << "3. Delete user\n";
                        cout << "0. Log out\n";
                        cout << "Choice: ";
                        cin >> choice;

                        if (choice == 1) um.showAllUsers();
                        else if (choice == 2) um.changeUserRole();
                        else if (choice == 3) um.deleteUser();
                        else if (choice == 0) break;
                        else cout << "Invalid option.\n";
                    }
                    saveUsers();
                }
                else if (user->getRole() == Role::LIBRARIAN) {
                    vector<Book> books;
                    vector<Author> authors;
                    vector<Genre> genres;
                    vector<Publisher> publishers;
                    vector<Library> libraries;
                    vector<LibraryBook> libraryBooks;
                    vector<Order> orders;

                    BookManager bm(&books, &authors, &genres, &publishers);
                    AuthorManager am(&authors);
                    GenreManager gm(&genres);
                    PublisherManager pm(&publishers);
                    LibraryManager lm(&libraries);
                    LibraryBookManager lbm(&libraryBooks, &books);
                    OrderManager om(&orders, &books);

                    int choice;
                    while (true) {
                        cout << "\n--- Librarian Menu ---\n";
                        cout << "1. View all books\n";
                        cout << "2. Add new book\n";
                        cout << "3. View authors\n";
                        cout << "4. Add author\n";
                        cout << "5. View genres\n";
                        cout << "6. Add genre\n";
                        cout << "7. View publishers\n";
                        cout << "8. Add publisher\n";
                        cout << "9. View libraries\n";
                        cout << "10. Add library\n";
                        cout << "11. Add book to library\n";
                        cout << "12. View books in library\n";
                        cout << "13. View all orders\n";
                        cout << "14. Return a book\n";
                        cout << "0. Logout\n";
                        cout << "Choice: ";
                        cin >> choice;

                        if (choice == 1) bm.viewBooks();
                        else if (choice == 2) bm.addBook();
                        else if (choice == 3) am.viewAuthors();
                        else if (choice == 4) am.addAuthor();
                        else if (choice == 5) gm.viewGenres();
                        else if (choice == 6) gm.addGenre();
                        else if (choice == 7) pm.viewPublishers();
                        else if (choice == 8) pm.addPublisher();
                        else if (choice == 9) lm.viewLibraries();
                        else if (choice == 10) lm.addLibrary();
                        else if (choice == 11) lbm.addBookToLibrary();
                        else if (choice == 12) {
                            string libId;
                            cout << "Enter library ID: ";
                            cin >> libId;
                            lbm.viewLibraryBooks(libId);
                        }
                        else if (choice == 13) om.viewAllOrders();
                        else if (choice == 14) om.returnOrder();
                        else if (choice == 0) break;
                        else cout << "Invalid choice.\n";
                    }
                }
                else if (user->getRole() == Role::USER) {
                    vector<Book> books;
                    vector<Author> authors;
                    vector<Genre> genres;
                    vector<Publisher> publishers;
                    vector<Order> orders;

                    BookManager bm(&books, &authors, &genres, &publishers);
                    OrderManager om(&orders, &books);

                    int choice;
                    while (true) {
                        cout << "\n--- User Menu ---\n";
                        cout << "1. View available books\n";
                        cout << "2. View order history\n";
                        cout << "3. Create new order\n";
                        cout << "0. Logout\n";
                        cout << "Choice: ";
                        cin >> choice;

                        if (choice == 1) bm.viewBooks();
                        else if (choice == 2) om.viewOrdersByUser(user->getId());
                        else if (choice == 3) om.createOrder(user->getId());
                        else if (choice == 0) break;
                        else cout << "Invalid option.\n";
                    }
                }
            }
        }
        else if (choice == 0) break;
        else cout << "Invalid choice.\n";
    }
}
