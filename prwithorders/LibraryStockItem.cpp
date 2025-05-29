#include "LibraryStockItem.h"

LibraryStockItem::LibraryStockItem(const std::string& libId, int bId, int qty)
    : libraryId(libId), bookId(bId), quantity(qty) {
}

std::string LibraryStockItem::getLibraryId() const { return libraryId; }
int LibraryStockItem::getBookId() const { return bookId; }
int LibraryStockItem::getQuantity() const { return quantity; }
void LibraryStockItem::setQuantity(int newQuantity) { quantity = newQuantity; }


std::ostream& operator<<(std::ostream& os, const LibraryStockItem& item) {
    os << item.libraryId << " " << item.bookId << " " << item.quantity << std::endl;
    return os;
}

std::istream& operator>>(std::istream& is, LibraryStockItem& item) {
    is >> item.libraryId >> item.bookId >> item.quantity;
    return is;
}