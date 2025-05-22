#pragma once
#include "Library.h"
#include <vector>
#include <string>
using namespace std;

class LibraryManager {
private:
    vector<Library>* libraries;
    string filename = "libraries.txt";

public:
    LibraryManager(vector<Library>* libraryList);
    void loadLibraries();
    void saveLibraries();
    void addLibrary();
    void viewLibraries();
};
