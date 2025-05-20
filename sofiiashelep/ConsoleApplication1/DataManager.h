#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Genre.h"
#include "Library.h"
#include "LibraryBook.h"
#include "Order.h"
using namespace std;

class DataManager {
private:
    vector<User> users;
    vector<Book> books;
    vector<Author> authors;
    vector<Publisher> publishers;
    vector<Genre> genres;
    vector<Library> libraries;
    vector<LibraryBook> libraryBooks;
    vector<Order> orders;

public:
    void loadData();
    void saveData();
    bool registerUser(const User& user);
    User* loginUser(const string& email, const string& password);

    vector<User>& getUsers() { return users; }
    vector<Library>& getLibraries() { return libraries; }
    vector<Book>& getBooks() { return books; }
    vector<Order>& getOrders() { return orders; }
    vector<LibraryBook>& getLibraryBooks() { return libraryBooks; }
};