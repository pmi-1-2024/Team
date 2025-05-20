#pragma once
#include <iostream>
using namespace std;

#include <string>

class Library {
private:
    int ID;
    string name;
    string address;
public:

    Library(int id, const std::string& name, const std::string& address);
    int getID() const { return ID; }
    string getName() const { return name; }
    string getAddress() const { return address; }

};

