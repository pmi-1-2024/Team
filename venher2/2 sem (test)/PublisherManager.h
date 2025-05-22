#pragma once
#include "Publisher.h"
#include <vector>
#include <string>
using namespace std;

class PublisherManager {
private:
    vector<Publisher>* publishers;
    string filename = "publishers.txt";

public:
    PublisherManager(vector<Publisher>* publisherList);
    void loadPublishers();
    void savePublishers();
    void addPublisher();
    void viewPublishers();
};
