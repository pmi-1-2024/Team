#include "OrderManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cctype>

OrderManager::OrderManager(BookManager* bm) : bookManager(bm), ordersFileName("orders.txt") {
    loadOrdersFromFile();
}

OrderManager::~OrderManager() {
    saveOrdersToFile();
}

void OrderManager::loadOrdersFromFile() {
    ifstream file(ordersFileName);
    if (!file.is_open()) {
        return; // File doesn't exist yet, that's okay
    }

    Order order;
    orders.clear();
    while (file >> order) {
        orders.push_back(order);
    }
    file.close();
}

void OrderManager::saveOrdersToFile() const {
    ofstream file(ordersFileName, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << ordersFileName << " for saving orders." << endl;
        return;
    }

    for (const auto& order : orders) {
        file << order;
    }
    file.close();
}

void OrderManager::displayOrderDetails(const Order& order) const {
    const Book* book = bookManager->findBookById(order.getBookId());

    cout << "Order ID: " << order.getOrderId() << endl;
    cout << "Type: " << order.getTypeString() << endl;
    cout << "Status: " << order.getStatusString() << endl;
    cout << "Book: ";
    if (book) {
        cout << book->getTitle() << " (ID: " << book->getId() << ")" << endl;
        cout << "Author: " << bookManager->getAuthorNameById(book->getAuthorId()) << endl;
    }
    else {
        cout << "Book not found (ID: " << order.getBookId() << ")" << endl;
    }

    if (order.getType() == 1) { // PURCHASE
        cout << "Format: " << order.getBookFormat() << endl;
        cout << "Price: " << order.getTotalPrice() << " UAH" << endl;
    }

    cout << "Order Date: " << order.getOrderDate() << endl;
    if (!order.getReturnDate().empty()) {
        cout << "Return Date: " << order.getReturnDate() << endl;
    }
    cout << "------------------------" << endl;
}

void OrderManager::borrowBook(const User& currentUser) {
    bool continueBorrowing = true;

    while (continueBorrowing) {
        // Show available books
        cout << "\n=== Available Books for Borrowing ===" << endl;
        const vector<Book>& allBooks = bookManager->getAllBooks();
        vector<Book> availableBooks;

        for (const auto& book : allBooks) {
            if (book.isAvailable() && !hasActiveOrderForBook(currentUser.getId(), book.getId())) {
                availableBooks.push_back(book);
            }
        }

        if (availableBooks.empty()) {
            cout << "No books available for borrowing." << endl;
            return;
        }

        for (const auto& book : availableBooks) {
            book.displayInfo(*bookManager);
        }

        // Get book selection
        int bookId = getIntInput("Enter the ID of the book you want to borrow: ");

        // Find the book
        Book* selectedBook = nullptr;
        for (auto& book : availableBooks) {
            if (book.getId() == bookId) {
                selectedBook = &book;
                break;
            }
        }

        if (!selectedBook) {
            cout << "Invalid book ID or book not available for borrowing." << endl;
        }
        else {
            // Create borrow order
            Order newOrder(currentUser.getId(), bookId, 0); // 0 = BORROW
            orders.push_back(newOrder);

            // Mark book as unavailable
            bookManager->setBookAvailability(bookId, false);

            cout << "Book \"" << selectedBook->getTitle() << "\" successfully borrowed!" << endl;
            cout << "Order ID: " << newOrder.getOrderId() << endl;
        }

        // Ask if user wants to borrow another book
        char choice = getCharInput("Do you want to borrow another book?", "yn");
        continueBorrowing = (choice == 'y');
    }
}

void OrderManager::returnBook(const User& currentUser) {
    // Get active borrow orders for the user
    vector<Order> activeOrders = getActiveOrders(currentUser.getId());

    if (activeOrders.empty()) {
        cout << "You have no active borrowed books to return." << endl;
        return;
    }

    cout << "\n=== Your Active Borrowed Books ===" << endl;
    for (const auto& order : activeOrders) {
        displayOrderDetails(order);
    }

    int orderId = getIntInput("Enter the Order ID of the book you want to return: ");

    // Find the order
    bool orderFound = false;
    for (auto& order : orders) {
        if (order.getOrderId() == orderId &&
            order.getUserId() == currentUser.getId() &&
            order.canBeReturned()) {

            // Mark order as returned
            order.setStatus(1); // RETURNED
            order.setReturnDate(order.getCurrentDate());

            // Make book available again
            bookManager->setBookAvailability(order.getBookId(), true);

            cout << "Book successfully returned!" << endl;
            orderFound = true;
            break;
        }
    }

    if (!orderFound) {
        cout << "Invalid Order ID or this order cannot be returned." << endl;
    }
}

