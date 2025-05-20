#pragma once
#include <string>
using namespace std;

class Order {
private:
    int ID;
    int bookID;
    int userID;
    string borrowDate;
    string returnDate;
public:

    Order(int id, int bookID, int userID, const string& borrowDate, const string& returnDate);


    int getID() const { return ID; }
    int getBookID() const { return bookID; }
    int getUserID() const { return userID; }
    string getBorrowDate() const { return borrowDate; }
    string getReturnDate() const { return returnDate; }
};