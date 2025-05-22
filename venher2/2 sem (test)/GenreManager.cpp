#include "GenreManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

GenreManager::GenreManager(vector<Genre>* genreList)
    : genres(genreList) {
    loadGenres();
}

void GenreManager::loadGenres() {
    ifstream inFile(filename);
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, name;
        if (iss >> id >> name) {
            genres->push_back(Genre(id, name));
        }
    }
}

void GenreManager::saveGenres() {
    ofstream outFile(filename);
    for (const auto& g : *genres) {
        outFile << g.getId() << " " << g.getName() << endl;
    }
}

void GenreManager::addGenre() {
    string id, name;
    cout << "Enter genre ID: ";
    cin >> id;
    cout << "Enter genre name (one word): ";
    cin >> name;

    genres->push_back(Genre(id, name));
    saveGenres();
    cout << "Genre added successfully.\n";
}

void GenreManager::viewGenres() {
    cout << "\n===== GENRES =====\n";
    for (const auto& g : *genres) {
        cout << "ID: " << g.getId()
            << " | Name: " << g.getName() << endl;
    }
}
