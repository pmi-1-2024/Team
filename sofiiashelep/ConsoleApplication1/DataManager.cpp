#include <iostream>
#include "DataManager.h"
using namespace std;
void DataManager::loadData() {
    // Завантаження даних з файлів
    // Тут можна реалізувати логіку для зчитування даних з файлів
}

void DataManager::saveData() {
    // Збереження даних у файли
    // Тут можна реалізувати логіку для запису даних у файли
}

bool DataManager::registerUser(const User& user) {
    for (const auto& existingUser : users) {
        if (existingUser.getEmail() == user.getEmail()) {
            return false; // Користувач вже існує
        }
    }
    users.push_back(user);
    return true;
}

User* DataManager::loginUser(const string& email, const string& password) {
    for (auto& user : users) {
        if (user.getEmail() == email && user.getPassword() == password) {
            return &user; // Успішний вхід
        }
    }
    return nullptr; // Невірні дані
}