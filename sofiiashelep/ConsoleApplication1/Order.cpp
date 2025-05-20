#include "Order.h"

Order::Order(int id, int bookID, int userID, const std::string& borrowDate, const std::string& returnDate)
    : ID(id), bookID(bookID), userID(userID), borrowDate(borrowDate), returnDate(returnDate) {
}
