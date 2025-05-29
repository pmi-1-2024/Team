#pragma once
#include <string>
using namespace std;

class Author {
private:
    string id;
    string name;
    string surname;

public:
    Author() = default;
    Author(string id, string name, string surname);

    string getId() const;
    string getName() const;
    string getSurname() const;
    string getFullName() const;
};
