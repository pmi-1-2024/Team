#pragma once
#include "User.h"
#include <vector>
#include <string>
using namespace std;

class UserManager {
private:
    vector<User>* users;
public:
    UserManager(vector<User>* usersList);

    void showAllUsers();
    void changeUserRole();
    void deleteUser();
};
