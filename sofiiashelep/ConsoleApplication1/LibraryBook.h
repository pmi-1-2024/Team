#pragma once
#include <string>
#include <iostream>
using namespace std;

class LibraryBook {
private:
    int libraryID;
    int bookID;
    int quantity;
public:
    LibraryBook(int libraryID, int bookID, int quantity)
        : libraryID(libraryID), bookID(bookID), quantity(quantity) {
    }

    int getLibraryID() const { return libraryID; }
    int getBookID() const { return bookID; }
    int getQuantity() const { return quantity; }
    void setLibraryID(int newLibraryID) { libraryID = newLibraryID; }
    void setBookID(int newBookID) { bookID = newBookID; }
    void setQuantity(int newQuantity) { quantity = newQuantity; }
    void addQuantity(int amount) { quantity += amount; }
    void removeQuantity(int amount) { quantity -= amount; }
    bool isAvailable() const { return quantity > 0; }
    void borrowBook() { if (isAvailable()) removeQuantity(1); }
    void returnBook() { addQuantity(1); }
    void printInfo() const {
        cout << "Library ID: " << libraryID << ", Book ID: " << bookID << ", Quantity: " << quantity << endl;
    }
};