#include "LibraryStockItem.h"


LibraryStockItem::LibraryStockItem(const string& libId, int bId, int qty)
    : libraryId(libId), bookId(bId), quantity(qty) {
}

string LibraryStockItem::getLibraryId() const { return libraryId; }
int LibraryStockItem::getBookId() const { return bookId; }
int LibraryStockItem::getQuantity() const { return quantity; }
void LibraryStockItem::setQuantity(int newQuantity) { quantity = newQuantity; }


ostream& operator<<(ostream& os, const LibraryStockItem& item) {
    os << item.libraryId << " " << item.bookId << " " << item.quantity << endl;
    return os;
}

istream& operator>>(istream& is, LibraryStockItem& item) {
    is >> item.libraryId >> item.bookId >> item.quantity;
    return is;
}