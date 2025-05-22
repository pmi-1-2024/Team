#include <iostream> 
#include <fstream>
#include <string>
#include <Windows.h>
#include "BookManager.h"

using namespace std;

void showMainMenu() {
    cout << "========== Головне меню ==========" << endl;
    cout << "1. Вхід" << endl;
    cout << "2. Зареєструватися" << endl;
    cout << "0. Вийти" << endl;
    cout << "==================================" << endl;
    cout << "Оберіть опцію: ";
}

void showRoleMenu() {
    cout << "\n--- Вибір ролі ---" << endl;
    cout << "1. Покупець" << endl;
    cout << "2. Бібліотекар" << endl;
    cout << "3. Адмін" << endl;
    cout << "Оберіть роль: ";
}

string getRoleFromChoice(int choice) {
    switch (choice) {
    case 1: return "Покупець";
    case 2: return "Бібліотекар";
    case 3: return "Адмін";
    default: return "";
    }
}

bool authenticateUser(const string& role, const string& email, const string& password) {
    ifstream file("users.txt");
    if (!file.is_open()) {
        cerr << "Не вдалося відкрити файл users.txt" << endl;
        return false;
    }

    string fileRole, fileEmail, filePassword;

    while (file >> fileRole >> fileEmail >> filePassword) {
        if (fileRole == role && fileEmail == email && filePassword == password) {
            return true;
        }
    }

    return false;
}

bool userExists(const string& email) {
    ifstream file("users.txt");
    string fileRole, fileEmail, filePassword;

    while (file >> fileRole >> fileEmail >> filePassword) {
        if (fileEmail == email) {
            return true;
        }
    }
    return false;
}

void registerUser() {
    int roleChoice;
    string role, email, password;

    cout << "\n==== Реєстрація користувача ====\n";
    showRoleMenu();
    cin >> roleChoice;

    role = getRoleFromChoice(roleChoice);
    if (role.empty()) {
        cout << "Невірна роль." << endl;
        return;
    }

    cout << "Введіть електронну пошту: ";
    cin >> email;

    if (userExists(email)) {
        cout << "Користувач з такою поштою вже існує.\n";
        return;
    }

    cout << "Введіть пароль: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    if (!file.is_open()) {
        cerr << " Не вдалося відкрити файл для запису.\n";
        return;
    }

    file << role << " " << email << " " << password << endl;
    file.close();

    cout << " Реєстрація успішна!\n";
}

bool loginUser() {
    int roleChoice;
    string role, email, password;

    cout << "\n==== Вхід користувача ====\n";
    showRoleMenu();
    cin >> roleChoice;

    role = getRoleFromChoice(roleChoice);
    if (role.empty()) {
        cout << "Невірна роль." << endl;
        return false;
    }

    cout << "Введіть електронну пошту: ";
    cin >> email;
    cout << "Введіть пароль: ";
    cin >> password;

    if (authenticateUser(role, email, password)) {
        cout << "Успішний вхід як " << role << "!" << endl;

        if (role == "Покупець") {
            // buyerMenu();
        }
        else if (role == "Бібліотекар") {
            BookManager manager;
            manager.run();
        }
        else if (role == "Адмін") {
            // adminMenu();
        }

        return true;
    }
    else {
        cout << "Невірна пошта або пароль.\n";
        return false;
    }
}

int main() {
    SetConsoleOutputCP(1251);
    int choice;

    do {
        showMainMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            loginUser();
            break;
        case 2:
            registerUser();
            break;
        case 0:
            cout << "Вихід з програми..." << endl;
            break;
        default:
            cout << "Невірний вибір. Спробуйте ще раз." << endl;
        }

        cout << endl;

    } while (choice != 0);

    return 0;
}
