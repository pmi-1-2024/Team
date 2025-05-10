#pragma once
class Author
{
private:
	int id;
	string name;
	string surname;
	//string email;
	//string password;
	//string role;
public:
	Author(int id, string name, string surname)
		: id(id), name(name), surname(surname) {
	}
	int getId() const { return id; }
	string getName() const { return name; }
	string getSurname() const { return surname; }
	void setName(const string& newName) { name = newName; }
	void setSurname(const string& newSurname) { surname = newSurname; }
};

