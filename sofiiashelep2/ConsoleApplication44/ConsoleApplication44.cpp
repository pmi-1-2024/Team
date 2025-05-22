#include <iostream>
#include <string>
#include <locale>
using namespace std;

// ==================== КЛАС BOOK ====================
class Book {
private:
    int id;
    string title;
    string author;
    string genre;
    string publisher;
    int year;
    double paperPrice;
    double electronicPrice;
    bool available;

public:
    // Конструктори
    Book() {
        id = 0;
        title = "";
        author = "";
        genre = "";
        publisher = "";
        year = 0;
        paperPrice = 0.0;
        electronicPrice = 0.0;
        available = true;
    }

    Book(int id, string title, string author, string genre, string publisher,
        int year, double paperPrice, double electronicPrice, bool available = true) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->publisher = publisher;
        this->year = year;
        this->paperPrice = paperPrice;
        this->electronicPrice = electronicPrice;
        this->available = available;
    }

    // Геттери
    int getId() { return id; }
    string getTitle() { return title; }
    string getAuthor() { return author; }
    string getGenre() { return genre; }
    string getPublisher() { return publisher; }
    int getYear() { return year; }
    double getPaperPrice() { return paperPrice; }
    double getElectronicPrice() { return electronicPrice; }
    bool isAvailable() { return available; }

    // Сеттери
    void setAvailable(bool available) { this->available = available; }
    void setTitle(string title) { this->title = title; }
    void setAuthor(string author) { this->author = author; }
    void setGenre(string genre) { this->genre = genre; }
    void setPublisher(string publisher) { this->publisher = publisher; }
    void setYear(int year) { this->year = year; }
    void setPaperPrice(double price) { this->paperPrice = price; }
    void setElectronicPrice(double price) { this->electronicPrice = price; }

    // Методи для відображення
    void displayInfo() {
        cout << "ID: " << id << endl;
        cout << "Назва: " << title << endl;
        cout << "Автор: " << author << endl;
        cout << "Жанр: " << genre << endl;
        cout << "Видавництво: " << publisher << endl;
        cout << "Рiк: " << year << endl;
        cout << "Цiна паперової: " << paperPrice << " грн" << endl;
        cout << "Цiна електронної: " << electronicPrice << " грн" << endl;
        cout << "Доступна: " << (available ? "Так" : "Ні") << endl;
        cout << "------------------------" << endl;
    }

    string toString() {
        return title + " - " + author + " (" + to_string(year) + ")";
    }
};

// ==================== КЛАС ORDER ====================
class Order {
private:
    int orderId;
    int bookId;
    string bookTitle;
    string orderDate;
    string returnDate;
    string orderType;
    double price;
    bool active;
    bool returned;

public:
    // Конструктори
    Order() {
        orderId = 0;
        bookId = 0;
        bookTitle = "";
        orderDate = "";
        returnDate = "";
        orderType = "";
        price = 0.0;
        active = false;
        returned = false;
    }

    Order(int orderId, int bookId, string bookTitle, string orderDate, string orderType, double price = 0.0) {
        this->orderId = orderId;
        this->bookId = bookId;
        this->bookTitle = bookTitle;
        this->orderDate = orderDate;
        this->returnDate = "";
        this->orderType = orderType;
        this->price = price;
        this->returned = false;

        if (orderType == "borrow") {
            this->active = true;
        }
        else {
            this->active = false;
        }
    }

    // Геттери
    int getOrderId() { return orderId; }
    int getBookId() { return bookId; }
    string getBookTitle() { return bookTitle; }
    string getOrderDate() { return orderDate; }
    string getReturnDate() { return returnDate; }
    string getOrderType() { return orderType; }
    double getPrice() { return price; }
    bool isActive() { return active; }
    bool isReturned() { return returned; }

    // Сеттери
    void setReturnDate(string returnDate) { this->returnDate = returnDate; }
    void setActive(bool active) { this->active = active; }
    void setReturned(bool returned) { this->returned = returned; }
    void setPrice(double price) { this->price = price; }

