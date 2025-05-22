#include "AuthorManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

AuthorManager::AuthorManager(vector<Author>* authorList)
    : authors(authorList) {
    loadAuthors();
}

void AuthorManager::loadAuthors() {
    ifstream inFile("authors.txt");
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, name, surname;
        if (iss >> id >> name >> surname) {
            authors->push_back(Author(id, name, surname));
        }
    }
}

void AuthorManager::saveAuthors() {
    ofstream outFile("authors.txt");
    for (const auto& a : *authors) {
        outFile << a.getId() << " " << a.getName() << " " << a.getSurname() << endl;
    }
}

void AuthorManager::addAuthor() {
    string id, name, surname;
    cout << "Enter author ID: ";
    cin >> id;
    cout << "Enter name: ";
    cin >> name;
    cout << "Enter surname: ";
    cin >> surname;

    authors->push_back(Author(id, name, surname));
    saveAuthors();
    cout << "Author added successfully.\n";
}

void AuthorManager::viewAuthors() {
    cout << "\n===== AUTHORS =====\n";
    for (const auto& a : *authors) {
        cout << "ID: " << a.getId()
            << " | Name: " << a.getName() << " " << a.getSurname() << endl;
    }
}
