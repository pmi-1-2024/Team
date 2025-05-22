#include "OrderManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

OrderManager::OrderManager(vector<Order>* orderList, vector<Book>* bookList)
    : orders(orderList), books(bookList) {
    loadOrders();
}

void OrderManager::loadOrders() {
    ifstream inFile(filename);
    if (!inFile) return;

    string line;
    while (getline(inFile, line)) {
        istringstream iss(line);
        string id, userId, bookId, libraryId, issueDate, returnDate;
        if (iss >> id >> userId >> bookId >> libraryId >> issueDate >> returnDate) {
            orders->push_back(Order(id, userId, bookId, libraryId, issueDate, returnDate));
        }
    }
}

void OrderManager::saveOrders() {
    ofstream outFile(filename);
    for (const auto& o : *orders) {
        outFile << o.getId() << " "
            << o.getUserId() << " "
            << o.getBookId() << " "
            << o.getLibraryId() << " "
            << o.getIssueDate() << " "
            << o.getReturnDate() << endl;
    }
}

void OrderManager::createOrder(const string& userId) {
    string id, bookId, libraryId;
    cout << "Enter order ID: ";
    cin >> id;
    cout << "Enter book ID: ";
    cin >> bookId;
    cout << "Enter library ID: ";
    cin >> libraryId;

    string issueDate, returnDate = "-";
    cout << "Enter issue date (YYYY-MM-DD): ";
    cin >> issueDate;

    orders->push_back(Order(id, userId, bookId, libraryId, issueDate, returnDate));
    saveOrders();
    cout << "Order created.\n";
}

void OrderManager::viewOrdersByUser(const string& userId) {
    cout << "\nYour Orders:\n";
    for (const auto& o : *orders) {
        if (o.getUserId() == userId) {
            cout << "Order ID: " << o.getId()
                << " | Book ID: " << o.getBookId()
                << " | Library: " << o.getLibraryId()
                << " | Issued: " << o.getIssueDate()
                << " | Returned: " << o.getReturnDate() << endl;
        }
    }
}

void OrderManager::viewAllOrders() {
    cout << "\nAll Orders:\n";
    for (const auto& o : *orders) {
        cout << "Order ID: " << o.getId()
            << " | User: " << o.getUserId()
            << " | Book: " << o.getBookId()
            << " | Library: " << o.getLibraryId()
            << " | Issued: " << o.getIssueDate()
            << " | Returned: " << o.getReturnDate() << endl;
    }
}

void OrderManager::returnOrder() {
    string orderId;
    cout << "Enter order ID to mark as returned: ";
    cin >> orderId;

    for (auto& o : *orders) {
        if (o.getId() == orderId) {
            cout << "Enter return date (YYYY-MM-DD): ";
            string date;
            cin >> date;
            o.setReturnDate(date);
            saveOrders();
            cout << "Order updated.\n";
            return;
        }
    }

    cout << "Order not found.\n";
}
