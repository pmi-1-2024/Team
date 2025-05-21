#pragma once

#include <vector>
#include <string>
#include "Book.h"
#include "Author.h"
#include "Publisher.h"
#include "Genre.h"

class BookManager {
private:
    vector<Book> books;
    vector<Author> authors;
    vector<Publisher> publishers;
    vector<Genre> genres;

    void loadAllData();
    void saveAllData() const;

    void saveBooks() const;
    void saveAuthors() const;
    void savePublishers() const;
    void saveGenres() const;

public:
    BookManager();
    ~BookManager(); 

    void run();

    void addBook();
    void viewBooks() const;
    void findBook(); 
    void modifyBook();
    void removeBook();

    void addAuthor();
    void viewAuthors() const;
    void modifyAuthor();
    void removeAuthor();

    void addPublisher();
    void viewPublishers() const;
    void modifyPublisher();
    void removePublisher();

    void addGenre();
    void viewGenres() const;
    void modifyGenre();
    void removeGenre();

    void exportToCSV(const string& filename) const;

    int displayMainMenu() const;

};

