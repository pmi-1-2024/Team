#pragma once
#include <string>
using namespace std;

class Publisher {
private:
    string id;
    string name;
    string address;

public:
    Publisher() = default;
    Publisher(string id, string name, string address);

    string getId() const;
    string getName() const;
    string getAddress() const;
};
