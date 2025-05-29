#include "PublisherManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

PublisherManager::PublisherManager(vector<Publisher>* publisherList)
    : publishers(publisherList) {
    loadPublishers();
}

void PublisherManager::loadPublishers() {
    ifstream inFile(filename);
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, name, address;
        if (iss >> id >> name >> address) {
            publishers->push_back(Publisher(id, name, address));
        }
    }
}

void PublisherManager::savePublishers() {
    ofstream outFile(filename);
    for (const auto& p : *publishers) {
        outFile << p.getId() << " " << p.getName() << " " << p.getAddress() << endl;
    }
}

void PublisherManager::addPublisher() {
    string id, name, address;
    cout << "Enter publisher ID: ";
    cin >> id;
    cout << "Enter publisher name (one word): ";
    cin >> name;
    cout << "Enter publisher address (one word): ";
    cin >> address;

    publishers->push_back(Publisher(id, name, address));
    savePublishers();
    cout << "Publisher added successfully.\n";
}

void PublisherManager::viewPublishers() {
    cout << "\n===== PUBLISHERS =====\n";
    for (const auto& p : *publishers) {
        cout << "ID: " << p.getId()
            << " | Name: " << p.getName()
            << " | Address: " << p.getAddress() << endl;
    }
}
