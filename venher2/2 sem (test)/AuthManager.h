#pragma once
#include "User.h"
#include <vector>
using namespace std;

class AuthManager {
private:
    vector<User> users;
    string filename = "users.txt";

public:
    AuthManager();
    void loadUsers();
    void saveUsers();
    bool registerUser();
    User* loginUser();
    void showMainMenu();
};
