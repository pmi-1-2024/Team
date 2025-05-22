#include "Book.h"
#include <vector>
#include <iostream>
#include <string>
#include <limits>
#include <sstream> 

Book::Book() : id(0), rating(0.0), authorName(""), publisherName(""), format("Paper") {}

void Book::setId(int newId) { id = newId; }
void Book::setTitle(const string& newTitle) { title = newTitle; }
void Book::setAuthorName(const string& newAuthorName) { authorName = newAuthorName; } 
void Book::setPublisherName(const string& newPublisherName) { publisherName = newPublisherName; } 
void Book::setRating(double newRating) { rating = newRating; }
void Book::setFormat(const string& newFormat) { format = newFormat; }
void Book::setGenreNames(const vector<string>& genres) { genreNames = genres; } 

int Book::getId() const { return id; }
const string& Book::getTitle() const { return title; }
const string& Book::getAuthorName() const { return authorName; } 
const string& Book::getPublisherName() const { return publisherName; } 
const vector<string>& Book::getGenreNames() const { return genreNames; } 
double Book::getRating() const { return rating; }
const string& Book::getFormat() const { return format; }

string Book::getGenreNamesCSV() const { 
    string res;
    if (!genreNames.empty()) {
        for (size_t i = 0; i < genreNames.size(); ++i) {
            res += genreNames[i];
            if (i < genreNames.size() - 1) {
                res += ";";
            }
        }
    }
    return res;
}

istream& operator>>(istream& is, Book& b) {
    if (!(is >> b.id)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!getline(is, b.title)) return is;

    if (!getline(is, b.authorName)) return is;
    if (!getline(is, b.publisherName)) return is;

    int genre_count = 0;
    if (!(is >> genre_count)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    b.genreNames.clear(); 
    if (is && genre_count > 0) {
        b.genreNames.reserve(genre_count);
        for (int i = 0; i < genre_count; ++i) {
            string genre_name_val;
            if (!getline(is, genre_name_val)) { 
                return is;
            }
            b.genreNames.push_back(genre_name_val);
        }
    }
    else if (genre_count > 0 && !is) {
        return is;
    }

    if (!(is >> b.rating)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!getline(is, b.format)) return is;

    return is;
}

ostream& operator<<(ostream& os, const Book& b) {
    os << b.id << "\n";
    os << b.title << "\n";
    os << b.authorName << "\n"; 
    os << b.publisherName << "\n"; 
    os << b.genreNames.size() << "\n";
    for (const string& genre_name : b.genreNames) { 
        os << genre_name << "\n";
    }
    os << b.rating << "\n";
    os << b.format << "\n";
    return os;
}