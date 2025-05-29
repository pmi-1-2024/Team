#pragma once
#include "LibraryStockItem.h" 
#include "Book.h"             
#include <vector>
#include <string>
#include "PhysicalLibraryManager.h"
class BookManager;

class LibraryStockManager {
private:
    vector<LibraryStockItem>* stockItems;
    const BookManager& bookManagerRef;
    string filename = "library_stock.txt";

    void loadStockItems();
    void saveStockItems() const;

public:
    LibraryStockManager(vector<LibraryStockItem>* stockList, const BookManager& bmRef);
    ~LibraryStockManager();

    bool addOrUpdateStockItem(const string& physicalLibraryId, int bookId, int quantityChange);
    void viewStockForLibrary(const string& physicalLibraryId) const;
    void updateStockQuantityViaMenu();
    LibraryStockItem* findStockItem(const string& physicalLibraryId, int bookId);

    void runStockManagementMenu(const PhysicalLibraryManager& physLibManager);
};