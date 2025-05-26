#pragma once

#include <string>
#include <iostream>

using namespace std;

class Genre {
private:
    int id;
    string name;

public:
    Genre(int id = 0, const string& name = "");

    int getId() const;
    const string& getName() const; 

    void setId(int id);
    void setName(const string& name);

    friend ostream& operator<<(ostream& os, const Genre& genre);
    friend istream& operator>>(istream& is, Genre& genre);
};

