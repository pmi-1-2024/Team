#pragma once 

#include <string>
#include <vector>
#include <iostream>
#include <sstream> 
#include <limits>  
#include <algorithm> 

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

    int year = 0;
    double paperPrice = 0.0;
    double electronicPrice = 0.0;
    bool available = true;


public:
    Book();

    Book(int id, const string& title, int authorId, int publisherId,
        const vector<int>& genreIds, double rating, const string& format,
        int year, double paperPrice, double electronicPrice, bool available = true);

    int getId() const;
    const string& getTitle() const;
    int getAuthorId() const;
    int getPublisherId() const;
    const vector<int>& getGenreIds() const;
    double getRating() const;
    const string& getFormat() const;
    int getYear() const;
    double getPaperPrice() const;
    double getElectronicPrice() const;
    bool isAvailable() const;


    void setId(int newId);
    void setTitle(const string& newTitle);
    void setAuthorId(int newAuthorId);
    void setPublisherId(int newPublisherId);
    void setRating(double newRating);
    void setFormat(const string& newFormat);
    void setGenreIds(const vector<int>& genres);
    void setYear(int newYear);
    void setPaperPrice(double price);
    void setElectronicPrice(double price);
    void setAvailable(bool avail);

    void displayInfo(const class BookManager& bookManager) const;

    friend istream& operator>>(istream& is, Book& b);
    friend ostream& operator<<(ostream& os, const Book& b);
};