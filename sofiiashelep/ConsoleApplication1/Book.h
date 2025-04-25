#pragma once
class Book
{
private:
	int id;
	string title;
	string author;
	string genre;
	int year;
	int pages;
	string publisher;
	string format;
public:
	Book(int id, string title, string author, string genre, int year, int pages, string publisher, string format)
		: id(id), title(title), author(author), genre(genre), year(year), pages(pages), publisher(publisher), format(format) {
	}
	int getId() const { return id; }
	string getTitle() const { return title; }
	string getAuthor() const { return author; }
	string getGenre() const { return genre; }
	int getYear() const { return year; }
	int getPages() const { return pages; }
	string getPublisher() const { return publisher; }
	string getFormat() const { return format; }
	void setTitle(const string& newTitle) { title = newTitle; }
	void setAuthor(const string& newAuthor) { author = newAuthor; }
	void setGenre(const string& newGenre) { genre = newGenre; }
	void setYear(int newYear) { year = newYear; }
	void setPages(int newPages) { pages = newPages; }
	void setPublisher(const string& newPublisher) { publisher = newPublisher; }
	void setFormat(const string& newFormat) { format = newFormat; }
};