    // Методи для роботи з замовленням
    void returnOrder(string returnDate) {
        if (orderType == "borrow" && active && !returned) {
            this->returnDate = returnDate;
            this->active = false;
            this->returned = true;
        }
    }

    void completeOrder() {
        this->active = false;
    }

    void displayOrderInfo() {
        cout << "ID замовлення: " << orderId << endl;
        cout << "Книга: " << bookTitle << " (ID: " << bookId << ")" << endl;
        cout << "Дата замовлення: " << orderDate << endl;
        cout << "Тип: " << getOrderTypeText() << endl;

        if (price > 0) {
            cout << "Цiна: " << price << " грн" << endl;
        }

        if (orderType == "borrow") {
            cout << "Статус: " << (active ? "Активне" : "Завершене") << endl;
            if (returnDate != "") {
                cout << "Дата повернення: " << returnDate << endl;
            }
        }

        cout << "------------------------" << endl;
    }

    string getOrderTypeText() {
        if (orderType == "borrow") return "Позичка";
        if (orderType == "purchase_paper") return "Покупка (паперова)";
        if (orderType == "purchase_electronic") return "Покупка (електронна)";
        return "Невiдомо";
    }

    bool canBeReturned() {
        return (orderType == "borrow" && active && !returned);
    }
};

// ==================== КЛАС LIBRARY ====================
class Library {
private:
    Book books[100];
    Order orders[500];
    int bookCount;
    int orderCount;
    int nextOrderId;

public:
    Library() {
        bookCount = 0;
        orderCount = 0;
        nextOrderId = 1;
        initializeBooks();
    }

    void initializeBooks() {
        addBook(Book(1, "Кобзар", "Тарас Шевченко", "Поезiя", "Наукова думка", 2015, 120.0, 80.0));
        addBook(Book(2, "Лiсова пiсня", "Леся Українка", "Драма", "Школа", 2018, 95.0, 65.0));
        addBook(Book(3, "Захар Беркут", "Iван Франко", "Icторичний роман", "Веселка", 2017, 150.0, 100.0));
        addBook(Book(4, "Тигролови", "Iван Багряний", "Пригодницький роман", "Країна Мрiй", 2019, 180.0, 120.0));
        addBook(Book(5, "Мiсто", "Валер'ян Пiдмогильний", "Роман", "Фолiо", 2016, 140.0, 90.0));
        addBook(Book(6, "Harry Potter", "J.K. Rowling", "Фентезi", "Bloomsbury", 2020, 300.0, 200.0));
        addBook(Book(7, "1984", "George Orwell", "Антиутопiя", "Penguin", 2021, 250.0, 170.0));
    }

    void addBook(Book book) {
        if (bookCount < 100) {
            books[bookCount] = book;
            bookCount++;
        }
    }

    void displayAllBooks() {
        cout << "\n=== ВСI КНИГИ В БIБЛIОТЕЦI ===" << endl;
        for (int i = 0; i < bookCount; i++) {
            books[i].displayInfo();
        }
    }

