#pragma once
#include <string>
using namespace std;
class Library
{
private:
	int id;
	string name;
	string address;
public:
	Library(int id, string name, string address)
		: id(id), name(name), address(address) {
	}
	int getId() const { return id; }
	string getName() const { return name; }
	string getAddress() const { return address; }
	void setName(const string& newName) { name = newName; }
	void setAddress(const string& newAddress) { address = newAddress; }
};

