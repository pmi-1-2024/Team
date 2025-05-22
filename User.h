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

    // ��������� ����������� ID � 8 ����
    static string generateID() {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dist(10000000, 99999999);
        return to_string(dist(gen));
    }

    // �������� ����� �����������
    void inputUserData(const string& roleInput) {
        role = roleInput;
        id = generateID();
        cout << "������ �������: ";
        cin >> surname;
        cout << "������ ��'�: ";
        cin >> name;
        cout << "������ ���������� �����: ";
        cin >> email;
        cout << "������ ������: ";
        cin >> password;
    }

    // �������
    string getEmail() const { return email; }
    string getPassword() const { return password; }
    string getRole() const { return role; }

    // ���������� ����������� � ����
    void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        if (file.is_open()) {
            file << id << " " << surname << " " << name << " "
                << role << " " << email << " " << password << endl;
            file.close();
        }
        else {
            cerr << "�� ������� ������� ���� ��� ������." << endl;
        }
    }

    // �������� �� ���� ���������� �� email
    static bool exists(const string& filename, const string& email) {
        ifstream file(filename);
        string tempID, tempSurname, tempName, tempRole, tempEmail, tempPassword;

        while (file >> tempID >> tempSurname >> tempName >> tempRole >> tempEmail >> tempPassword) {
            if (tempEmail == email) return true;
        }

        return false;
    }

    // �������� ����� + ������ + ���
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
