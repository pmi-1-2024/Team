#include "Order.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <limits>
#include <ctime>

int Order::nextOrderId = 1;

Order::Order() : orderId(0), userId(""), bookId(0), type(0),
status(0), orderDate(""), returnDate(""),
totalPrice(0.0), bookFormat("Paper") {
}

Order::Order(const string& userId, int bookId, int type, const string& bookFormat, double price)
    : orderId(nextOrderId++), userId(userId), bookId(bookId), type(type),
    status(0), returnDate(""), totalPrice(price), bookFormat(bookFormat) {
    orderDate = getCurrentDate();
    if (type == 1) { 
        status = 2; 
    }
}

string Order::getTypeString() const {
    if (type == 0) return "Borrow";
    if (type == 1) return "Purchase";
    return "Unknown";
}

string Order::getStatusString() const {
    if (status == 0) return "Active";
    if (status == 1) return "Returned";
    if (status == 2) return "Completed";
    return "Unknown";
}

string Order::getCurrentDate() const {
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);

    stringstream ss;
    struct tm timeStruct;
    localtime_s(&timeStruct, &time_t);
    ss << put_time(&timeStruct, "%Y-%m-%d %H:%M:%S");

    return ss.str();
}

bool Order::canBeReturned() const {
    return (type == 0 && status == 0); 
}

ostream& operator<<(ostream& os, const Order& order) {
    os << order.orderId << "\n"
        << order.userId << "\n"
        << order.bookId << "\n"
        << order.type << "\n"
        << order.status << "\n"
        << order.orderDate << "\n"
        << order.returnDate << "\n"
        << order.totalPrice << "\n"
        << order.bookFormat << "\n";
    return os;
}

istream& operator>>(istream& is, Order& order) {
    if (!(is >> order.orderId)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!getline(is, order.userId)) return is;
    if (!(is >> order.bookId)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!(is >> order.type)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!(is >> order.status)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!getline(is, order.orderDate)) return is;
    if (!getline(is, order.returnDate)) return is;
    if (!(is >> order.totalPrice)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    if (!getline(is, order.bookFormat)) return is;

    if (order.orderId >= Order::nextOrderId) {
        Order::nextOrderId = order.orderId + 1;
    }
    return is;
}
