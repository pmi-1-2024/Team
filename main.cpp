#include <iostream> 
#include <fstream>
#include <string>
#include <Windows.h>
#include "BookManager.h"
#include "User.h"

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

void registerUser() {
    int roleChoice;
    cout << "\n==== Реєстрація користувача ====\n";
    showRoleMenu();
    cin >> roleChoice;

    string role = getRoleFromChoice(roleChoice);
    if (role.empty()) {
        cout << "Невірна роль." << endl;
        return;
    }

    User newUser;
    newUser.inputUserData(role);

    if (User::exists("users.txt", newUser.getEmail())) {
        cout << "Користувач з такою поштою вже існує.\n";
        return;
    }

    newUser.saveToFile("users.txt");
    cout << "Реєстрація успішна!\n";
}

bool loginUser() {
    int roleChoice;
    string email, password;

    cout << "\n==== Вхід користувача ====\n";
    showRoleMenu();
    cin >> roleChoice;

    string role = getRoleFromChoice(roleChoice);
    if (role.empty()) {
        cout << "Невірна роль." << endl;
        return false;
    }

    cout << "Введіть електронну пошту: ";
    cin >> email;
    cout << "Введіть пароль: ";
    cin >> password;

    if (User::authenticate("users.txt", role, email, password)) {
        cout << "Успішний вхід як " << role << "!" << endl;

        if (role == "Покупець") {
            // buyerMenu();
        }
        else if (role == "Бібліотекар") {
         //   BookManager manager;
         //   manager.run();
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
    SetConsoleCP(1251);
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
