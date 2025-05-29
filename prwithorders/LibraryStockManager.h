#pragma once
#include "LibraryStockItem.h" 
#include "Book.h"             
#include <vector>
#include <string>
#include "PhysicalLibraryManager.h"
class BookManager;

class LibraryStockManager {
private:
    std::vector<LibraryStockItem>* stockItems;
    const BookManager& bookManagerRef;
    std::string filename = "library_stock.txt";

    void loadStockItems();
    void saveStockItems() const;

public:
    LibraryStockManager(std::vector<LibraryStockItem>* stockList, const BookManager& bmRef);
    ~LibraryStockManager();

    bool addOrUpdateStockItem(const std::string& physicalLibraryId, int bookId, int quantityChange); 
    void viewStockForLibrary(const std::string& physicalLibraryId) const; 
    void updateStockQuantityViaMenu();
    LibraryStockItem* findStockItem(const std::string& physicalLibraryId, int bookId); 

    void runStockManagementMenu(const PhysicalLibraryManager& physLibManager);
};