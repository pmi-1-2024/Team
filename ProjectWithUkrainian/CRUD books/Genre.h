#pragma once

#include <string>
#include <iostream>

class Genre {
private:
    int id;
    std::string name;

public:
    Genre(int id = 0, const std::string& name = "");

    int getId() const;
    const std::string& getName() const; 

    void setId(int id);
    void setName(const std::string& name);

    friend std::ostream& operator<<(std::ostream& os, const Genre& genre);
    friend std::istream& operator>>(std::istream& is, Genre& genre);
};

