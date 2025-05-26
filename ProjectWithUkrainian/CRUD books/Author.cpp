#include "Author.h"
#include <limits>

Author::Author(int id, const string& name) : id(id), name(name) {}

int Author::getId() const { return id; }
const string& Author::getName() const { return name; } 

void Author::setId(int id) { this->id = id; }
void Author::setName(const string& name) { this->name = name; }

ostream& operator<<(ostream& os, const Author& author) {
    os << author.id << " " << author.name << endl;
    return os;
}

istream& operator>>(istream& is, Author& author) {
    is >> author.id;
    if (is.peek() == '\n') { 
        is.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
        is.ignore(); 
    }
    getline(is, author.name);
    return is;
}