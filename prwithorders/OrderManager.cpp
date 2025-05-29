#include "OrderManager.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <cctype>

OrderManager::OrderManager(BookManager* bm) : bookManager(bm) {
    loadOrdersFromFile();
}

OrderManager::~OrderManager() {
    saveOrdersToFile();
}

void OrderManager::loadOrdersFromFile() {
    ifstream file(ORDERS_FILE);
    if (!file.is_open()) {
        return; 
    }

    Order order;
    orders.clear();
    while (file >> order) {
        orders.push_back(order);
    }
    file.close();
}

void OrderManager::saveOrdersToFile() const {
    ofstream file(ORDERS_FILE, ios::trunc);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << ORDERS_FILE << " for saving orders." << endl;
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

    if (order.getType() == OrderType::PURCHASE) {
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

        int bookId = getIntInput("Enter the ID of the book you want to borrow: ");

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
            Order newOrder(currentUser.getId(), bookId, OrderType::BORROW);
            orders.push_back(newOrder);

            bookManager->setBookAvailability(bookId, false);

            cout << "Book \"" << selectedBook->getTitle() << "\" successfully borrowed!" << endl;
            cout << "Order ID: " << newOrder.getOrderId() << endl;
        }

        char choice = getCharInput("Do you want to borrow another book?", "yn");
        continueBorrowing = (choice == 'y');
    }
}

void OrderManager::returnBook(const User& currentUser) {
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

    bool orderFound = false;
    for (auto& order : orders) {
        if (order.getOrderId() == orderId &&
            order.getUserId() == currentUser.getId() &&
            order.canBeReturned()) {

            order.setStatus(OrderStatus::RETURNED);
            order.setReturnDate(order.getCurrentDate());

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
        cout << "\n=== Books Available for Purchase ===" << endl;
        const vector<Book>& allBooks = bookManager->getAllBooks();

        if (allBooks.empty()) {
            cout << "No books available for purchase." << endl;
            return;
        }

        for (const auto& book : allBooks) {
            book.displayInfo(*bookManager);
        }

        int bookId = getIntInput("Enter the ID of the book you want to buy: ");

        const Book* selectedBook = bookManager->findBookById(bookId);

        if (!selectedBook) {
            cout << "Invalid book ID." << endl;
            continue;
        }

        cout << "\n=== Purchase Options for \"" << selectedBook->getTitle() << "\" ===" << endl;

        vector<pair<string, double>> availableFormats;

        if (selectedBook->getPaperPrice() > 0) {
            availableFormats.push_back({ "Paper", selectedBook->getPaperPrice() });
            cout << "1. Paper version - " << selectedBook->getPaperPrice() << " UAH" << endl;
        }

        if (selectedBook->getElectronicPrice() > 0) {
            availableFormats.push_back({ "Electronic", selectedBook->getElectronicPrice() });
            cout << (availableFormats.size()) << ". Electronic version - "
                << selectedBook->getElectronicPrice() << " UAH" << endl;
        }

        if (availableFormats.empty()) {
            cout << "This book is not available for purchase (no prices set)." << endl;
            continue;
        }

        int formatChoice = getIntInput("Choose format (enter number): ");

        if (formatChoice < 1 || formatChoice > static_cast<int>(availableFormats.size())) {
            cout << "Invalid format choice." << endl;
            continue;
        }

        string selectedFormat = availableFormats[formatChoice - 1].first;
        double price = availableFormats[formatChoice - 1].second;

        Order newOrder(currentUser.getId(), bookId, OrderType::PURCHASE, selectedFormat, price);
        orders.push_back(newOrder);

        cout << "Book \"" << selectedBook->getTitle() << "\" (" << selectedFormat
            << " version) successfully purchased for " << price << " UAH!" << endl;
        cout << "Order ID: " << newOrder.getOrderId() << endl;

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
        if (order.getUserId() == userId && order.getStatus() == OrderStatus::ACTIVE) {
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
            order.getStatus() == OrderStatus::ACTIVE &&
            order.getType() == OrderType::BORROW) {
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
    char input_char_val;
    string line_input;
    while (true) {
        cout << prompt << " (" << validChars[0] << "/" << validChars[1] << "): ";
        getline(cin, line_input);
        if (line_input.length() == 1) {
            input_char_val = tolower(line_input[0]);
            if (validChars.find(input_char_val) != string::npos) {
                return input_char_val;
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