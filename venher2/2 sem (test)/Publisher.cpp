#include "Publisher.h"
using namespace std;

Publisher::Publisher(string id, string name, string address)
    : id(id), name(name), address(address) {
}

string Publisher::getId() const { return id; }
string Publisher::getName() const { return name; }
string Publisher::getAddress() const { return address; }
