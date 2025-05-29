#include "Order.h"
#include <chrono>
#include <iomanip>
#include <sstream>
#include <limits>
#include <ctime>

int Order::nextOrderId = 1;

Order::Order() : orderId(0), userId(""), bookId(0), type(OrderType::BORROW),
status(OrderStatus::ACTIVE), orderDate(""), returnDate(""),
totalPrice(0.0), bookFormat("Paper") {
}

Order::Order(const string& userId, int bookId, OrderType type, const string& bookFormat, double price)
    : orderId(nextOrderId++), userId(userId), bookId(bookId), type(type),
    status(OrderStatus::ACTIVE), returnDate(""), totalPrice(price), bookFormat(bookFormat) {
    orderDate = getCurrentDate();
    if (type == OrderType::PURCHASE) {
        status = OrderStatus::COMPLETED;
    }
}

string Order::getTypeString() const {
    switch (type) {
    case OrderType::BORROW: return "Borrow";
    case OrderType::PURCHASE: return "Purchase";
    default: return "Unknown";
    }
}

string Order::getStatusString() const {
    switch (status) {
    case OrderStatus::ACTIVE: return "Active";
    case OrderStatus::RETURNED: return "Returned";
    case OrderStatus::COMPLETED: return "Completed";
    default: return "Unknown";
    }
}

string Order::getCurrentDate() const {
    auto now = chrono::system_clock::now();
    auto time_t = chrono::system_clock::to_time_t(now);

    stringstream ss;

#ifdef _WIN32
    struct tm timeStruct;
    localtime_s(&timeStruct, &time_t);
    ss << put_time(&timeStruct, "%Y-%m-%d %H:%M:%S");
#else
    struct tm* timeStruct = localtime(&time_t);
    ss << put_time(timeStruct, "%Y-%m-%d %H:%M:%S");
#endif

    return ss.str();
}

bool Order::canBeReturned() const {
    return (type == OrderType::BORROW && status == OrderStatus::ACTIVE);
}

ostream& operator<<(ostream& os, const Order& order) {
    os << order.orderId << "\n"
        << order.userId << "\n"
        << order.bookId << "\n"
        << static_cast<int>(order.type) << "\n"
        << static_cast<int>(order.status) << "\n"
        << order.orderDate << "\n"
        << order.returnDate << "\n"
        << order.totalPrice << "\n"
        << order.bookFormat << "\n";
    return os;
}

istream& operator>>(istream& is, Order& order) {
    int typeInt, statusInt;

    if (!(is >> order.orderId)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!getline(is, order.userId)) return is;

    if (!(is >> order.bookId)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!(is >> typeInt)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    order.type = static_cast<OrderType>(typeInt);

    if (!(is >> statusInt)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');
    order.status = static_cast<OrderStatus>(statusInt);

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