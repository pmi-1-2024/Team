#pragma once
#include <string>
using namespace std;

class Publisher
{
private:
	int id;
	string name;
	string address;
public:
	Publisher(int id, string name, string address)
		: id(id), name(name), address(address) {
	}
	int getId() const { return id; }
	string getName() const { return name; }
	string getAddress() const { return address; }
	void setName(const string& newName) { name = newName; }
	void setAddress(const string& newAddress) { address = newAddress; }
};

