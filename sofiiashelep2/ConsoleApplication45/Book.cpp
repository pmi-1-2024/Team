#include "Book.h"
#include <vector>
#include <iostream>
#include <string>
#include <limits>  


Book::Book() : id(0), rating(0.0), authorId(0), publisherId(0), format("Paper") {}

void Book::setId(int newId) { id = newId; }
void Book::setTitle(const string& newTitle) { title = newTitle; }
void Book::setAuthorId(int newAuthorId) { authorId = newAuthorId; }
void Book::setPublisherId(int newPublisherId) { publisherId = newPublisherId; }
void Book::setRating(double newRating) { rating = newRating; }
void Book::setFormat(const string& newFormat) { format = newFormat; }
void Book::setGenreIds(const vector<int>& genres) { genreIds = genres; }

int Book::getId() const { return id; }
const string& Book::getTitle() const { return title; }
int Book::getAuthorId() const { return authorId; }
int Book::getPublisherId() const { return publisherId; }
const vector<int>& Book::getGenreIds() const { return genreIds; }
double Book::getRating() const { return rating; }
const string& Book::getFormat() const { return format; }

int Book::getAuthorID() const { return getAuthorId(); }
int Book::getPublisherID() const { return getPublisherId(); }
vector<int> Book::getGenreIDs() const { return getGenreIds(); }

string Book::getGenreIdCSV() const {
    string res;
    if (!genreIds.empty()) {
        for (size_t i = 0; i < genreIds.size(); ++i) {
            res += to_string(genreIds[i]);
            if (i < genreIds.size() - 1) {
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

    if (!(is >> b.authorId)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    if (!(is >> b.publisherId)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    int genre_count = 0;
    if (!(is >> genre_count)) return is;
    is.ignore(numeric_limits<streamsize>::max(), '\n');

    b.genreIds.clear();
    if (is && genre_count > 0) {
        b.genreIds.reserve(genre_count);
        for (int i = 0; i < genre_count; ++i) {
            int genre_id_val;
            if (!(is >> genre_id_val)) {
                return is;
            }
            is.ignore(numeric_limits<streamsize>::max(), '\n');
            b.genreIds.push_back(genre_id_val);
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
    os << b.authorId << "\n";
    os << b.publisherId << "\n";
    os << b.genreIds.size() << "\n";
    for (int genre_id : b.genreIds) {
        os << genre_id << "\n";
    }
    os << b.rating << "\n";
    os << b.format << "\n";
    return os;
}