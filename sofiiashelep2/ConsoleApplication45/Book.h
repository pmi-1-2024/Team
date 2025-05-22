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
    string publisher;
    vector<int> genreIds;
    double rating;
    string format;
    string genre;
    double paperPrice;
    double electronicPrice;
    bool available;
    string author;
    int year;

public:
    Book();
    Book(int id, const string& title, const string& author, const string& genre, const string& publisher, int year, double paperPrice, double electronicPrice, bool available = true) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->authorId = 0;
        this->publisherId = 0;
        this->genreIds = {};
        this->rating = 0.0;
        this->format = "";
        this->paperPrice = paperPrice;
        this->electronicPrice = electronicPrice;
        this->available = available;
        this->genre = genre;
        this->year = year;
    }

    const string& getAuthor() const {
        return author;
    }

    void setId(int newId);
    void setTitle(const string& newTitle);
    void setAuthorId(int newAuthorId);
    void setPublisherId(int newPublisherId);
    void setRating(double newRating);
    void setFormat(const string& newFormat);
    void displayInfo() const;
    int getYear() const { return year; }

    int getId() const;
    const string& getTitle() const;
    int getAuthorId() const;
    int getPublisherId() const;
    const vector<int>& getGenreIds() const;
    double getRating() const;
    const string& getFormat() const;
    const string& getGenre() const {
        return genre;
    }
    const string& getPublisher() const {
        return publisher;
    }
    bool isAvailable() const {
        return available;
    }

    void setAvailable(bool isAvailable) { 
        available = isAvailable;
    }

    int getAuthorID() const;
    int getPublisherID() const;
    vector<int> getGenreIDs() const;

    void setGenreIds(const vector<int>& genres);
    string getGenreIdCSV() const;

    double getPaperPrice() const { return paperPrice; }
    double getElectronicPrice() const { return electronicPrice; }

    friend istream& operator>>(istream& is, Book& b);
    friend ostream& operator<<(ostream& os, const Book& b);
};
