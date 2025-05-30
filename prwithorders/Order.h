#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "Book.h"
using namespace std;

class Order {
private:
    static int nextOrderId;
    int orderId;
    string userId;
    int bookId;
    int type; // 0 = BORROW, 1 = PURCHASE
    int status; // 0 = ACTIVE, 1 = RETURNED, 2 = COMPLETED
    string orderDate;
    string returnDate;
    double totalPrice;
    string bookFormat; // "Paper" or "Electronic"

public:
    Order();
    Order(const string& userId, int bookId, int type, const string& bookFormat = "", double price = 0.0);

    // Getters
    int getOrderId() const { return orderId; }
    string getUserId() const { return userId; }
    int getBookId() const { return bookId; }
    int getType() const { return type; }
    int getStatus() const { return status; }
    string getOrderDate() const { return orderDate; }
    string getReturnDate() const { return returnDate; }
    double getTotalPrice() const { return totalPrice; }
    string getBookFormat() const { return bookFormat; }

    // Setters
    void setStatus(int newStatus) { status = newStatus; }
    void setReturnDate(const string& date) { returnDate = date; }

    // Utility methods
    string getTypeString() const;
    string getStatusString() const;
    string getCurrentDate() const;
    bool canBeReturned() const;

    // File I/O
    friend ostream& operator<<(ostream& os, const Order& order);
    friend istream& operator>>(istream& is, Order& order);
};