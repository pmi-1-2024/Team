#include "Library.h"
using namespace std;

Library::Library(string id, string name, string address)
    : id(id), name(name), address(address) {
}

string Library::getId() const { return id; }
string Library::getName() const { return name; }
string Library::getAddress() const { return address; }
