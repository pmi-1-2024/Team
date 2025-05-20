#pragma once
#include <string>
using namespace std;

class Book {
private:
    int id;
    string title;
    int authorID; 
    string genre;
    int year;
    int pages;
    string publisher;
    string format;
public:
    Book(int id, string title, int authorID, string genre, int year, int pages, string publisher, string format)
        : id(id), title(title), authorID(authorID), genre(genre), year(year), pages(pages), publisher(publisher), format(format) {
    }

    int getId() const { return id; }
    string getTitle() const { return title; }
    int getAuthorID() const { return authorID; }
    string getGenre() const { return genre; }
    int getYear() const { return year; }
    int getPages() const { return pages; }
    string getPublisher() const { return publisher; }
    string getFormat() const { return format; }

    void setTitle(const string& newTitle) { title = newTitle; }
    void setAuthorID(int newAuthorID) { authorID = newAuthorID; }
    void setGenre(const string& newGenre) { genre = newGenre; }
    void setYear(int newYear) { year = newYear; }
    void setPages(int newPages) { pages = newPages; }
    void setPublisher(const string& newPublisher) { publisher = newPublisher; }
    void setFormat(const string& newFormat) { format = newFormat; }
};