    void displayAvailableBooks() {
        cout << "\n=== ДОСТУПНI КНИГИ ===" << endl;
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].isAvailable()) {
                books[i].displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає доступних книг." << endl;
        }
    }

    Book* findBookById(int id) {
        for (int i = 0; i < bookCount; i++) {
            if (books[i].getId() == id) {
                return &books[i];
            }
        }
        return nullptr;
    }

    void displayBooksByGenre(string genre) {
        cout << "\n=== КНИГИ ЗА ЖАНРОМ: " << genre << " ===" << endl;
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].isAvailable() && books[i].getGenre() == genre) {
                books[i].displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає доступних книг цього жанру." << endl;
        }
    }

    void displayBooksByPublisher(string publisher) {
        cout << "\n=== КНИГИ ВИДАВНИЦТВА: " << publisher << " ===" << endl;
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].isAvailable() && books[i].getPublisher() == publisher) {
                books[i].displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає доступних книг цього видавництва." << endl;
        }
    }

    void displayBooksByYear(int year, bool after) {
        if (after) {
            cout << "\n=== КНИГИ ПIСЛЯ " << year << " РОКУ ===" << endl;
        }
        else {
            cout << "\n=== КНИГИ ДО " << year << " РОКУ ===" << endl;
        }

        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            bool yearMatch = after ? (books[i].getYear() >= year) : (books[i].getYear() <= year);
            if (books[i].isAvailable() && yearMatch) {
                books[i].displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає доступних книг за вказаний перiод." << endl;
        }
    }

    void displayBooksByAuthor(string author) {
        cout << "\n=== КНИГИ АВТОРА: " << author << " ===" << endl;
        bool found = false;
        for (int i = 0; i < bookCount; i++) {
            if (books[i].isAvailable() && books[i].getAuthor() == author) {
                books[i].displayInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає доступних книг цього автора." << endl;
        }
    }

    bool canBorrowBook(int userId) {
        return getActiveOrdersCount(userId) < 3;
    }

    int getActiveOrdersCount(int userId) {
        int count = 0;
        for (int i = 0; i < orderCount; i++) {
            if (orders[i].isActive()) {
                count++;
            }
        }
        return count;
    }

    bool borrowBook(int bookId, int userId, string date) {
        Book* book = findBookById(bookId);
        if (book == nullptr) {
            cout << "Книгу не знайдено!" << endl;
            return false;
        }

        if (!book->isAvailable()) {
            cout << "Книга недоступна для позики!" << endl;
            return false;
        }

        if (!canBorrowBook(userId)) {
            cout << "Досягнуто лiмiт активних замовлень (3)!" << endl;
            return false;
        }

        if (orderCount < 500) {
            orders[orderCount] = Order(nextOrderId++, bookId, book->getTitle(), date, "borrow");
            orderCount++;
            book->setAvailable(false);
            cout << "Книгу успiшно позичено!" << endl;
            return true;
        }

        cout << "Неможливо створити замовлення!" << endl;
        return false;
    }

    bool purchaseBook(int bookId, int userId, string date, string type) {
        Book* book = findBookById(bookId);
        if (book == nullptr) {
            cout << "Книгу не знайдено!" << endl;
            return false;
        }

        if (!book->isAvailable()) {
            cout << "Книга недоступна для покупки!" << endl;
            return false;
        }

        double price;
        string orderType;

        if (type == "paper") {
            price = book->getPaperPrice();
            orderType = "purchase_paper";
        }
        else if (type == "electronic") {
            price = book->getElectronicPrice();
            orderType = "purchase_electronic";
        }
        else {
            cout << "Невiрний тип покупки!" << endl;
            return false;
        }

        if (orderCount < 500) {
            orders[orderCount] = Order(nextOrderId++, bookId, book->getTitle(), date, orderType, price);
            orderCount++;

            if (type == "paper") {
                book->setAvailable(false);
            }

            cout << "Книгу успiшно придбано за " << price << " грн!" << endl;
            return true;
        }

        cout << "Неможливо створити замовлення!" << endl;
        return false;
    }

    Order* findOrderById(int orderId) {
        for (int i = 0; i < orderCount; i++) {
            if (orders[i].getOrderId() == orderId) {
                return &orders[i];
            }
        }
        return nullptr;
    }

    bool returnBook(int orderId, string returnDate) {
        Order* order = findOrderById(orderId);
        if (order == nullptr) {
            cout << "Замовлення не знайдено!" << endl;
            return false;
        }

        if (!order->canBeReturned()) {
            cout << "Це замовлення не можна повернути!" << endl;
            return false;
        }

        order->returnOrder(returnDate);

        Book* book = findBookById(order->getBookId());
        if (book != nullptr) {
            book->setAvailable(true);
        }

        cout << "Книгу успiшно повернено!" << endl;
        return true;
    }

    void displayOrderHistory(int userId) {
        cout << "\n=== IСТОРIЯ ЗАМОВЛЕНЬ ===" << endl;
        bool found = false;
        for (int i = 0; i < orderCount; i++) {
            orders[i].displayOrderInfo();
            found = true;
        }
        if (!found) {
            cout << "Немає замовлень." << endl;
        }
    }

    void displayActiveOrders(int userId) {
        cout << "\n=== АКТИВНI ЗАМОВЛЕННЯ ===" << endl;
        bool found = false;
        for (int i = 0; i < orderCount; i++) {
            if (orders[i].isActive()) {
                orders[i].displayOrderInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає активних замовлень." << endl;
        }
    }

    void displayCompletedOrders(int userId) {
        cout << "\n=== ЗАВЕРШЕНI ЗАМОВЛЕННЯ ===" << endl;
        bool found = false;
        for (int i = 0; i < orderCount; i++) {
            if (!orders[i].isActive()) {
                orders[i].displayOrderInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "Немає завершених замовлень." << endl;
        }
    }

    void displayAllOrders(int userId) {
        cout << "\n=== ВСI ЗАМОВЛЕННЯ ===" << endl;
        bool found = false;
        for (int i = 0; i < orderCount; i++) {
            orders[i].displayOrderInfo();
            found = true;
        }
        if (!found) {
            cout << "Немає замовлень." << endl;
        }
    }

    void displayMainMenu() {
        cout << "\n========== БIБЛIОТЕКА ==========" << endl;
        cout << "1. Взяти книгу з бiблiотеки" << endl;
        cout << "2. Повернути замовлення" << endl;
        cout << "3. Придбати книгу" << endl;
        cout << "4. Переглянути iсторiю замовлень" << endl;
        cout << "5. Переглянути активнi замовлення" << endl;
        cout << "6. Переглянути завершенi замовлення" << endl;
        cout << "0. Вихiд" << endl;
        cout << "Ваш вибiр: ";
    }

    void displayFilterMenu() {
        cout << "\n=== ФIЛЬТРИ ===" << endl;
        cout << "1. За жанром" << endl;
        cout << "2. За видавництвом" << endl;
        cout << "3. За роком видання" << endl;
        cout << "4. За автором" << endl;
        cout << "0. Назад" << endl;
        cout << "Ваш вибiр: ";
    }

    int getBookCount() { return bookCount; }
    int getOrderCount() { return orderCount; }
};

// ==================== КЛАС MENUHANDLER ====================
class MenuHandler {
private:
    Library library;
    int currentUserId;

public:
    MenuHandler() {
        currentUserId = 1;
    }

    string getCurrentDate() {
        return "2024-01-15";
    }

    void waitForEnter() {
        cout << "\nНатиснiть Enter для продовження...";
        cin.ignore();
        cin.get();
    }

    int getIntInput() {
        int input;
        while (!(cin >> input)) {
            cout << "Помилка! Введiть число: ";
            cin.clear();
            cin.ignore(10000, '\n');
        }
        cin.ignore();
        return input;
    }

    string getStringInput() {
        string input;
        getline(cin, input);
        return input;
    }

    void handleBookSelection(bool forBorrow = true) {
        cout << "\nВведiть ID книги (0 - назад): ";
        int bookId = getIntInput();

        if (bookId == 0) return;

        Book* book = library.findBookById(bookId);
        if (book == nullptr) {
            cout << "Книгу з таким ID не знайдено!" << endl;
            waitForEnter();
            return;
        }

        if (!book->isAvailable()) {
            cout << "Ця книга недоступна!" << endl;
            waitForEnter();
            return;
        }

        cout << "\n=== ВИБРАНА КНИГА ===" << endl;
        book->displayInfo();

        cout << "Пiдтвердити? (1 - так, 0 - ні): ";
        int confirm = getIntInput();

        if (confirm == 1) {
            if (forBorrow) {
                library.borrowBook(bookId, currentUserId, getCurrentDate());
            }
            waitForEnter();
        }
    }

    void handleFilteredBookDisplay() {
        int filterChoice;
        do {
            library.displayFilterMenu();
            filterChoice = getIntInput();

            switch (filterChoice) {
            case 1: {
                cout << "Введiть жанр: ";
                string genre = getStringInput();
                library.displayBooksByGenre(genre);
                handleBookSelection(true);
                break;
            }
            case 2: {
                cout << "Введiть видавництво: ";
                string publisher = getStringInput();
                library.displayBooksByPublisher(publisher);
                handleBookSelection(true);
                break;
            }
            case 3: {
                cout << "Введiть рiк: ";
                int year = getIntInput();
                cout << "1 - пiсля цього року, 2 - до цього року: ";
                int yearChoice = getIntInput();
                library.displayBooksByYear(year, yearChoice == 1);
                handleBookSelection(true);
                break;
            }
            case 4: {
                cout << "Введiть автора: ";
                string author = getStringInput();
                library.displayBooksByAuthor(author);
                handleBookSelection(true);
                break;
            }
            case 0:
                return;
            default:
                cout << "Невiрний вибір!" << endl;
                waitForEnter();
                break;
            }
        } while (filterChoice != 0);
    }

    void handleBorrowBook() {
        if (!library.canBorrowBook(currentUserId)) {
            cout << "Ви досягли лiмiту активних замовлень (3)!" << endl;
            waitForEnter();
            return;
        }

        int choice;
        do {
            cout << "\n=== ПОЗИКА КНИГИ ===" << endl;
            cout << "1. Переглянути всi доступнi книги" << endl;
            cout << "2. Застосувати фiльтри" << endl;
            cout << "0. Назад" << endl;
            cout << "Ваш вибiр: ";
            choice = getIntInput();

            switch (choice) {
            case 1:
                library.displayAvailableBooks();
                handleBookSelection(true);
                break;
            case 2:
                handleFilteredBookDisplay();
                break;
            case 0:
                return;
            default:
                cout << "Невiрний вибiр!" << endl;
                waitForEnter();
                break;
            }
        } while (choice != 0);
    }

    void handleReturnBook() {
        cout << "\n=== ПОВЕРНЕННЯ КНИГИ ===" << endl;
        library.displayActiveOrders(currentUserId);

        cout << "\nВведiть ID замовлення для повернення (0 - назад): ";
        int orderId = getIntInput();

        if (orderId == 0) return;

        Order* order = library.findOrderById(orderId);
        if (order == nullptr) {
            cout << "Замовлення не знайдено!" << endl;
            waitForEnter();
            return;
        }

        if (!order->canBeReturned()) {
            cout << "Це замовлення не можна повернути!" << endl;
            waitForEnter();
            return;
        }

        cout << "\n=== IНФОРМАЦIЯ ПРО ЗАМОВЛЕННЯ ===" << endl;
        order->displayOrderInfo();

        cout << "Пiдтвердити повернення? (1 - так, 0 - ні): ";
        int confirm = getIntInput();

        if (confirm == 1) {
            library.returnBook(orderId, getCurrentDate());
            waitForEnter();
        }
    }

    void handlePurchaseSelection() {
        cout << "\nВведiть ID книги для покупки (0 - назад): ";
        int bookId = getIntInput();

        if (bookId == 0) return;

        Book* book = library.findBookById(bookId);
        if (book == nullptr) {
            cout << "Книгу з таким ID не знайдено!" << endl;
            waitForEnter();
            return;
        }

        if (!book->isAvailable()) {
            cout << "Ця книга недоступна!" << endl;
            waitForEnter();
            return;
        }

        cout << "\n=== ВИБРАНА КНИГА ===" << endl;
        book->displayInfo();

        cout << "\n=== ТИП ПОКУПКИ ===" << endl;
        cout << "1. Паперова версiя" << endl;
        cout << "2. Електронна версiя" << endl;
        cout << "Ваш вибiр: ";
        int typeChoice = getIntInput();

        string purchaseType;
        if (typeChoice == 1) {
            purchaseType = "paper";
            cout << "Цiна паперової версiї: " << book->getPaperPrice() << " грн" << endl;
        }
        else if (typeChoice == 2) {
            purchaseType = "electronic";
            cout << "Цiна електронної версiї: " << book->getElectronicPrice() << " грн" << endl;
        }
        else {
            cout << "Невiрний вибiр!" << endl;
            waitForEnter();
            return;
        }

        cout << "Пiдтвердити покупку? (1 - так, 0 - нi): ";
        int confirm = getIntInput();

        if (confirm == 1) {
            library.purchaseBook(bookId, currentUserId, getCurrentDate(), purchaseType);
            waitForEnter();
        }
    }

    void handleFilteredPurchaseDisplay() {
        int filterChoice;
        do {
            library.displayFilterMenu();
            filterChoice = getIntInput();

            switch (filterChoice) {
            case 1: {
                cout << "Введiть жанр: ";
                string genre = getStringInput();
                library.displayBooksByGenre(genre);
                handlePurchaseSelection();
                break;
            }
            case 2: {
                cout << "Введiть видавництво: ";
                string publisher = getStringInput();
                library.displayBooksByPublisher(publisher);
                handlePurchaseSelection();
                break;
            }
            case 3: {
                cout << "Введiть рiк: ";
                int year = getIntInput();
                cout << "1 - пiсля цього року, 2 - до цього року: ";
                int yearChoice = getIntInput();
                library.displayBooksByYear(year, yearChoice == 1);
                handlePurchaseSelection();
                break;
            }
            case 4: {
                cout << "Введiть автора: ";
                string author = getStringInput();
                library.displayBooksByAuthor(author);
                handlePurchaseSelection();
                break;
            }
            case 0:
                return;
            default:
                cout << "Невiрний вибiр!" << endl;
                waitForEnter();
                break;
            }
        } while (filterChoice != 0);
    }

    void handlePurchaseBook() {
        int choice;
        do {
            cout << "\n=== ПОКУПКА КНИГИ ===" << endl;
            cout << "1. Переглянути всi доступнi книги" << endl;
            cout << "2. Застосувати фiльтри" << endl;
            cout << "0. Назад" << endl;
            cout << "Ваш вибiр: ";
            choice = getIntInput();

            switch (choice) {
            case 1:
                library.displayAvailableBooks();
                handlePurchaseSelection();
                break;
            case 2:
                handleFilteredPurchaseDisplay();
                break;
            case 0:
                return;
            default:
                cout << "Невiрний вибiр!" << endl;
                waitForEnter();
                break;
            }
        } while (choice != 0);
    }

    void handleOrderHistory() {
        int choice;
        do {
            cout << "\n=== IСТОРIЯ ЗАМОВЛЕНЬ ===" << endl;
            cout << "1. Всi замовлення" << endl;
            cout << "2. Активнi замовлення" << endl;
            cout << "3. Завершенi замовлення" << endl;
            cout << "0. Назад" << endl;
            cout << "Ваш вибiр: ";
            choice = getIntInput();

            switch (choice) {
            case 1:
                library.displayAllOrders(currentUserId);
                waitForEnter();
                break;
            case 2:
                library.displayActiveOrders(currentUserId);
                waitForEnter();
                break;
            case 3:
                library.displayCompletedOrders(currentUserId);
                waitForEnter();
                break;
            case 0:
                return;
            default:
                cout << "Невiрний вибiр!" << endl;
                waitForEnter();
                break;
            }
        } while (choice != 0);
    }

    void handleMainMenu() {
        int choice;
        do {
            library.displayMainMenu();
            choice = getIntInput();

            switch (choice) {
            case 1:
                handleBorrowBook();
                break;
            case 2:
                handleReturnBook();
                break;
            case 3:
                handlePurchaseBook();
                break;
            case 4:
                handleOrderHistory();
                break;
            case 5:
                library.displayActiveOrders(currentUserId);
                waitForEnter();
                break;
            case 6:
                library.displayCompletedOrders(currentUserId);
                waitForEnter();
                break;
            case 0:
                cout << "До побачення!" << endl;
                break;
            default:
                cout << "Невiрний вибiр! Спробуйте ще раз." << endl;
                waitForEnter();
                break;
            }
        } while (choice != 0);
    }

    void run() {
        cout << "Ласкаво просимо до бiблiотеки!" << endl;
        handleMainMenu();
    }
};

// ==================== ГОЛОВНА ФУНКЦІЯ ====================
int main() {
	setlocale(LC_ALL, "ukr");
    MenuHandler menuHandler;
    menuHandler.run();
    return 0;
}
