#pragma once
#include "LibraryBook.h"
#include "Book.h"
#include <vector>
#include <string>
using namespace std;

class LibraryBookManager {
private:
    vector<LibraryBook>* libraryBooks;
    vector<Book>* books;
    string filename = "librarybooks.txt";

public:
    LibraryBookManager(vector<LibraryBook>* lbList, vector<Book>* bookList);
    void loadLibraryBooks();
    void saveLibraryBooks();
    void addBookToLibrary();
    void viewLibraryBooks(const string& libraryId);
};
