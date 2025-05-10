#pragma once
#include <string>
using namespace std;

class User
{
private:
	int id;
	string name;
	string surname;
	string email;
	string password;
	string role;
public:
	User(int id, string name, string surname, string email, string password, string role)
		: id(id), name(name), surname(surname), email(email), password(password), role(role) {
	}
	int getId() const { return id; }
	string getName() const { return name; }
	string getSurname() const { return surname; }
	string getEmail() const { return email; }
	string getPassword() const { return password; }
	string getRole() const { return role; }
	void setName(const string& newName) { name = newName; }
	void setSurname(const string& newSurname) { surname = newSurname; }
	void setEmail(const string& newEmail) { email = newEmail; }
	void setPassword(const string& newPassword) { password = newPassword; }
	void setRole(const string& newRole) { role = newRole; }
};

