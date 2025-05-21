#include "BookManager.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream> 

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
            cerr << "Error: Cannot open " << filename << " for saving." << endl;
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
    cout << "Data saved. Exiting program." << endl;
}

void BookManager::loadAllData() {
    loadFromFile(BOOKS_FILE, books);
    loadFromFile(AUTHORS_FILE, authors);
    loadFromFile(PUBLISHERS_FILE, publishers);
    loadFromFile(GENRES_FILE, genres);
    cout << "Data loaded." << endl;
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
    int id_val, authorId_val, publisherId_val;
    string title_val, format_val, genre_ids_str_val;
    double rating_val;
    vector<int> genre_ids_vec_val;

    cout << "Adding new book ---\n";
    cout << "ID: ";
    cin >> id_val;
    cin.ignore(10000, '\n');

    cout << "Title: ";
    getline(cin, title_val);

    cout << "Author ID: ";
    cin >> authorId_val;
    cin.ignore(10000, '\n');

    cout << "Publisher ID: ";
    cin >> publisherId_val;
    cin.ignore(10000, '\n');

    cout << "Genre IDs (e.g. 1;2;3 or empty, separated by semicolon ';'): ";
    getline(cin, genre_ids_str_val);

    cout << "Rating: ";
    cin >> rating_val;
    cin.ignore(10000, '\n');

    cout << "Format (Paper/Electronic): ";
    getline(cin, format_val);

    b.setId(id_val);
    b.setTitle(title_val);
    b.setAuthorId(authorId_val);
    b.setPublisherId(publisherId_val);
    b.setRating(rating_val);
    b.setFormat(format_val);

    if (!genre_ids_str_val.empty()) {
        stringstream ss(genre_ids_str_val);
        string item_str;
        int item_int;
        while (getline(ss, item_str, ';')) {
            if (!item_str.empty()) {
                stringstream converter(item_str);
                if (converter >> item_int) { 
                    genre_ids_vec_val.push_back(item_int);
                }

            }
        }
    }
    b.setGenreIds(genre_ids_vec_val);

    books.push_back(b);
    saveBooks();
    cout << "Book added." << endl;
}

void BookManager::viewBooks() const {
    if (books.empty()) {
        cout << "No books in the library." << endl;
        return;
    }
    cout << "\n--- All Books ---\n";
    for (size_t i = 0; i < books.size(); ++i) { 
        cout << books[i];
    }
}

void BookManager::findBook() {
    string title_query;
    cout << "Enter title (or part of title) to search: ";
    getline(cin, title_query);
    bool found = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getTitle().find(title_query) != string::npos) {
            cout << books[i];
            found = true;
        }
    }
    if (!found) cout << "No books found matching your query." << endl;
}

void BookManager::modifyBook() {
    int id_to_update;
    cout << "Enter ID of the book to update: ";
    cin >> id_to_update;
    cin.ignore(10000, '\n');

    bool found_book = false;
    for (size_t i = 0; i < books.size(); ++i) {
        if (books[i].getId() == id_to_update) {
            found_book = true;
            cout << "Found book. Current data for \"" << books[i].getTitle() << "\"\n";
            cout << "Enter new data (press Enter to keep current for text fields, ID " << books[i].getId() << " cannot be changed):\n";

            string temp_str;
            int temp_int;
            double temp_double;

            cout << "New Title (current: " << books[i].getTitle() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) books[i].setTitle(temp_str);

            cout << "New Author ID (current: " << books[i].getAuthorId() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                stringstream converter(temp_str);
                if (converter >> temp_int) books[i].setAuthorId(temp_int);
            }

            cout << "New Publisher ID (current: " << books[i].getPublisherId() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                stringstream converter(temp_str);
                if (converter >> temp_int) books[i].setPublisherId(temp_int);
            }

            cout << "New Genre IDs (e.g. 1;2;3, current: " << books[i].getGenreIdCSV() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                vector<int> new_genre_ids;
                stringstream ss(temp_str);
                string item_str;
                int item_int_val;
                while (getline(ss, item_str, ';')) {
                    if (!item_str.empty()) {
                        stringstream converter(item_str);
                        if (converter >> item_int_val) new_genre_ids.push_back(item_int_val);
                    }
                }
                books[i].setGenreIds(new_genre_ids);
            }

            cout << "New Rating (current: " << books[i].getRating() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) {
                stringstream converter(temp_str);
                if (converter >> temp_double) books[i].setRating(temp_double);
            }

            cout << "New Format (current: " << books[i].getFormat() << "): ";
            getline(cin, temp_str);
            if (!temp_str.empty()) books[i].setFormat(temp_str);

            saveBooks();
            cout << "Book updated." << endl;
            break;
        }
    }
    if (!found_book) cout << "Book with ID " << id_to_update << " not found." << endl;
}

