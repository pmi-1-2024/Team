#include "LibraryBookManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

LibraryBookManager::LibraryBookManager(vector<LibraryBook>* lbList, vector<Book>* bookList)
    : libraryBooks(lbList), books(bookList) {
    loadLibraryBooks();
}

void LibraryBookManager::loadLibraryBooks() {
    ifstream inFile(filename);
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string libId, bookId;
        int quantity;
        if (iss >> libId >> bookId >> quantity) {
            libraryBooks->push_back(LibraryBook(libId, bookId, quantity));
        }
    }
}

void LibraryBookManager::saveLibraryBooks() {
    ofstream outFile(filename);
    for (const auto& lb : *libraryBooks) {
        outFile << lb.getLibraryId() << " " << lb.getBookId() << " " << lb.getQuantity() << endl;
    }
}

void LibraryBookManager::addBookToLibrary() {
    string libId, bookId;
    int quantity;

    cout << "Enter library ID: ";
    cin >> libId;
    cout << "Enter book ID: ";
    cin >> bookId;
    cout << "Enter quantity: ";
    cin >> quantity;

    libraryBooks->push_back(LibraryBook(libId, bookId, quantity));
    saveLibraryBooks();
    cout << "Book added to library.\n";
}

void LibraryBookManager::viewLibraryBooks(const string& libraryId) {
    cout << "\nBooks in library [" << libraryId << "]:\n";
    for (const auto& lb : *libraryBooks) {
        if (lb.getLibraryId() == libraryId) {
            cout << "Book ID: " << lb.getBookId()
                << " | Quantity: " << lb.getQuantity() << endl;
        }
    }
}
