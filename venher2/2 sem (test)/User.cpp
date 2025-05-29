#include "User.h"
using namespace std;

User::User() {}

User::User(string id, string surname, string name, string email, string password, Role role)
    : id(id), surname(surname), name(name), email(email), password(password), role(role) {
}

string User::getId() const {
    return id;
}

string User::getFullName() const {
    return name + " " + surname;
}

string User::getEmail() const {
    return email;
}

string User::getPassword() const {
    return password;
}

Role User::getRole() const {
    return role;
}

void User::setRole(Role newRole) {
    role = newRole;
}
