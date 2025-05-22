#pragma once
#include "Author.h"
#include <vector>
#include <string>

class AuthorManager {
private:
    vector<Author>* authors;
    string filename = "authors.txt";

public:
    AuthorManager(vector<Author>* authorsList);

    void loadAuthors();
    void saveAuthors();

    void addAuthor();
    void viewAuthors();
};
