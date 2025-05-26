#include "BookManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <limits> 


using namespace std; 

const string BOOKS_FILE = "books.txt";
const string AUTHORS_FILE = "authors.txt";
const string PUBLISHERS_FILE = "publishers.txt";
const string GENRES_FILE = "genres.txt";

namespace {
    template<typename T>
    void loadFromFile(const string& filename, vector<T>& items) {
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        T item;
        while (file >> item) {
            items.push_back(item);
        }
        file.close();
    }

    template<typename T>
    void saveToFile(const string& filename, const vector<T>& items) {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cerr << "Помилка: Неможливо відкрити " << filename << " для збереження." << endl;
            return;
        }
        for (const auto& item : items) {
            file << item;
        }
        file.close();
    }
}

BookManager::BookManager() {
    loadAllData();
}

BookManager::~BookManager() {
    saveAllData();
    cout << "Дані збережено. Вихід з програми." << endl;
}

void BookManager::loadAllData() {
    loadFromFile(BOOKS_FILE, books);
    loadFromFile(AUTHORS_FILE, authors);
    loadFromFile(PUBLISHERS_FILE, publishers);
    loadFromFile(GENRES_FILE, genres);
    cout << "Дані завантажено." << endl;
}

void BookManager::saveAllData() const {
    saveBooks();
    saveAuthors();
    savePublishers();
    saveGenres();
}

void BookManager::saveBooks() const { saveToFile(BOOKS_FILE, books); }
void BookManager::saveAuthors() const { saveToFile(AUTHORS_FILE, authors); }
void BookManager::savePublishers() const { saveToFile(PUBLISHERS_FILE, publishers); }
void BookManager::saveGenres() const { saveToFile(GENRES_FILE, genres); }


void BookManager::addBook() {
    Book b;
    int id_val;
    string authorName_val, publisherName_val;
    string title_val, format_val, genre_names_str_val;
    double rating_val;
    vector<string> genre_names_vec_val;

    cout << "Додавання нової книги ---\n";
    cout << "ID: ";
    cin >> id_val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Назва: ";
    getline(cin, title_val);

    cout << "Ім'я автора: ";
    getline(cin, authorName_val);

    cout << "Назва видавництва: ";
    getline(cin, publisherName_val);

    cout << "Назви жанрів (наприклад, Фентезі;Наукова фантастика або порожньо, розділені крапкою з комою ';'): ";
    getline(cin, genre_names_str_val);

    cout << "Рейтинг: ";
    cin >> rating_val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Формат (Паперова/Електронна): ";
    getline(cin, format_val);

    b.setId(id_val);
    b.setTitle(title_val);
    b.setAuthorName(authorName_val);
    b.setPublisherName(publisherName_val);
    b.setRating(rating_val);
    b.setFormat(format_val);

    if (!genre_names_str_val.empty()) {
        stringstream ss(genre_names_str_val);
        string item_str;
        while (getline(ss, item_str, ';')) {
            if (!item_str.empty()) {
                genre_names_vec_val.push_back(item_str);
            }
        }
    }
    b.setGenreNames(genre_names_vec_val);

    books.push_back(b);
    saveBooks();
    cout << "Книгу додано." << endl;
}

void BookManager::viewBooks() const {
    if (books.empty()) {
        cout << "У бібліотеці немає книг." << endl;
        return;
    }
    cout << "\n--- Усі книги ---\n";
    for (size_t i = 0; i < books.size(); ++i) {
        cout << books[i]; 
    }
}

void BookManager::findBook() {
    string title_query;
    cout << "Введіть назву (або частину назви) для пошуку: ";
    getline(cin, title_query);
    bool found = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getTitle().find(title_query) != string::npos) {
            cout << books[i];
            found = true;
        }
    }
    if (!found) cout << "Книг, що відповідають вашому запиту, не знайдено." << endl;
}

