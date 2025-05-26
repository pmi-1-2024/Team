#pragma once
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Book {
private:
    int id;
    string title;
    string authorName; 
    string publisherName; 
    vector<string> genreNames; 
    double rating;
    string format;

public:
    Book();

    void setId(int newId);
    void setTitle(const string& newTitle);
    void setAuthorName(const string& newAuthorName); 
    void setPublisherName(const string& newPublisherName); 
    void setRating(double newRating);
    void setFormat(const string& newFormat);
    void setGenreNames(const vector<string>& genres); 

    int getId() const;
    const string& getTitle() const;
    const string& getAuthorName() const; 
    const string& getPublisherName() const; 
    const vector<string>& getGenreNames() const; 
    double getRating() const;
    const string& getFormat() const;


    string getGenreNamesCSV() const; 

    friend istream& operator>>(istream& is, Book& b);
    friend ostream& operator<<(ostream& os, const Book& b);
};