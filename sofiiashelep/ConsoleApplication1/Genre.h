#pragma once
#include <string>
using namespace std;

class Genre
{
private:
	int id;
	string name;
public:
	Genre(int id, string name)
		: id(id), name(name) {
	}
	int getId() const { return id; }
	string getName() const { return name; }
	void setName(const string& newName) { name = newName; }
};

