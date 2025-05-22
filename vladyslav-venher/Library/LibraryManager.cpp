#include "LibraryManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

LibraryManager::LibraryManager(vector<Library>* libraryList)
    : libraries(libraryList) {
    loadLibraries();
}

void LibraryManager::loadLibraries() {
    ifstream inFile(filename);
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, name, address;
        if (iss >> id >> name >> address) {
            libraries->push_back(Library(id, name, address));
        }
    }
}

void LibraryManager::saveLibraries() {
    ofstream outFile(filename);
    for (const auto& lib : *libraries) {
        outFile << lib.getId() << " " << lib.getName() << " " << lib.getAddress() << endl;
    }
}

void LibraryManager::addLibrary() {
    string id, name, address;
    cout << "Enter library ID: ";
    cin >> id;
    cout << "Enter library name (one word): ";
    cin >> name;
    cout << "Enter library address (one word): ";
    cin >> address;

    libraries->push_back(Library(id, name, address));
    saveLibraries();
    cout << "Library added successfully.\n";
}

void LibraryManager::viewLibraries() {
    cout << "\n===== LIBRARIES =====\n";
    for (const auto& lib : *libraries) {
        cout << "ID: " << lib.getId()
            << " | Name: " << lib.getName()
            << " | Address: " << lib.getAddress() << endl;
    }
}