void BookManager::removeBook() {
    int id_to_delete;
    cout << "Enter ID of the book to delete: ";
    cin >> id_to_delete;
    cin.ignore(10000, '\n');

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
        cout << "Book deleted." << endl;
    }
    else {
        cout << "Book with ID " << id_to_delete << " not found." << endl;
    }
}

// Автори 
void BookManager::addAuthor() {
    Author author;
    int id_val;
    string name_val;
    cout << "New Author ID: ";
    cin >> id_val;
    cin.ignore(10000, '\n');
    cout << "Author Name: ";
    getline(cin, name_val);
    author.setId(id_val);
    author.setName(name_val);
    authors.push_back(author);
    saveAuthors();
    cout << "Author added." << endl;
}

void BookManager::viewAuthors() const {
    if (authors.empty()) { cout << "No authors." << endl; return; }
    cout << "\n--- All Authors ---\n";
    for (size_t i = 0; i < authors.size(); ++i) {
        cout << authors[i].getId() << " " << authors[i].getName() << endl;
    }
}

void BookManager::modifyAuthor() {
    int id_val;
    string name_val;
    cout << "Enter Author ID to update: ";
    cin >> id_val;
    cin.ignore(10000, '\n');
    bool found = false;
    for (size_t i = 0; i < authors.size(); ++i) {
        if (authors[i].getId() == id_val) {
            cout << "Current Name: " << authors[i].getName() << ". New Name: ";
            getline(cin, name_val);
            if (!name_val.empty()) authors[i].setName(name_val);
            found = true;
            break;
        }
    }
    if (found) { saveAuthors(); cout << "Author updated." << endl; }
    else { cout << "Author not found." << endl; }
}

void BookManager::removeAuthor() {
    int id_val;
    cout << "Enter Author ID to delete: ";
    cin >> id_val;
    cin.ignore(10000, '\n');

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
        cout << "Author deleted." << endl;
    }
    else { cout << "Author not found." << endl; }
}

// Видавництва
void BookManager::addPublisher() {
    Publisher p; int id; string name;
    cout << "New Publisher ID: "; cin >> id;
    cin.ignore(10000, '\n');
    cout << "Publisher Name: "; getline(cin, name);
    p.setId(id); p.setName(name);
    publishers.push_back(p);
    savePublishers();
    cout << "Publisher added." << endl;
}
void BookManager::viewPublishers() const {
    if (publishers.empty()) { cout << "No publishers." << endl; return; }
    cout << "\n--- All Publishers ---\n";
    for (size_t i = 0; i < publishers.size(); ++i) {
        cout << publishers[i].getId() << " " << publishers[i].getName() << endl;
    }
}
void BookManager::modifyPublisher() {
    int id; string name;
    cout << "Enter Publisher ID to update: "; cin >> id;
    cin.ignore(10000, '\n');
    bool found = false;
    for (size_t i = 0; i < publishers.size(); ++i) {
        if (publishers[i].getId() == id) {
            cout << "Current Name: " << publishers[i].getName() << ". New Name: ";
            getline(cin, name);
            if (!name.empty()) publishers[i].setName(name);
            found = true;
            break;
        }
    }
    if (found) { savePublishers(); cout << "Publisher updated." << endl; }
    else { cout << "Publisher not found." << endl; }
}
void BookManager::removePublisher() {
    int id;
    cout << "Enter Publisher ID to delete: "; cin >> id;
    cin.ignore(10000, '\n');
    vector<Publisher> temp_pubs;
    bool removed = false;
    for (size_t i = 0; i < publishers.size(); ++i) {
        if (publishers[i].getId() != id) temp_pubs.push_back(publishers[i]);
        else removed = true;
    }
    if (removed) { publishers = temp_pubs; savePublishers(); cout << "Publisher deleted." << endl; }
    else { cout << "Publisher not found." << endl; }
}

//Жанри 
void BookManager::addGenre() {
    Genre g; int id; string name;
    cout << "New Genre ID: "; cin >> id;
    cin.ignore(10000, '\n');
    cout << "Genre Name: "; getline(cin, name);
    g.setId(id); g.setName(name);
    genres.push_back(g);
    saveGenres();
    cout << "Genre added." << endl;
}

void BookManager::viewGenres() const {
    if (genres.empty()) { cout << "No genres available." << endl; return; }
    cout << "\n--- All Genres ---\n";
    for (size_t i = 0; i < genres.size(); ++i) {
        cout << genres[i].getId() << " " << genres[i].getName() << endl;
    }
}
void BookManager::modifyGenre() {
    int id; string name;
    cout << "Enter Genre ID to update: "; cin >> id;
    cin.ignore(10000, '\n');
    bool found = false;
    for (size_t i = 0; i < genres.size(); ++i) {
        if (genres[i].getId() == id) {
            cout << "Current Name: " << genres[i].getName() << ". New Name: ";
            getline(cin, name);
            if (!name.empty()) genres[i].setName(name);
            found = true;
            break;
        }
    }
    if (found) { saveGenres(); cout << "Genre updated." << endl; }
    else { cout << "Genre not found." << endl; }
}
void BookManager::removeGenre() {
    int id;
    cout << "Enter Genre ID to delete: "; cin >> id;
    cin.ignore(10000, '\n');
    vector<Genre> temp_genres;
    bool removed = false;
    for (size_t i = 0; i < genres.size(); ++i) {
        if (genres[i].getId() != id) temp_genres.push_back(genres[i]);
        else removed = true;
    }
    if (removed) { genres = temp_genres; saveGenres(); cout << "Genre deleted." << endl; }
    else { cout << "Genre not found." << endl; }
}

