#pragma once
#include "Genre.h"
#include <vector>
#include <string>
using namespace std;

class GenreManager {
private:
    vector<Genre>* genres;
    string filename = "genres.txt";

public:
    GenreManager(vector<Genre>* genreList);
    void loadGenres();
    void saveGenres();
    void addGenre();
    void viewGenres();
};
