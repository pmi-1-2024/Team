#include <iostream>
#include "DataManager.h"
using namespace std;
void DataManager::loadData() {
    // ������������ ����� � �����
    // ��� ����� ���������� ����� ��� ���������� ����� � �����
}

void DataManager::saveData() {
    // ���������� ����� � �����
    // ��� ����� ���������� ����� ��� ������ ����� � �����
}

bool DataManager::registerUser(const User& user) {
    for (const auto& existingUser : users) {
        if (existingUser.getEmail() == user.getEmail()) {
            return false; // ���������� ��� ����
        }
    }
    users.push_back(user);
    return true;
}

User* DataManager::loginUser(const string& email, const string& password) {
    for (auto& user : users) {
        if (user.getEmail() == email && user.getPassword() == password) {
            return &user; // ������� ����
        }
    }
    return nullptr; // ����� ���
}