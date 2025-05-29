#pragma once

#include "Order.h"
#include "BookManager.h"
#include "User.h"
#include <vector>
#include <string>

using namespace std;

const string ORDERS_FILE = "orders.txt";

class OrderManager {
private:
    vector<Order> orders;
    BookManager* bookManager;

    void loadOrdersFromFile();
    void saveOrdersToFile() const;
    void displayOrderDetails(const Order& order) const;

public:
    OrderManager(BookManager* bm);
    ~OrderManager();

    void borrowBook(const User& currentUser);
    void returnBook(const User& currentUser);
    void buyBook(const User& currentUser);
    void viewOrderHistory(const User& currentUser) const;

    vector<Order> getActiveOrders(const string& userId) const;
    vector<Order> getUserOrders(const string& userId) const;
    bool hasActiveOrderForBook(const string& userId, int bookId) const;

    int getIntInput(const string& prompt, bool allowZero = false) const;
    char getCharInput(const string& prompt, const string& validChars = "yn") const;
    string getStringLineInput(const string& prompt) const;
};
