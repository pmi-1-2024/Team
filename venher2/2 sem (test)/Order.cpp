#include "Order.h"

Order::Order(string id, string userId, string bookId, string libraryId, string dateIssued, string dateReturned)
    : id(id), userId(userId), bookId(bookId), libraryId(libraryId), dateIssued(dateIssued), dateReturned(dateReturned) {
}

string Order::getId() const { return id; }
string Order::getUserId() const { return userId; }
string Order::getBookId() const { return bookId; }
string Order::getLibraryId() const { return libraryId; }
string Order::getIssueDate() const { return dateIssued; }
string Order::getReturnDate() const { return dateReturned; }

void Order::setReturnDate(string date) {
    dateReturned = date;
}
