#include "BookManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

BookManager::BookManager(vector<Book>* bookList, vector<Author>* authorList, vector<Genre>* genreList, vector<Publisher>* publisherList)
    : books(bookList), authors(authorList), genres(genreList), publishers(publisherList) {
    loadBooks();
}

void BookManager::loadBooks() {
    ifstream inFile("books.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, authorId, title, publisherId;
        int year, pages, format;
        string genreStr;

        if (!(iss >> id >> authorId >> year >> title >> pages >> genreStr >> publisherId >> format)) continue;

        vector<string> genreIds;
        istringstream genreStream(genreStr);
        string g;
        while (getline(genreStream, g, ',')) genreIds.push_back(g);

        books->push_back(Book(id, authorId, year, title, pages, genreIds, publisherId, format));
    }
}

void BookManager::saveBooks() {
    ofstream outFile("books.txt");
    for (const auto& b : *books) {
        outFile << b.getId() << " "
            << b.getAuthorId() << " "
            << b.getYear() << " "
            << b.getTitle() << " "
            << b.getPages() << " ";

        const auto& g = b.getGenreIds();
        for (size_t i = 0; i < g.size(); ++i) {
            outFile << g[i];
            if (i != g.size() - 1) outFile << ",";
        }

        outFile << " " << b.getPublisherId() << " "
            << b.getFormat() << endl;
    }
}

void BookManager::viewBooks() {
    cout << "\n===== BOOKS =====\n";
    for (const auto& b : *books) {
        cout << "ID: " << b.getId()
            << " | Title: " << b.getTitle()
            << " | Year: " << b.getYear()
            << " | Pages: " << b.getPages()
            << " | Format: " << (b.getFormat() == 0 ? "Printed" : "Digital")
            << endl;
    }
}

void BookManager::addBook() {
    string id, authorId, title, publisherId;
    int year, pages, format;
    string genreStr;

    cout << "Enter book ID: ";
    cin >> id;
    cout << "Enter author ID: ";
    cin >> authorId;
    cout << "Enter publication year: ";
    cin >> year;
    cout << "Enter title (one word or use _): ";
    cin >> title;
    cout << "Enter number of pages: ";
    cin >> pages;
    cout << "Enter genre IDs (comma-separated): ";
    cin >> genreStr;
    cout << "Enter publisher ID: ";
    cin >> publisherId;
    cout << "Enter format (0 - Printed, 1 - Digital): ";
    cin >> format;

    vector<string> genreIds;
    istringstream genreStream(genreStr);
    string g;
    while (getline(genreStream, g, ',')) genreIds.push_back(g);

    books->push_back(Book(id, authorId, year, title, pages, genreIds, publisherId, format));
    saveBooks();
    cout << "Book added.\n";
}