void BookManager::modifyBook() {
    int id_to_update;
    cout << "Введіть ID книги для оновлення: ";
    cin >> id_to_update;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool found_book = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getId() == id_to_update) {
            found_book = true;
            cout << "Знайдено книгу. Поточні дані для \"" << books[i].getTitle() << "\"\n";
            cout << "Введіть нові дані (натисніть Enter, щоб зберегти поточні для текстових полів, ID " << books[i].getId() << " не можна змінити):\n";

            string temp_str;
            double temp_double;

            cout << "Нова назва (поточна: " << books[i].getTitle() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) books[i].setTitle(temp_str);

            cout << "Нове ім'я автора (поточне: " << books[i].getAuthorName() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                books[i].setAuthorName(temp_str);
            }

            cout << "Нова назва видавництва (поточна: " << books[i].getPublisherName() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                books[i].setPublisherName(temp_str);
            }

            cout << "Нові назви жанрів (наприклад, Фентезі;Наукова фантастика, поточні: " << books[i].getGenreNamesCSV() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                vector<string> new_genre_names;
                stringstream ss(temp_str);
                string item_str;
                while (getline(ss, item_str, ';')) {
                    if (!item_str.empty()) {
                        new_genre_names.push_back(item_str);
                    }
                }
                books[i].setGenreNames(new_genre_names);
            }

            cout << "Новий рейтинг (поточний: " << books[i].getRating() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                stringstream converter(temp_str);
                if (converter >> temp_double) books[i].setRating(temp_double);
            }

            cout << "Новий формат (поточний: " << books[i].getFormat() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) books[i].setFormat(temp_str);

            saveBooks();
            cout << "Книгу оновлено." << endl;
            break;
        }
    }
    if (!found_book) cout << "Книгу з ID " << id_to_update << " не знайдено." << endl;
}


void BookManager::removeBook() {
    int id_to_delete;
    cout << "Введіть ID книги для видалення: ";
    cin >> id_to_delete;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<Book> temp_books;
    bool removed = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getId() != id_to_delete) {
            temp_books.push_back(books[i]);
        }
        else {
            removed = true;
        }
    }

    if (removed) {
        books = temp_books;
        saveBooks();
        cout << "Книгу видалено." << endl;
    }
    else {
        cout << "Книгу з ID " << id_to_delete << " не знайдено." << endl;
    }
}

void BookManager::addAuthor() {
    Author author;
    int id_val;
    string name_val;
    cout << "ID нового автора: ";
    cin >> id_val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Ім'я автора: ";
    getline(cin, name_val);
    author.setId(id_val);
    author.setName(name_val);
    authors.push_back(author);
    saveAuthors();
    cout << "Автора додано." << endl;
}

void BookManager::viewAuthors() const {
    if (authors.empty()) { cout << "Авторів немає." << endl; return; }
    cout << "\n--- Усі автори ---\n";
    for (size_t i = 0; i < authors.size(); ++i) {
        cout << authors[i].getId() << " " << authors[i].getName() << endl;
    }
}

void BookManager::modifyAuthor() {
    int id_val;
    string name_val;
    cout << "Введіть ID автора для оновлення: ";
    cin >> id_val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    bool found = false;
    for (size_t i = 0; i < authors.size(); ++i) {
        if (authors[i].getId() == id_val) {
            cout << "Поточне ім'я: " << authors[i].getName() << ". Нове ім'я: ";
            getline(cin, name_val);
            if (!name_val.empty()) authors[i].setName(name_val);
            found = true;
            break;
        }
    }
    if (found) { saveAuthors(); cout << "Автора оновлено." << endl; }
    else { cout << "Автора не знайдено." << endl; }
}

void BookManager::removeAuthor() {
    int id_val;
    cout << "Введіть ID автора для видалення: ";
    cin >> id_val;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

    vector<Author> temp_authors;
    bool removed = false;
    for (size_t i = 0; i < authors.size(); ++i) {
        if (authors[i].getId() != id_val) {
            temp_authors.push_back(authors[i]);
        }
        else {
            removed = true;
        }
    }
    if (removed) {
        authors = temp_authors;
        saveAuthors();
        cout << "Автора видалено." << endl;
    }
    else { cout << "Автора не знайдено." << endl; }
}

