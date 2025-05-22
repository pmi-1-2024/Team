#pragma once
#include <string>
using namespace std;

class Order {
private:
    string id;
    string userId;
    string bookId;
    string libraryId;
    string dateIssued;
    string dateReturned;

public:
    Order() = default;
    Order(string id, string userId, string bookId, string libraryId, string dateIssued, string dateReturned = "");

    string getId() const;
    string getUserId() const;
    string getBookId() const;
    string getLibraryId() const;
    string getIssueDate() const;
    string getReturnDate() const;

    void setReturnDate(string date);
};
