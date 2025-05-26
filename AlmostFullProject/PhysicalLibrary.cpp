#include "PhysicalLibrary.h"
#include <limits>

using namespace std;

PhysicalLibrary::PhysicalLibrary(const string& id_val, const string& name_val, const string& address_val)
    : id(id_val), name(name_val), address(address_val) {
}

string PhysicalLibrary::getId() const { return id; }
string PhysicalLibrary::getName() const { return name; }
string PhysicalLibrary::getAddress() const { return address; }

void PhysicalLibrary::setName(const string& newName) { name = newName; }
void PhysicalLibrary::setAddress(const string& newAddress) { address = newAddress; }

ostream& operator<<(ostream& os, const PhysicalLibrary& lib) {
    os << lib.id << "\n"
        << lib.name << "\n"
        << lib.address << "\n";
    return os;
}

istream& operator>>(istream& is, PhysicalLibrary& lib) {
    if (!getline(is, lib.id)) return is;
    if (!getline(is, lib.name)) return is;
    if (!getline(is, lib.address)) return is;

    return is;
}