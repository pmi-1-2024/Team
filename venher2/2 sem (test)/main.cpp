#include <windows.h>
#include "AuthManager.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    AuthManager auth;
    auth.showMainMenu();

    return 0;
}
