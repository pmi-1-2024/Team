
#include "PhysicalLibraryManager.h"
#include <fstream>
#include <algorithm> 
#include <limits>   
using namespace std;

namespace { 
    template<typename T>
    void loadItemsFromFile(const string& filename, vector<T>& items) {
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        T item;
        items.clear();
        while (file >> item) {
            items.push_back(item);
        }
        file.close();
    }

    template<typename T>
    void saveItemsToFile(const string& filename, const vector<T>& items) {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cerr << "Error: Cannot open " << filename << " for saving." << endl;
            return;
        }
        for (const auto& item : items) {
            file << item; 
        }
        file.close();
    }
} 

PhysicalLibraryManager::PhysicalLibraryManager(vector<PhysicalLibrary>* libraryList)
    : libraries(libraryList) {
    if (libraries == nullptr) {
        cerr << "Error: PhysicalLibraryManager received a null pointer for libraryList." << endl;
    }
    loadLibraries();
}

PhysicalLibraryManager::~PhysicalLibraryManager() {
    saveLibraries();
}

void PhysicalLibraryManager::loadLibraries() {
    if (!libraries) return;
    loadItemsFromFile(filename, *libraries);
}

void PhysicalLibraryManager::saveLibraries() const {
    if (!libraries) return;
    saveItemsToFile(filename, *libraries);
}

void PhysicalLibraryManager::addLibrary() {
    if (!libraries) return;
    string id, name, address;
    cout << "Enter ID for the new physical library: "; 
    getline(cin, id);

    if (findLibraryById(id) != nullptr) {
        cout << "Physical library with ID " << id << " already exists." << endl; 
        return;
    }

    cout << "Enter library name: "; 
    getline(cin, name);
    cout << "Enter library address: "; 
    getline(cin, address);

    libraries->emplace_back(id, name, address);
    cout << "Physical library added." << endl; 
}

void PhysicalLibraryManager::viewLibraries() const {
    if (!libraries || libraries->empty()) {
        cout << "No physical libraries registered." << endl; 
        return;
    }
    cout << "\n===== Registered Physical Libraries =====\n"; 
    for (const auto& lib : *libraries) {
        cout << "ID: " << lib.getId()
            << " | Name: " << lib.getName()   
            << " | Address: " << lib.getAddress()  
            << endl;
    }
    cout << "==========================================\n";
}

PhysicalLibrary* PhysicalLibraryManager::findLibraryById(const string& libId) {
    if (!libraries) return nullptr;
    for (auto& lib : *libraries) {
        if (lib.getId() == libId) {
            return &lib;
        }
    }
    return nullptr;
}

const PhysicalLibrary* PhysicalLibraryManager::findLibraryById(const string& libId) const {
    if (!libraries) return nullptr;
    for (const auto& lib : *libraries) {
        if (lib.getId() == libId) {
            return &lib;
        }
    }
    return nullptr;
}

void PhysicalLibraryManager::modifyLibrary() {
    if (!libraries) return;
    string id_to_update;
    cout << "Enter ID of the physical library to update: "; 
    getline(cin, id_to_update);

    PhysicalLibrary* lib = findLibraryById(id_to_update);
    if (lib) {
        string temp_str;
        cout << "Found library. Current data: \n" 
            << "Name: " << lib->getName() << "\n" 
            << "Address: " << lib->getAddress() << "\n"; 
        cout << "Enter new data (press Enter to keep current value):\n"; 

        cout << "New Name (current: " << lib->getName() << "): "; 
        getline(cin, temp_str);
        if (!temp_str.empty()) lib->setName(temp_str);

        cout << "New Address (current: " << lib->getAddress() << "): "; 
        getline(cin, temp_str);
        if (!temp_str.empty()) lib->setAddress(temp_str);

        cout << "Physical library data updated." << endl; 
    }
    else {
        cout << "Physical library with ID " << id_to_update << " not found." << endl; 
    }
}

void PhysicalLibraryManager::removeLibrary() {
    if (!libraries) return;
    string id_to_delete;
    cout << "Enter ID of the physical library to delete: "; 
    getline(cin, id_to_delete);

    auto it = remove_if(libraries->begin(), libraries->end(),
        [&](const PhysicalLibrary& lib) { return lib.getId() == id_to_delete; });

    if (it != libraries->end()) {
        libraries->erase(it, libraries->end());
        cout << "Physical library deleted." << endl; 
    }
    else {
        cout << "Physical library with ID " << id_to_delete << " not found." << endl; 
    }
}

void PhysicalLibraryManager::runPhysicalLibraryMenu() {
    int choice;
    do {
        cout << "\n--- Manage Physical Libraries ---\n" 
            << "1. Add Physical Library\n"                
            << "2. View All Physical Libraries\n"         
            << "3. Modify Physical Library Data\n"        
            << "4. Remove Physical Library\n"             
            << "0. Return to Previous Menu\n"             
            << "Your choice: ";                         
        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1; 
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        }

        switch (choice) {
        case 1: addLibrary(); break;
        case 2: viewLibraries(); break;
        case 3: modifyLibrary(); break;
        case 4: removeLibrary(); break;
        case 0: cout << "Returning to previous menu...\n"; break; 
        default: cout << "Invalid choice. Please try again.\n"; 
        }
        if (choice != 0) {
            cout << "Press Enter to continue..."; cin.get(); 
        }
    } while (choice != 0);
}