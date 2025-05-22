#include "LibraryBook.h"
using namespace std;

LibraryBook::LibraryBook(string libraryId, string bookId, int quantity)
    : libraryId(libraryId), bookId(bookId), quantity(quantity) {
}

string LibraryBook::getLibraryId() const { return libraryId; }
string LibraryBook::getBookId() const { return bookId; }
int LibraryBook::getQuantity() const { return quantity; }
