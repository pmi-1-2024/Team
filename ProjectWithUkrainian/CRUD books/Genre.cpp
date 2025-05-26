#include "Genre.h"
#include <limits> 
using namespace std;

Genre::Genre(int id, const string& name) : id(id), name(name) {}

int Genre::getId() const { return id; }
const string& Genre::getName() const { return name; } 

void Genre::setId(int id) { this->id = id; }
void Genre::setName(const string& name) { this->name = name; }

ostream& operator<<(ostream& os, const Genre& genre) {
    os << genre.id << " " << genre.name << endl;
    return os;
}

istream& operator>>(istream& is, Genre& genre) {
    is >> genre.id;
    if (is.peek() == '\n') {
        is.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
        is.ignore();
    }
    getline(is, genre.name);
    return is;
}