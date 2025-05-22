#pragma once
#include <string>
using namespace std;

class Library {
private:
    string id;
    string name;
    string address;

public:
    Library() = default;
    Library(string id, string name, string address);

    string getId() const;
    string getName() const;
    string getAddress() const;
};
