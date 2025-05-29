#pragma once
#include <string>
using namespace std;

class LibraryBook {
private:
    string libraryId;
    string bookId;
    int quantity;

public:
    LibraryBook() = default;
    LibraryBook(string libraryId, string bookId, int quantity);

    string getLibraryId() const;
    string getBookId() const;
    int getQuantity() const;
};