void BookManager::addPublisher() {
    Publisher p; int id; string name;
    cout << "ID нового видавництва: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Назва видавництва: "; getline(cin, name);
    p.setId(id); p.setName(name);
    publishers.push_back(p);
    savePublishers();
    cout << "Видавництво додано." << endl;
}
void BookManager::viewPublishers() const {
    if (publishers.empty()) { cout << "Видавництв немає." << endl; return; }
    cout << "\n--- Усі видавництва ---\n";
    for (size_t i = 0; i < publishers.size(); ++i) {
        cout << publishers[i].getId() << " " << publishers[i].getName() << endl;
    }
}
void BookManager::modifyPublisher() {
    int id; string name;
    cout << "Введіть ID видавництва для оновлення: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    bool found = false;
    for (size_t i = 0; i < publishers.size(); ++i) {
        if (publishers[i].getId() == id) {
            cout << "Поточна назва: " << publishers[i].getName() << ". Нова назва: ";
            getline(cin, name);
            if (!name.empty()) publishers[i].setName(name);
            found = true;
            break;
        }
    }
    if (found) { savePublishers(); cout << "Видавництво оновлено." << endl; }
    else { cout << "Видавництво не знайдено." << endl; }
}
void BookManager::removePublisher() {
    int id;
    cout << "Введіть ID видавництва для видалення: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    vector<Publisher> temp_pubs;
    bool removed = false;
    for (size_t i = 0; i < publishers.size(); ++i) {
        if (publishers[i].getId() != id) temp_pubs.push_back(publishers[i]);
        else removed = true;
    }
    if (removed) { publishers = temp_pubs; savePublishers(); cout << "Видавництво видалено." << endl; }
    else { cout << "Видавництво не знайдено." << endl; }
}

void BookManager::addGenre() {
    Genre g; int id; string name;
    cout << "ID нового жанру: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Назва жанру: "; getline(cin, name);
    g.setId(id); g.setName(name);
    genres.push_back(g);
    saveGenres();
    cout << "Жанр додано." << endl;
}

void BookManager::viewGenres() const {
    if (genres.empty()) { cout << "Доступних жанрів немає." << endl; return; }
    cout << "\n--- Усі жанри ---\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        cout << genres[i].getId() << " " << genres[i].getName() << endl;
    }
}
void BookManager::modifyGenre() {
    int id; string name;
    cout << "Введіть ID жанру для оновлення: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    bool found = false;
    for (size_t i = 0; i < genres.size(); ++i) {
        if (genres[i].getId() == id) {
            cout << "Поточна назва: " << genres[i].getName() << ". Нова назва: ";
            getline(cin, name);
            if (!name.empty()) genres[i].setName(name);
            found = true;
            break;
        }
    }
    if (found) { saveGenres(); cout << "Жанр оновлено." << endl; }
    else { cout << "Жанр не знайдено." << endl; }
}
void BookManager::removeGenre() {
    int id;
    cout << "Введіть ID жанру для видалення: "; cin >> id;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    vector<Genre> temp_genres;
    bool removed = false;
    for (size_t i = 0; i < genres.size(); ++i) {
        if (genres[i].getId() != id) temp_genres.push_back(genres[i]);
        else removed = true;
    }
    if (removed) { genres = temp_genres; saveGenres(); cout << "Жанр видалено." << endl; }
    else { cout << "Жанр не знайдено." << endl; }
}

void BookManager::exportToCSV(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Помилка: Неможливо відкрити " << filename << " для експорту в CSV." << endl;
        return;
    }
    file << "ID,Назва,Ім'яАвтора,НазваВидавництва,НазвиЖанрів,Рейтинг,Формат\n"; 
    for (size_t i = 0; i < books.size(); ++i) {
        file << books[i].getId() << ",\"" << books[i].getTitle() << "\","
            << "\"" << books[i].getAuthorName() << "\",\"" << books[i].getPublisherName() << "\",\""
            << books[i].getGenreNamesCSV() << "\"," << books[i].getRating() << ",\""
            << books[i].getFormat() << "\"\n";
    }
    file.close();
    cout << "Книги експортовано до " << filename << "." << endl;
}

