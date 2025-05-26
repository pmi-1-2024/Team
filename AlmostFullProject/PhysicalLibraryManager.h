#pragma once
#include "PhysicalLibrary.h"
#include <vector>
#include <string>
#include <iostream> 

class PhysicalLibraryManager {
private:
    vector<PhysicalLibrary>* libraries;
    string filename = "libraries.txt";

    void loadLibraries();
    void saveLibraries() const;

public:
    PhysicalLibraryManager(vector<PhysicalLibrary>* libraryList);
    ~PhysicalLibraryManager();

    void addLibrary();
    void viewLibraries() const; 
    void modifyLibrary();
    void removeLibrary();

    PhysicalLibrary* findLibraryById(const string& libId);
    const PhysicalLibrary* findLibraryById(const string& libId) const;

    void runPhysicalLibraryMenu();
};