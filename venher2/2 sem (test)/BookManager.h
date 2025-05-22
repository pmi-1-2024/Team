#pragma once
#include "Book.h"
#include "Author.h"
#include "Genre.h"
#include "Publisher.h"
#include <vector>
#include <string>

class BookManager {
private:
    vector<Book>* books;
    vector<Author>* authors;
    vector<Genre>* genres;
    vector<Publisher>* publishers;
    string filename = "books.txt";

public:
    BookManager(vector<Book>* b, vector<Author>* a, vector<Genre>* g, vector<Publisher>* p);

    void loadBooks();
    void saveBooks();

    void addBook();
    void viewBooks();
};
