#pragma once
#include <string>
using namespace std;

class LibraryBook
{
private:
	string title;
	string author;
	int publicationYear;
	int libraryId;
	int genreId;
	int publisherId;
	int quantity;
public:
	LibraryBook(string title, string author, int publicationYear, int libraryId, int genreId, int publisherId, int quantity)
		: title(title), author(author), publicationYear(publicationYear), libraryId(libraryId), genreId(genreId), publisherId(publisherId), quantity(quantity) {
	}
	string getTitle() const { return title; }
	string getAuthor() const { return author; }
	int getPublicationYear() const { return publicationYear; }
	int getLibraryId() const { return libraryId; }
	int getGenreId() const { return genreId; }
	int getPublisherId() const { return publisherId; }
	int getQuantity() const { return quantity; }
	void setTitle(const string& newTitle) { title = newTitle; }
	void setAuthor(const string& newAuthor) { author = newAuthor; }
	void setPublicationYear(int newPublicationYear) { publicationYear = newPublicationYear; }
	void setLibraryId(int newLibraryId) { libraryId = newLibraryId; }
	void setGenreId(int newGenreId) { genreId = newGenreId; }
	void setPublisherId(int newPublisherId) { publisherId = newPublisherId; }
	void setQuantity(int newQuantity) { quantity = newQuantity; }
};

