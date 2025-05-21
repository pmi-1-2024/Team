#include "Publisher.h"
#include <limits> 
using namespace std;

Publisher::Publisher(int id, const string& name) : id(id), name(name) {}

int Publisher::getId() const { return id; }
const string& Publisher::getName() const { return name; } 

void Publisher::setId(int id) { this->id = id; }
void Publisher::setName(const string& name) { this->name = name; }

ostream& operator<<(ostream& os, const Publisher& publisher) {
    os << publisher.id << " " << publisher.name << endl;
    return os;
}

istream& operator>>(istream& is, Publisher& publisher) {
    is >> publisher.id;
    if (is.peek() == '\n') {
        is.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
        is.ignore();
    }
    getline(is, publisher.name);
    return is;
}