void OrderManager::buyBook(const User& currentUser) {
    bool continueBuying = true;

    while (continueBuying) {
        // Show all books
        cout << "\n=== Books Available for Purchase ===" << endl;
        const vector<Book>& allBooks = bookManager->getAllBooks();

        if (allBooks.empty()) {
            cout << "No books available for purchase." << endl;
            return;
        }

        for (const auto& book : allBooks) {
            book.displayInfo(*bookManager);
        }

        // Get book selection
        int bookId = getIntInput("Enter the ID of the book you want to buy: ");

        // Find the book
        const Book* selectedBook = bookManager->findBookById(bookId);

        if (!selectedBook) {
            cout << "Invalid book ID." << endl;
            continue;
        }

        // Show format options and prices
        cout << "\n=== Purchase Options for \"" << selectedBook->getTitle() << "\" ===" << endl;

        vector<pair<string, double>> availableFormats;

        if (selectedBook->getPaperPrice() > 0) {
            availableFormats.push_back(make_pair("Paper", selectedBook->getPaperPrice()));
            cout << "1. Paper version - " << selectedBook->getPaperPrice() << " UAH" << endl;
        }

        if (selectedBook->getElectronicPrice() > 0) {
            availableFormats.push_back(make_pair("Electronic", selectedBook->getElectronicPrice()));
            cout << availableFormats.size() << ". Electronic version - "
                << selectedBook->getElectronicPrice() << " UAH" << endl;
        }

        if (availableFormats.empty()) {
            cout << "This book is not available for purchase (no prices set)." << endl;
            continue;
        }

        // Get format choice
        int formatChoice = getIntInput("Choose format (enter number): ");

        if (formatChoice < 1 || formatChoice >(int)availableFormats.size()) {
            cout << "Invalid format choice." << endl;
            continue;
        }

        string selectedFormat = availableFormats[formatChoice - 1].first;
        double price = availableFormats[formatChoice - 1].second;

        // Create purchase order
        Order newOrder(currentUser.getId(), bookId, 1, selectedFormat, price); // 1 = PURCHASE
        orders.push_back(newOrder);

        cout << "Book \"" << selectedBook->getTitle() << "\" (" << selectedFormat
            << " version) successfully purchased for " << price << " UAH!" << endl;
        cout << "Order ID: " << newOrder.getOrderId() << endl;

        // Ask if user wants to buy another book
        char choice = getCharInput("Do you want to buy another book?", "yn");
        continueBuying = (choice == 'y');
    }
}

void OrderManager::viewOrderHistory(const User& currentUser) const {
    vector<Order> userOrders = getUserOrders(currentUser.getId());

    if (userOrders.empty()) {
        cout << "You have no order history." << endl;
        return;
    }

    cout << "\n=== Your Order History ===" << endl;
    for (const auto& order : userOrders) {
        displayOrderDetails(order);
    }
}

vector<Order> OrderManager::getActiveOrders(const string& userId) const {
    vector<Order> activeOrders;
    for (const auto& order : orders) {
        if (order.getUserId() == userId && order.getStatus() == 0) { // ACTIVE
            activeOrders.push_back(order);
        }
    }
    return activeOrders;
}

vector<Order> OrderManager::getUserOrders(const string& userId) const {
    vector<Order> userOrders;
    for (const auto& order : orders) {
        if (order.getUserId() == userId) {
            userOrders.push_back(order);
        }
    }
    return userOrders;
}

bool OrderManager::hasActiveOrderForBook(const string& userId, int bookId) const {
    for (const auto& order : orders) {
        if (order.getUserId() == userId &&
            order.getBookId() == bookId &&
            order.getStatus() == 0 && // ACTIVE
            order.getType() == 0) { // BORROW
            return true;
        }
    }
    return false;
}

int OrderManager::getIntInput(const string& prompt, bool allowZero) const {
    int input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.good() && (allowZero || input != 0)) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
        cout << "Input error. Please enter an integer" << (allowZero ? "" : " (non-zero)") << "." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

char OrderManager::getCharInput(const string& prompt, const string& validChars) const {
    char inputChar;
    string lineInput;
    while (true) {
        cout << prompt << " (" << validChars[0] << "/" << validChars[1] << "): ";
        getline(cin, lineInput);
        if (lineInput.length() == 1) {
            inputChar = tolower(lineInput[0]);
            if (validChars.find(inputChar) != string::npos) {
                return inputChar;
            }
        }
        cout << "Invalid input. Please enter '" << validChars[0] << "' or '" << validChars[1] << "'." << endl;
    }
}

string OrderManager::getStringLineInput(const string& prompt) const {
    string input;
    cout << prompt;
    getline(cin, input);
    return input;
}