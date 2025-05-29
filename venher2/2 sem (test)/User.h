#pragma once
#include <string>
using namespace std;

enum class Role {
    ADMIN,
    LIBRARIAN,
    USER
};

class User {
private:
    string id;
    string surname;
    string name;
    string email;
    string password;
    Role role;

public:
    User();
    User(string id, string surname, string name, string email, string password, Role role);

    string getId() const;
    string getFullName() const;
    string getEmail() const;
    string getPassword() const;
    Role getRole() const;

    void setRole(Role newRole);
};
