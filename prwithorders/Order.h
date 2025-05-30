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
    int type; 
    int status; 
    string orderDate;
    string returnDate;
    double totalPrice;
    string bookFormat; 

public:
    Order();
    Order(const string& userId, int bookId, int type, const string& bookFormat = "", double price = 0.0);

    int getOrderId() const { return orderId; }
    string getUserId() const { return userId; }
    int getBookId() const { return bookId; }
    int getType() const { return type; }
    int getStatus() const { return status; }
    string getOrderDate() const { return orderDate; }
    string getReturnDate() const { return returnDate; }
    double getTotalPrice() const { return totalPrice; }
    string getBookFormat() const { return bookFormat; }

    void setStatus(int newStatus) { status = newStatus; }
    void setReturnDate(const string& date) { returnDate = date; }

    string getTypeString() const;
    string getStatusString() const;
    string getCurrentDate() const;
    bool canBeReturned() const;

    friend ostream& operator<<(ostream& os, const Order& order);
    friend istream& operator>>(istream& is, Order& order);
};