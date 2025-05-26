#include "LibraryStockManager.h"
#include "BookManager.h" 
#include <iostream>
#include <fstream>
#include <limits>
#include <algorithm> 

using namespace std;

namespace {
    template<typename T>
    void loadItemsFromFileLocal(const string& filename, vector<T>& items) {
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
    void saveItemsToFileLocal(const string& filename, const vector<T>& items) {
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


LibraryStockManager::LibraryStockManager(vector<LibraryStockItem>* stockList, const BookManager& bmRef)
    : stockItems(stockList), bookManagerRef(bmRef) {
    if (!stockItems) {
    }
    loadStockItems();
}

LibraryStockManager::~LibraryStockManager() {
    saveStockItems();
}

void LibraryStockManager::loadStockItems() {
    if (!stockItems) return;
    loadItemsFromFileLocal(filename, *stockItems);
}

void LibraryStockManager::saveStockItems() const {
    if (!stockItems) return;
    saveItemsToFileLocal(filename, *stockItems);
}

LibraryStockItem* LibraryStockManager::findStockItem(const string& physicalLibraryId, int bookId) {
    if (!stockItems) return nullptr;
    for (auto& item : *stockItems) {
        if (item.getLibraryId() == physicalLibraryId && item.getBookId() == bookId) {
            return &item;
        }
    }
    return nullptr;
}

bool LibraryStockManager::addOrUpdateStockItem(const string& physicalLibraryId, int bookId, int quantityChange) {
    if (!stockItems) return false;

    const Book* bookExists = bookManagerRef.findBookById(bookId);
    if (!bookExists) {
        cout << "Error: Book with ID " << bookId << " not found in the main catalog." << endl;
        return false;
    }
    if (quantityChange == 0) {
        cout << "Quantity to change is zero, stock not modified." << endl;
        return true;
    }

    LibraryStockItem* existingItem = findStockItem(physicalLibraryId, bookId);
    if (existingItem) {
        int newQuantity = existingItem->getQuantity() + quantityChange;
        if (newQuantity < 0) {
            cout << "Error: Not enough books in stock to deduct this quantity." << endl;
            cout << "Current quantity: " << existingItem->getQuantity() << ", attempted to deduct: " << -quantityChange << endl;
            return false;
        }
        existingItem->setQuantity(newQuantity);
        cout << "Stock updated. Book ID " << bookId << " in library " << physicalLibraryId
            << ", new quantity: " << newQuantity << endl;
    }
    else {
        if (quantityChange < 0) {
            cout << "Error: Attempting to deduct a book that is not in stock for library " << physicalLibraryId << "." << endl;
            return false;
        }
        stockItems->emplace_back(physicalLibraryId, bookId, quantityChange);
        cout << "Book ID " << bookId << " added to stock for library " << physicalLibraryId
            << " with quantity: " << quantityChange << endl;
    }
    return true;
}


void LibraryStockManager::viewStockForLibrary(const string& physicalLibraryId) const {
    if (!stockItems) return;
    cout << "\n===== Stock for Physical Library ID: " << physicalLibraryId << " =====\n";
    bool found = false;
    for (const auto& item : *stockItems) {
        if (item.getLibraryId() == physicalLibraryId) {
            const Book* book = bookManagerRef.findBookById(item.getBookId());
            string bookTitle = book ? book->getTitle() : "Title Unknown";
            cout << "Book ID: " << item.getBookId()
                << " | Title: " << bookTitle
                << " | Quantity: " << item.getQuantity() << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No stock items found for this library or library ID is invalid." << endl;
    }
    cout << "=========================================================\n";
}

void LibraryStockManager::updateStockQuantityViaMenu() {
    string physLibId;
    int bookId_val, new_quantity_val;

    cout << "Enter Physical Library ID: ";
    getline(cin, physLibId);

    cout << "Enter Book ID: ";
    cin >> bookId_val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    LibraryStockItem* item = findStockItem(physLibId, bookId_val);
    if (item) {
        cout << "Current quantity for Book ID " << bookId_val << " in Library " << physLibId
            << " is " << item->getQuantity() << ". Enter new quantity: ";
        cin >> new_quantity_val;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (new_quantity_val < 0) {
            cout << "Quantity cannot be negative. To remove, set to 0." << endl;
            return;
        }
        item->setQuantity(new_quantity_val);
        if (new_quantity_val == 0) {
            cout << "Quantity set to 0. Consider removing the stock item if no longer needed." << endl;
        }
        cout << "Stock quantity updated." << endl;
    }
    else {
        cout << "Stock item for Book ID " << bookId_val
            << " in Library " << physLibId << " not found." << endl;
    }
}


void LibraryStockManager::runStockManagementMenu(const PhysicalLibraryManager& physLibManager) {
    int choice;
    string libId_menu;
    do {
        cout << "\n--- Manage Library Stock ---";
        physLibManager.viewLibraries();
        cout << "Enter Physical Library ID to manage stock (or '0' to go back): ";
        getline(cin, libId_menu);
        if (libId_menu == "0") break;

        if (physLibManager.findLibraryById(libId_menu) == nullptr) {
            cout << "Physical Library with ID '" << libId_menu << "' not found." << endl;
            continue;
        }

        this->viewStockForLibrary(libId_menu);

        cout << "\n--- Stock Options for Library " << libId_menu << " ---\n"
            << "1. Add/Increase Book Quantity\n"
            << "2. Update Total Book Quantity\n"
            << "3. View Current Stock for this Library\n"
            << "0. Select Different Library / Back\n"
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

        int bookId_val, quantity_val;
        switch (choice) {
        case 1: {
            cout << "Enter Book ID (from main catalog): ";
            cin >> bookId_val; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter quantity to add (can be negative to decrease): ";
            cin >> quantity_val; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (quantity_val == 0) { cout << "Quantity to change is zero.\n"; break; }
            addOrUpdateStockItem(libId_menu, bookId_val, quantity_val);
            break;
        }
        case 2: {
            updateStockQuantityViaMenu();
            cout << "Enter Book ID to update quantity: "; 
            cin >> bookId_val; cin.ignore(numeric_limits<streamsize>::max(), '\n');
            LibraryStockItem* item = this->findStockItem(libId_menu, bookId_val);
            if (item) {
                cout << "Current quantity: " << item->getQuantity() << ". Enter new total quantity: ";
                cin >> quantity_val; cin.ignore(numeric_limits<streamsize>::max(), '\n');
                if (quantity_val < 0) { cout << "Quantity cannot be negative." << endl; break; }
                item->setQuantity(quantity_val);
                cout << "Stock quantity updated." << endl;
            }
            else {
                cout << "Stock item for this book in this library not found." << endl;
            }
            break;
        }
        case 3: this->viewStockForLibrary(libId_menu); break;
        case 0: break;
        default: cout << "Invalid choice. Please try again.\n";
        }
        if (choice != 0) {
            cout << "Press Enter to continue..."; cin.get();
        }
    } while (libId_menu != "0");
}