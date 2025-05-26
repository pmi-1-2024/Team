#pragma once

#include <string>
#include <iostream>
#include <fstream>
#include <random>
#include <limits>

using namespace std;

class User {
private:
    string id;
    string surname;
    string name;
    string email;
    string password;
    string role;

public:
    User() = default;
    User(const string& id, const string& surname, const string& name,
        const string& email, const string& password, const string& role);

    static string generateID();
    void inputUserData(const string& roleInput); 

    string getId() const { return id; }
    string getSurname() const { return surname; } 
    string getName() const { return name; }       
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getRole() const { return role; }

    void setPassword(const string& newPassword) { password = newPassword; }
    void setEmail(const string& newEmail) { email = newEmail; }

    void saveToFile(const string& filename) const;
    static bool exists(const string& filename, const string& email);
    static bool authenticate(const string& filename, const string& role,
        const string& email, const string& password);
    static User loadByEmail(const string& filename, const string& emailToLoad);
};