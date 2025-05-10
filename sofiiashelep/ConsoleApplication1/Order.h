#pragma once
class Order
{
private:
	int id;
	int libraryId;
	int bookId;
public:
	Order(int id, int libraryId, int bookId)
		: id(id), libraryId(libraryId), bookId(bookId) {
	}
	int getId() const { return id; }
	int getLibraryId() const { return libraryId; }
	int getBookId() const { return bookId; }
	void setLibraryId(int newLibraryId) { libraryId = newLibraryId; }
	void setBookId(int newBookId) { bookId = newBookId; }
};

