#include "Book.h"

Book::Book(string id, string authorId, int year, string title, int pages,
    vector<string> genreIds, string publisherId, int format)
    : id(id), authorId(authorId), year(year), title(title), pages(pages),
    genreIds(genreIds), publisherId(publisherId), format(format) {
}

string Book::getId() const { return id; }
string Book::getAuthorId() const { return authorId; }
int Book::getYear() const { return year; }
string Book::getTitle() const { return title; }
int Book::getPages() const { return pages; }
vector<string> Book::getGenreIds() const { return genreIds; }
string Book::getPublisherId() const { return publisherId; }
int Book::getFormat() const { return format; }

bool Book::operator==(const Book& other) const {
    return id == other.id;
}
