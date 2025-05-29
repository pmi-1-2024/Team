#pragma once

#include "Book.h"   
#include "Author.h"
#include "Publisher.h"
#include "Genre.h"
#include <vector>
#include <string>
#include <iostream> 
#include <fstream>  
#include <sstream>  
#include <limits>   
#include <algorithm> 

using namespace std;

const string BOOKS_FILE_BM = "books.txt";
const string AUTHORS_FILE_BM = "authors.txt";
const string PUBLISHERS_FILE_BM = "publishers.txt";
const string GENRES_FILE_BM = "genres.txt";

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

    int getIntInput(const string& prompt, bool allowZero = false) const;
    double getDoubleInput(const string& prompt) const;
    string getStringLineInput(const string& prompt) const;
    char getCharInput(const string& prompt, const string& validChars = "yn") const;

public:
    BookManager();
    ~BookManager();

    void run();

    void addBook();
    void viewBooks() const;
    Book* findBookById(int bookId);
    const Book* findBookById(int bookId) const;
    void modifyBook();
    void removeBook();
    void setBookAvailability(int bookId, bool available);

    void addAuthor(); void viewAuthors() const; void modifyAuthor(); void removeAuthor();
    void addPublisher(); void viewPublishers() const; void modifyPublisher(); void removePublisher();
    void addGenre(); void viewGenres() const; void modifyGenre(); void removeGenre();

    int displayMainMenu() const;

    string getAuthorNameById(int authorId) const;
    string getPublisherNameById(int publisherId) const;
    string getGenreNameById(int genreId) const;
    bool authorExists(int authorId) const;
    bool publisherExists(int publisherId) const;
    bool genreExists(int genreId) const;

    const vector<Book>& getAllBooks() const;
};