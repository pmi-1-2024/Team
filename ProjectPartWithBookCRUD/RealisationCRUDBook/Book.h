#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std; 

class Book {
private:
    int id;
    string title;
    int authorId;
    int publisherId;
    vector<int> genreIds;
    double rating;
    string format; 

public:
    Book();

    void setId(int newId);
    void setTitle(const string& newTitle);
    void setAuthorId(int newAuthorId);
    void setPublisherId(int newPublisherId);
    void setRating(double newRating);
    void setFormat(const string& newFormat);

    int getId() const;
    const string& getTitle() const;
    int getAuthorId() const;
    int getPublisherId() const;
    const vector<int>& getGenreIds() const;
    double getRating() const;
    const string& getFormat() const;

    int getAuthorID() const; 
    int getPublisherID() const;
    vector<int> getGenreIDs() const;

    void setGenreIds(const vector<int>& genres);
    string getGenreIdCSV() const;

    friend istream& operator>>(istream& is, Book& b);
    friend ostream& operator<<(ostream& os, const Book& b);
};