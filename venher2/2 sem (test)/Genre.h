#pragma once
#include <string>
using namespace std;

class Genre {
private:
    string id;
    string name;

public:
    Genre() = default;
    Genre(string id, string name);

    string getId() const;
    string getName() const;
};