//Експорт
void BookManager::exportToCSV(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Cannot open " << filename << " for CSV export." << endl;
        return;
    }
    file << "ID,Title,AuthorID,PublisherID,GenreIDs,Rating,Format\n";
    for (size_t i = 0; i < books.size(); ++i) { // Простий цикл for
        file << books[i].getId() << ",\"" << books[i].getTitle() << "\","
            << books[i].getAuthorId() << "," << books[i].getPublisherId() << ",\""
            << books[i].getGenreIdCSV() << "\"," << books[i].getRating() << ",\""
            << books[i].getFormat() << "\"\n";
    }
    file.close();
    cout << "Books exported to " << filename << "." << endl;
}

//Меню
int BookManager::displayMainMenu() const {
    int choice = 0; 
    cout << "\n--- Library Menu ---\n"
        << "1. Manage Books\n"
        << "2. Manage Authors\n"
        << "3. Manage Publishers\n"
        << "4. Manage Genres\n"
        << "5. Export Books to CSV\n"
        << "6. Exit\n"
        << "Enter choice: ";
    cin >> choice;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    cin.ignore(10000, '\n');
    return choice;
}

void BookManager::run() {
    bool running = true;
    while (running) {
        int choice = displayMainMenu();
        int subChoice = 0;

        switch (choice) {
        case 1:
            cout << "\n--- Book Menu ---\n"
                << "1. Add Book\n"
                << "2. View All Books\n"
                << "3. Find Book by Title\n"
                << "4. Update Book by ID\n"
                << "5. Delete Book by ID\n"
                << "0. Back to Main Menu\n"
                << "Enter choice: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); subChoice = -1; }
            else { cin.ignore(10000, '\n'); }
            switch (subChoice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: findBook(); break;
            case 4: modifyBook(); break;
            case 5: removeBook(); break;
            case 0: break;
            default: cout << "Invalid book menu choice." << endl;
            }
            break;
        case 2:
            cout << "\n--- Author Menu ---\n"
                << "1. Add Author\n"
                << "2. View All Authors\n"
                << "3. Update Author by ID\n"
                << "4. Delete Author by ID\n"
                << "0. Back to Main Menu\n"
                << "Enter choice: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); subChoice = -1; }
            else { cin.ignore(10000, '\n'); }
            switch (subChoice) {
            case 1: addAuthor(); break;
            case 2: viewAuthors(); break;
            case 3: modifyAuthor(); break;
            case 4: removeAuthor(); break;
            case 0: break;
            default: cout << "Invalid author menu choice." << endl;
            }
            break;
        case 3:
            cout << "\n--- Publisher Menu ---\n"
                << "1. Add Publisher\n"
                << "2. View All Publishers\n"
                << "3. Update Publisher by ID\n"
                << "4. Delete Publisher by ID\n"
                << "0. Back to Main Menu\n"
                << "Enter choice: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); subChoice = -1; }
            else { cin.ignore(10000, '\n'); }
            switch (subChoice) {
            case 1: addPublisher(); break;
            case 2: viewPublishers(); break;
            case 3: modifyPublisher(); break;
            case 4: removePublisher(); break;
            case 0: break;
            default: cout << "Invalid publisher menu choice." << endl;
            }
            break;
        case 4:
            cout << "\n--- Genre Menu ---\n"
                << "1. Add Genre\n"
                << "2. View All Genres\n"
                << "3. Update Genre by ID\n"
                << "4. Delete Genre by ID\n"
                << "0. Back to Main Menu\n"
                << "Enter choice: ";
            cin >> subChoice;
            if (cin.fail()) { cin.clear(); cin.ignore(10000, '\n'); subChoice = -1; }
            else { cin.ignore(10000, '\n'); }
            switch (subChoice) {
            case 1: addGenre(); break;
            case 2: viewGenres(); break;
            case 3: modifyGenre(); break;
            case 4: removeGenre(); break;
            case 0: break;
            default: cout << "Invalid genre menu choice." << endl;
            }
            break;
        case 5:
            exportToCSV("library_export.csv");
            break;
        case 6:
            running = false;
            break;
        case -1:
            cout << "Invalid choice in Main Menu. Please enter a number." << endl;
            break;
        default:
            cout << "Invalid choice in Main Menu. Please try again." << endl;
            break;
        }
    }
}