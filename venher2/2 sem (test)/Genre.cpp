#include "Genre.h"
using namespace std;

Genre::Genre(string id, string name)
    : id(id), name(name) {
}

string Genre::getId() const { return id; }
string Genre::getName() const { return name; }
