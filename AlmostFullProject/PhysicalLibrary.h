#pragma once
#include <string>
#include <iostream>

using namespace std;

class PhysicalLibrary {
private:
    string id;
    string name;
    string address;

public:
    PhysicalLibrary() = default;
    PhysicalLibrary(const string& id, const string& name, const string& address);

    string getId() const;
    string getName() const;
    string getAddress() const;

    void setName(const string& newName);
    void setAddress(const string& newAddress);

    friend ostream& operator<<(ostream& os, const PhysicalLibrary& lib);
    friend istream& operator>>(istream& is, PhysicalLibrary& lib);
};