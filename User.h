#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <random>

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
        const string& email, const string& password, const string& role)
        : id(id), surname(surname), name(name), email(email), password(password), role(role) {
    }

    // Генерація випадкового ID з 8 цифр
    static string generateID() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(10000000, 99999999);
        return to_string(dist(gen));
    }

    // Введення даних користувача
    void inputUserData(const string& roleInput) {
        role = roleInput;
        id = generateID();
        cout << "Введіть прізвище: ";
        cin >> surname;
        cout << "Введіть ім'я: ";
        cin >> name;
        cout << "Введіть електронну пошту: ";
        cin >> email;
        cout << "Введіть пароль: ";
        cin >> password;
    }

    // Геттери
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getRole() const { return role; }

    // Збереження користувача у файл
    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << id << " " << surname << " " << name << " "
                << role << " " << email << " " << password << endl;
            file.close();
        }
        else {
            cerr << "Не вдалося відкрити файл для запису." << endl;
        }
    }

    // Перевірка чи існує користувач за email
    static bool exists(const string& filename, const string& email) {
        ifstream file(filename);
        string tempID, tempSurname, tempName, tempRole, tempEmail, tempPassword;

        while (file >> tempID >> tempSurname >> tempName >> tempRole >> tempEmail >> tempPassword) {
            if (tempEmail == email) return true;
        }

        return false;
    }

    // Перевірка пошти + пароля + ролі
    static bool authenticate(const string& filename, const string& role,
        const string& email, const string& password) {
        ifstream file("users.txt");
        string tempID, tempSurname, tempName, tempRole, tempEmail, tempPassword;

        while (file >> tempID >> tempSurname >> tempName >> tempRole >> tempEmail >> tempPassword) {
            if (tempRole == role && tempEmail == email && tempPassword == password) return true;
        }

        return false;
    }
};