int BookManager::displayMainMenu() const {
    int choice = 0;
    cout << "\n--- Меню бібліотеки ---\n"
        << "1. Керування книгами\n"
        << "2. Керування авторами\n"
        << "3. Керування видавництвами\n"
        << "4. Керування жанрами\n"
        << "5. Експорт книг до CSV\n"
        << "6. Вихід\n"
        << "Введіть вибір: ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        return -1;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    return choice;
}

void BookManager::run() {
    bool running = true;
    while (running) {
        int choice = displayMainMenu();
        int subChoice = 0;

        switch (choice) {
        case 1:
            cout << "\n--- Меню книг ---\n"
                << "1. Додати книгу\n"
                << "2. Переглянути всі книги\n"
                << "3. Знайти книгу за назвою\n"
                << "4. Оновити книгу за ID\n"
                << "5. Видалити книгу за ID\n"
                << "0. Повернутися до головного меню\n"
                << "Введіть вибір: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); subChoice = -1; } 
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); } 
            switch (subChoice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: findBook(); break;
            case 4: modifyBook(); break;
            case 5: removeBook(); break;
            case 0: break;
            default: cout << "Невірний вибір у меню книг." << endl;
            }
            break;
        case 2:
            cout << "\n--- Меню авторів ---\n"
                << "1. Додати автора\n"
                << "2. Переглянути всіх авторів\n"
                << "3. Оновити автора за ID\n"
                << "4. Видалити автора за ID\n"
                << "0. Повернутися до головного меню\n"
                << "Введіть вибір: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); subChoice = -1; } 
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); }
            switch (subChoice) {
            case 1: addAuthor(); break;
            case 2: viewAuthors(); break;
            case 3: modifyAuthor(); break;
            case 4: removeAuthor(); break;
            case 0: break;
            default: cout << "Невірний вибір у меню авторів." << endl;
            }
            break;
        case 3:
            cout << "\n--- Меню видавництв ---\n"
                << "1. Додати видавництво\n"
                << "2. Переглянути всі видавництва\n"
                << "3. Оновити видавництво за ID\n"
                << "4. Видалити видавництво за ID\n"
                << "0. Повернутися до головного меню\n"
                << "Введіть вибір: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); subChoice = -1; } 
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); } 
            switch (subChoice) {
            case 1: addPublisher(); break;
            case 2: viewPublishers(); break;
            case 3: modifyPublisher(); break;
            case 4: removePublisher(); break;
            case 0: break;
            default: cout << "Невірний вибір у меню видавництв." << endl;
            }
            break;
        case 4:
            cout << "\n--- Меню жанрів ---\n"
                << "1. Додати жанр\n"
                << "2. Переглянути всі жанри\n"
                << "3. Оновити жанр за ID\n"
                << "4. Видалити жанр за ID\n"
                << "0. Повернутися до головного меню\n"
                << "Введіть вибір: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); subChoice = -1; } 
            else { cin.ignore(numeric_limits<streamsize>::max(), '\n'); } 
            switch (subChoice) {
            case 1: addGenre(); break;
            case 2: viewGenres(); break;
            case 3: modifyGenre(); break;
            case 4: removeGenre(); break;
            case 0: break;
            default: cout << "Невірний вибір у меню жанрів." << endl;
            }
            break;
        case 5:
            exportToCSV("library_export.csv");
            break;
        case 6:
            running = false;
            break;
        case -1: 
            cout << "Невірний вибір у головному меню. Будь ласка, введіть число." << endl;
            break;
        default:
            cout << "Невірний вибір у головному меню. Будь ласка, спробуйте ще раз." << endl;
            break;
        }
    }
}