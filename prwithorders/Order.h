#pragma once

#include <string>
#include <iostream>
#include <vector>
#include "Book.h"

using namespace std;

enum class OrderType {
    BORROW,
    PURCHASE
};

enum class OrderStatus {
    ACTIVE,
    RETURNED,
    COMPLETED
};

class Order {
private:
    static int nextOrderId;
    int orderId;
    string userId;
    int bookId;
    OrderType type;
    OrderStatus status;
    string orderDate;
    string returnDate;
    double totalPrice;
    string bookFormat; 

public:
    Order();
    Order(const string& userId, int bookId, OrderType type, const string& bookFormat = "", double price = 0.0);

    int getOrderId() const { return orderId; }
    string getUserId() const { return userId; }
    int getBookId() const { return bookId; }
    OrderType getType() const { return type; }
    OrderStatus getStatus() const { return status; }
    string getOrderDate() const { return orderDate; }
    string getReturnDate() const { return returnDate; }
    double getTotalPrice() const { return totalPrice; }
    string getBookFormat() const { return bookFormat; }

    void setStatus(OrderStatus newStatus) { status = newStatus; }
    void setReturnDate(const string& date) { returnDate = date; }

    string getTypeString() const;
    string getStatusString() const;
    string getCurrentDate() const;
    bool canBeReturned() const;

    friend ostream& operator<<(ostream& os, const Order& order);
    friend istream& operator>>(istream& is, Order& order);
};
