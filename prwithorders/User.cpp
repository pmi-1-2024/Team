#include "User.h"
#include <sstream> 

User::User(const string& u_id, const string& u_surname, const string& u_name,
    const string& u_email, const string& u_password, const string& u_role)
    : id(u_id), surname(u_surname), name(u_name), email(u_email), password(u_password), role(u_role) {
}

void User::setRole(const string& newRole) {
    role = newRole;
}

vector<string> User::getFullInfoLines() const {
    return { id, surname, name, email, password, role, "" };
}

void User::saveAllUsers(const string& filename, const vector<User>& users) {
    ofstream file(filename, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << " for writing users." << endl;
        return;
    }

    for (const auto& user : users) {
        for (const auto& line : user.getFullInfoLines()) {
            file << line << "\n";
        }
    }

    file.close();
}

string User::generateID() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(10000000, 99999999);
    return to_string(dist(gen));
}
void User::inputUserData(const string& roleInput) {
    this->role = roleInput;
    cout << "Enter your surname: ";
    getline(cin, this->surname);
    cout << "Enter name: ";
    getline(cin, this->name);
    cout << "Enter email: ";
    getline(cin, this->email);
    cout << "Enter password: ";
    getline(cin, this->password);
}

void User::saveToFile(const string& filename) const {
    ofstream file(filename, ios::app);
    if (file.is_open()) {
        file << id << "\n"
            << surname << "\n"
            << name << "\n"
            << email << "\n"
            << password << "\n"
            << role << "\n\n";
        file.close();
    }
    else {
        cerr << "Error: Could not open file " << filename << " for writing user data." << endl;
    }
}

bool User::exists(const string& filename, const string& emailToCheck) {
    ifstream file(filename);
    if (!file.is_open()) return false;
    string tempId, tempSurname, tempName, tempEmail, tempPassword, tempRole, emptyLine;
    while (getline(file, tempId) &&
        getline(file, tempSurname) &&
        getline(file, tempName) &&
        getline(file, tempEmail) &&
        getline(file, tempPassword) &&
        getline(file, tempRole)) {
        if (tempEmail == emailToCheck) {
            file.close();
            return true;
        }
        getline(file, emptyLine);
    }
    file.close();
    return false;
}

bool User::authenticate(const string& filename, const string& roleToAuth,
    const string& emailToAuth, const string& passwordToAuth) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open user file " << filename << " for authentication." << endl;
        return false;
    }
    string tempId, tempSurname, tempName, tempEmail, tempPassword, tempRole, emptyLine;
    while (getline(file, tempId) &&
        getline(file, tempSurname) &&
        getline(file, tempName) &&
        getline(file, tempEmail) &&
        getline(file, tempPassword) &&
        getline(file, tempRole)) {
        if (tempEmail == emailToAuth && tempPassword == passwordToAuth && tempRole == roleToAuth) {
            file.close();
            return true;
        }
        getline(file, emptyLine);
    }
    file.close();
    return false;
}

User User::loadByEmail(const string& filename, const string& emailToLoad) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open user file " << filename << " for loading data." << endl;
        return User();
    }
    string tempId, tempSurname, tempName, tempEmail, tempPassword, tempRole, emptyLine;
    while (getline(file, tempId) &&
        getline(file, tempSurname) &&
        getline(file, tempName) &&
        getline(file, tempEmail) &&
        getline(file, tempPassword) &&
        getline(file, tempRole)) {
        if (tempEmail == emailToLoad) {
            file.close();
            return User(tempId, tempSurname, tempName, tempEmail, tempPassword, tempRole);
        }
        getline(file, emptyLine);
    }
    file.close();
    return User();
}