#pragma once
#include "Order.h"
#include "BookManager.h"
#include "User.h"
#include <vector>
#include <string>
using namespace std;

class OrderManager {
private:
    vector<Order> orders;
    BookManager* bookManager;
    string ordersFileName;

    void loadOrdersFromFile();
    void saveOrdersToFile() const;
    void displayOrderDetails(const Order& order) const;

public:
    OrderManager(BookManager* bm);
    ~OrderManager();

    // Customer operations
    void borrowBook(const User& currentUser);
    void returnBook(const User& currentUser);
    void buyBook(const User& currentUser);
    void viewOrderHistory(const User& currentUser) const;

    // Utility methods
    vector<Order> getActiveOrders(const string& userId) const;
    vector<Order> getUserOrders(const string& userId) const;
    bool hasActiveOrderForBook(const string& userId, int bookId) const;

    // Helper methods for input
    int getIntInput(const string& prompt, bool allowZero = false) const;
    char getCharInput(const string& prompt, const string& validChars = "yn") const;
    string getStringLineInput(const string& prompt) const;
};