#include "Author.h"
using namespace std;

Author::Author(string id, string name, string surname)
    : id(id), name(name), surname(surname) {
}

string Author::getId() const { return id; }
string Author::getName() const { return name; }
string Author::getSurname() const { return surname; }

string Author::getFullName() const {
    return name + " " + surname;
}
