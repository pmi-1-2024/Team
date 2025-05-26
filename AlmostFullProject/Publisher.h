#pragma once
#include <string>
#include <iostream>
using namespace std;

class Publisher {
private:
    int id;
    string name;

public:
    Publisher(int id = 0, const string& name = "");

    int getId() const;
    const string& getName() const;

    void setId(int id);
    void setName(const string& name);

    friend ostream& operator<<(ostream& os, const Publisher& publisher);
    friend istream& operator>>(istream& is, Publisher& publisher);
};

