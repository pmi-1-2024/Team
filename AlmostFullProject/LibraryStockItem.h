#pragma once
#include <string>
#include <iostream>

using namespace std;

class LibraryStockItem {
private:
    string libraryId; 
    int bookId;            
    int quantity;

public:
    LibraryStockItem() = default;
    LibraryStockItem(const string& libId, int bId, int qty);

    string getLibraryId() const;
    int getBookId() const; 
    int getQuantity() const;
    void setQuantity(int newQuantity);

    friend ostream& operator<<(ostream& os, const LibraryStockItem& item);
    friend istream& operator>>(istream& is, LibraryStockItem& item);
};