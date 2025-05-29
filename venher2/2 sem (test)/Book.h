#pragma once
#include <string>
#include <vector>
using namespace std;

class Book {
private:
    string id;
    string authorId;
    int year;
    string title;
    int pages;
    vector<string> genreIds;
    string publisherId;
    int format;

public:
    Book() = default;

    Book(string id, string authorId, int year, string title, int pages,
        vector<string> genreIds, string publisherId, int format);

    string getId() const;
    string getAuthorId() const;
    int getYear() const;
    string getTitle() const;
    int getPages() const;
    vector<string> getGenreIds() const;
    string getPublisherId() const;
    int getFormat() const;

    bool operator==(const Book& other) const;
};
