#include "BookManager.h"
#include <algorithm> 
#include <fstream> 
#include <sstream>  
#include <limits>   
#include <cctype>   
#include <iostream> 
#include <vector>   
#include <string>  
#include <stdexcept> 

using namespace std;

namespace {
    template<typename T>
    void loadDataFromFileInternal(const string& filename, vector<T>& items) {
        ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        T item;
        items.clear();
        try {
            while (file >> item) {
                items.push_back(item);
            }
        }
        catch (const ios_base::failure& e) {
            cerr << "Error during reading file " << filename << ": " << e.what() << endl;
        }
        file.close();
    }

    template<typename T>
    void saveDataToFileInternal(const string& filename, const vector<T>& items) {
        ofstream file(filename, ios::trunc);
        if (!file.is_open()) {
            cerr << "Error: Cannot open " << filename << " for saving." << endl;
            return;
        }
        try {
            for (const auto& item : items) {
                file << item;
            }
        }
        catch (const ios_base::failure& e) {
            cerr << "Error during writing to file " << filename << ": " << e.what() << endl;
        }
        file.close();
    }
}

BookManager::BookManager() {
    try {
        loadAllData();
    }
    catch (const std::exception& e) {
        cerr << "Error during BookManager construction (loadAllData): " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error during BookManager construction (loadAllData)." << endl;
    }
}

BookManager::~BookManager() {
    try {
        saveAllData();
        cout << "BookManager data saved." << endl;
    }
    catch (const std::exception& e) {
        cerr << "Error during BookManager destruction (saveAllData): " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error during BookManager destruction (saveAllData)." << endl;
    }
}

void BookManager::loadAllData() {
    try {
        loadDataFromFileInternal(BOOKS_FILE_BM, books);
        loadDataFromFileInternal(AUTHORS_FILE_BM, authors);
        loadDataFromFileInternal(PUBLISHERS_FILE_BM, publishers);
        loadDataFromFileInternal(GENRES_FILE_BM, genres);
        cout << "Book catalog data loaded." << endl;
    }
    catch (const std::exception& e) {
        cerr << "Error loading all data: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error while loading all data." << endl;
    }
}

void BookManager::saveAllData() const {
    try {
        saveBooks();
        saveAuthors();
        savePublishers();
        saveGenres();
    }
    catch (const std::exception& e) {
        cerr << "Error saving all data: " << e.what() << endl;
    }
    catch (...) {
        cerr << "Unknown error while saving all data." << endl;
    }
}

void BookManager::saveBooks() const { saveDataToFileInternal(BOOKS_FILE_BM, books); }
void BookManager::saveAuthors() const { saveDataToFileInternal(AUTHORS_FILE_BM, authors); }
void BookManager::savePublishers() const { saveDataToFileInternal(PUBLISHERS_FILE_BM, publishers); }
void BookManager::saveGenres() const { saveDataToFileInternal(GENRES_FILE_BM, genres); }

int BookManager::getIntInput(const string& prompt, bool allowZero) const {
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

double BookManager::getDoubleInput(const string& prompt) const {
    double input;
    while (true) {
        cout << prompt;
        cin >> input;
        if (cin.good()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return input;
        }
        cout << "Input error. Please enter a number (e.g., 123.45)." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string BookManager::getStringLineInput(const string& prompt) const {
    string input;
    cout << prompt;
    getline(cin, input);
    if (cin.fail()) {
        cin.clear();
        cerr << "Warning: getStringLineInput failed." << endl;
    }
    return input;
}

char BookManager::getCharInput(const string& prompt, const string& validChars) const {
    char input_char_val;
    string line_input;
    while (true) {
        cout << prompt << " (" << validChars[0] << "/" << validChars[1] << "): ";
        getline(cin, line_input);
        if (cin.fail()) {
            cin.clear();
            cerr << "Warning: getCharInput failed during getline." << endl;
            continue;
        }
        if (line_input.length() == 1) {
            input_char_val = tolower(line_input[0]);
            if (validChars.find(input_char_val) != string::npos) {
                return input_char_val;
            }
        }
        cout << "Invalid input. Please enter '" << validChars[0] << "' or '" << validChars[1] << "'." << endl;
    }
}

void BookManager::addBook() {
    try {
        Book b;
        int id_val, authorId_val, publisherId_val, year_val;
        string title_val, format_val, genre_ids_str_val;
        double rating_val, paper_price_val, electronic_price_val;
        char available_char;
        bool available_bool;
        vector<int> genre_ids_vec_val;

        cout << "--- Adding a New Book ---" << endl;

        while (true) {
            id_val = getIntInput("Book ID (non-zero): ");
            if (!findBookById(id_val)) break;
            cout << "Book with this ID already exists. Try another ID." << endl;
        }
        b.setId(id_val);
        b.setTitle(getStringLineInput("Title: "));
        viewAuthors();
        while (true) {
            authorId_val = getIntInput("Author ID (from the list provided, non-zero): ");
            if (authorExists(authorId_val)) break;
            cout << "Author with this ID does not exist. Please select an ID from the list or add a new author first." << endl;
        }
        b.setAuthorId(authorId_val);
        viewPublishers();
        while (true) {
            publisherId_val = getIntInput("Publisher ID (from the list provided, non-zero): ");
            if (publisherExists(publisherId_val)) break;
            cout << "Publisher with this ID does not exist. Please select an ID from the list or add a new publisher first." << endl;
        }
        b.setPublisherId(publisherId_val);
        viewGenres();
        genre_ids_str_val = getStringLineInput("Genre IDs (e.g., 1;2;3 or empty, separated by ';'): ");
        if (!genre_ids_str_val.empty()) {
            stringstream ss_genres(genre_ids_str_val);
            string item_str;
            int item_int;
            while (getline(ss_genres, item_str, ';')) {
                if (!item_str.empty()) {
                    stringstream converter(item_str);
                    if (converter >> item_int && genreExists(item_int)) {
                        genre_ids_vec_val.push_back(item_int);
                    }
                    else {
                        cout << "Warning: Genre with ID " << item_str << " not found or entered incorrectly. It will not be added." << endl;
                    }
                }
            }
        }
        b.setGenreIds(genre_ids_vec_val);
        rating_val = getDoubleInput("Rating (0.0 - 10.0): ");
        while (rating_val < 0.0 || rating_val > 10.0) {
            cout << "Rating must be between 0.0 - 10.0." << endl;
            rating_val = getDoubleInput("Rating (0.0 - 10.0): ");
        }
        b.setRating(rating_val);
        b.setFormat(getStringLineInput("Format (Paper/Electronic/Audio): "));
        year_val = getIntInput("Year of publication: ", true);
        b.setYear(year_val);
        paper_price_val = getDoubleInput("Paper version price (0 if none): ");
        b.setPaperPrice(paper_price_val < 0 ? 0 : paper_price_val);
        electronic_price_val = getDoubleInput("Electronic version price (0 if none): ");
        b.setElectronicPrice(electronic_price_val < 0 ? 0 : electronic_price_val);
        available_char = getCharInput("Available?", "yn");
        available_bool = (available_char == 'y');
        b.setAvailable(available_bool);
        books.push_back(b);
        cout << "Book added." << endl;
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while adding a book: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while adding a book." << endl;
    }
}

void BookManager::viewBooks() const {
    try {
        if (books.empty()) {
            cout << "No books in the catalog." << endl;
            return;
        }
        cout << "\n--- All Books in Catalog ---" << endl;
        for (const auto& book : books) {
            book.displayInfo(*this);
        }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while viewing books: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while viewing books." << endl;
    }
}

Book* BookManager::findBookById(int bookId) {
    for (auto& book : books) {
        if (book.getId() == bookId) {
            return &book;
        }
    }
    return nullptr;
}
const Book* BookManager::findBookById(int bookId) const {
    for (const auto& book : books) {
        if (book.getId() == bookId) {
            return &book;
        }
    }
    return nullptr;
}

void BookManager::modifyBook() {
    try {
        int id_to_update = getIntInput("Enter ID of the book to update: ");
        Book* book_to_modify = findBookById(id_to_update);

        if (book_to_modify == nullptr) {
            cout << "Book with ID " << id_to_update << " not found." << endl;
            return;
        }

        cout << "Found book. Current data for \"" << book_to_modify->getTitle() << "\":" << endl;
        book_to_modify->displayInfo(*this);
        cout << "Enter new data (press Enter to keep current value. ID cannot be changed):\n";

        string temp_str; int temp_int; double temp_double; char temp_char;

        temp_str = getStringLineInput("New title (current: " + book_to_modify->getTitle() + "): ");
        if (!temp_str.empty()) book_to_modify->setTitle(temp_str);

        viewAuthors();
        temp_str = getStringLineInput("New Author ID (current: " + to_string(book_to_modify->getAuthorId()) + "): ");
        if (!temp_str.empty()) {
            stringstream converter(temp_str);
            if (converter >> temp_int && authorExists(temp_int)) book_to_modify->setAuthorId(temp_int);
            else cout << "Author ID not changed (invalid input or ID does not exist)." << endl;
        }

        viewPublishers();
        temp_str = getStringLineInput("New Publisher ID (current: " + to_string(book_to_modify->getPublisherId()) + "): ");
        if (!temp_str.empty()) {
            stringstream converter(temp_str);
            if (converter >> temp_int && publisherExists(temp_int)) book_to_modify->setPublisherId(temp_int);
            else cout << "Publisher ID not changed (invalid input or ID does not exist)." << endl;
        }

        viewGenres();
        string current_genre_ids_display_str;
        const vector<int>& current_ids = book_to_modify->getGenreIds();
        if (!current_ids.empty()) {
            stringstream ss_display;
            for (size_t i = 0; i < current_ids.size(); ++i) {
                ss_display << current_ids[i];
                if (i < current_ids.size() - 1) {
                    ss_display << ";";
                }
            }
            current_genre_ids_display_str = ss_display.str();
        }
        else {
            current_genre_ids_display_str = "none";
        }
        temp_str = getStringLineInput("New Genre IDs (current: " + current_genre_ids_display_str + ", separated by ';'): ");

        if (!temp_str.empty()) {
            vector<int> new_genre_ids; stringstream ss(temp_str); string item_str; int item_int_val;
            while (getline(ss, item_str, ';')) {
                if (!item_str.empty()) {
                    stringstream converter(item_str);
                    if (converter >> item_int_val && genreExists(item_int_val)) new_genre_ids.push_back(item_int_val);
                    else cout << "Warning: Genre ID " << item_str << " not found or invalid, will not be added." << endl;
                }
            }
            book_to_modify->setGenreIds(new_genre_ids);
        }

        temp_str = getStringLineInput("New rating (current: " + to_string(book_to_modify->getRating()) + "): ");
        if (!temp_str.empty()) {
            stringstream converter(temp_str);
            if (converter >> temp_double && temp_double >= 0.0 && temp_double <= 10.0) book_to_modify->setRating(temp_double);
            else cout << "Rating not changed (invalid input)." << endl;
        }

        temp_str = getStringLineInput("New format (current: " + book_to_modify->getFormat() + "): ");
        if (!temp_str.empty()) book_to_modify->setFormat(temp_str);

        temp_str = getStringLineInput("New year of publication (current: " + to_string(book_to_modify->getYear()) + "): ");
        if (!temp_str.empty()) { stringstream c(temp_str); if (c >> temp_int) book_to_modify->setYear(temp_int); }

        temp_str = getStringLineInput("New paper version price (current: " + to_string(book_to_modify->getPaperPrice()) + "): ");
        if (!temp_str.empty()) { stringstream c(temp_str); if (c >> temp_double) book_to_modify->setPaperPrice(temp_double < 0 ? 0 : temp_double); }

        temp_str = getStringLineInput("New electronic version price (current: " + to_string(book_to_modify->getElectronicPrice()) + "): ");
        if (!temp_str.empty()) { stringstream c(temp_str); if (c >> temp_double) book_to_modify->setElectronicPrice(temp_double < 0 ? 0 : temp_double); }

        temp_str = getStringLineInput("Available (y/n) (current: " + string(book_to_modify->isAvailable() ? "y" : "n") + "): ");
        if (!temp_str.empty()) {
            temp_char = tolower(temp_str[0]);
            if (temp_char == 'y' || temp_char == 'n') book_to_modify->setAvailable(temp_char == 'y');
            else cout << "Availability status not changed (invalid input)." << endl;
        }
        cout << "Book updated." << endl;
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while modifying a book: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while modifying a book." << endl;
    }
}

void BookManager::removeBook() {
    try {
        int id_to_delete = getIntInput("Enter ID of the book to delete: ");
        auto it = remove_if(books.begin(), books.end(),
            [id_to_delete](const Book& b) { return b.getId() == id_to_delete; });
        if (it != books.end()) {
            books.erase(it, books.end());
            cout << "Book deleted." << endl;
        }
        else {
            cout << "Book with ID " << id_to_delete << " not found." << endl;
        }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while removing a book: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while removing a book." << endl;
    }
}

void BookManager::setBookAvailability(int bookId, bool available) {
    try {
        Book* book = findBookById(bookId);
        if (book) {
            book->setAvailable(available);
        }
        else {
            cerr << "Error (BookManager::setBookAvailability): Book with ID " << bookId << " not found." << endl;
        }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while setting book availability: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while setting book availability." << endl;
    }
}

void BookManager::addAuthor() {
    try {
        int id_val; string name_val;
        cout << "--- Adding Author ---" << endl;
        while (true) {
            id_val = getIntInput("Author ID (non-zero): ");
            if (!authorExists(id_val)) break;
            cout << "Author with ID " << id_val << " already exists.\n";
        }
        name_val = getStringLineInput("Author Name: ");
        authors.emplace_back(id_val, name_val);
        cout << "Author added.\n";
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while adding an author: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while adding an author." << endl;
    }
}
void BookManager::viewAuthors() const {
    try {
        if (authors.empty()) { cout << "No authors found.\n"; return; }
        cout << "\n--- Authors ---\n";
        for (const auto& a : authors) cout << "ID: " << a.getId() << ", Name: " << a.getName() << endl;
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while viewing authors: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while viewing authors." << endl;
    }
}
void BookManager::modifyAuthor() {
    try {
        int id_val = getIntInput("Author ID to modify: ");
        bool found = false;
        for (auto& a : authors) {
            if (a.getId() == id_val) {
                string n_name = getStringLineInput("New name (current: " + a.getName() + "): ");
                if (!n_name.empty()) a.setName(n_name);
                cout << "Author updated.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Author not found.\n";
        }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while modifying an author: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while modifying an author." << endl;
    }
}
void BookManager::removeAuthor() {
    try {
        int id_val = getIntInput("Author ID to delete: ");
        auto it = remove_if(authors.begin(), authors.end(), [id_val](const Author& a) { return a.getId() == id_val; });
        if (it != authors.end()) { authors.erase(it, authors.end()); cout << "Author deleted.\n"; }
        else { cout << "Author not found.\n"; }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while removing an author: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while removing an author." << endl;
    }
}

void BookManager::addPublisher() {
    try {
        int id; string name;
        cout << "--- Adding Publisher ---\n";
        while (true) {
            id = getIntInput("Publisher ID (non-zero): ");
            if (!publisherExists(id))break;
            cout << "Publisher with ID " << id << " already exists.\n";
        }
        name = getStringLineInput("Name: ");
        publishers.emplace_back(id, name);
        cout << "Publisher added.\n";
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while adding a publisher: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while adding a publisher." << endl;
    }
}
void BookManager::viewPublishers() const {
    try {
        if (publishers.empty()) { cout << "No publishers found.\n"; return; }
        cout << "\n--- Publishers ---\n";
        for (const auto& p : publishers)cout << "ID: " << p.getId() << ", Name: " << p.getName() << endl;
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while viewing publishers: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while viewing publishers." << endl;
    }
}
void BookManager::modifyPublisher() {
    try {
        int id = getIntInput("Publisher ID to modify: ");
        bool found = false;
        for (auto& p : publishers) {
            if (p.getId() == id) {
                string n = getStringLineInput("New Name (current: " + p.getName() + "): ");
                if (!n.empty())p.setName(n);
                cout << "Publisher updated.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Publisher not found.\n";
        }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while modifying a publisher: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while modifying a publisher." << endl;
    }
}
void BookManager::removePublisher() {
    try {
        int id = getIntInput("Publisher ID to delete: ");
        auto it = remove_if(publishers.begin(), publishers.end(), [id](const Publisher& p) {return p.getId() == id; });
        if (it != publishers.end()) { publishers.erase(it, publishers.end()); cout << "Publisher deleted.\n"; }
        else { cout << "Publisher not found.\n"; }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while removing a publisher: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while removing a publisher." << endl;
    }
}

void BookManager::addGenre() {
    try {
        int id; string name;
        cout << "--- Adding Genre ---\n";
        while (true) {
            id = getIntInput("Genre ID (non-zero): ");
            if (!genreExists(id))break;
            cout << "Genre with ID " << id << " already exists.\n";
        }
        name = getStringLineInput("Name: ");
        genres.emplace_back(id, name);
        cout << "Genre added.\n";
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while adding a genre: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while adding a genre." << endl;
    }
}
void BookManager::viewGenres() const {
    try {
        if (genres.empty()) { cout << "No genres found.\n"; return; }
        cout << "\n--- Genres ---\n";
        for (const auto& g : genres)cout << "ID: " << g.getId() << ", Name: " << g.getName() << endl;
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while viewing genres: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while viewing genres." << endl;
    }
}
void BookManager::modifyGenre() {
    try {
        int id = getIntInput("Genre ID to modify: ");
        bool found = false;
        for (auto& g : genres) {
            if (g.getId() == id) {
                string n = getStringLineInput("New Name (current: " + g.getName() + "): ");
                if (!n.empty())g.setName(n);
                cout << "Genre updated.\n";
                found = true;
                break;
            }
        }
        if (!found) {
            cout << "Genre not found.\n";
        }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while modifying a genre: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while modifying a genre." << endl;
    }
}
void BookManager::removeGenre() {
    try {
        int id = getIntInput("Genre ID to delete: ");
        auto it = remove_if(genres.begin(), genres.end(), [id](const Genre& g) {return g.getId() == id; });
        if (it != genres.end()) { genres.erase(it, genres.end()); cout << "Genre deleted.\n"; }
        else { cout << "Genre not found.\n"; }
    }
    catch (const std::exception& e) {
        cerr << "An error occurred while removing a genre: " << e.what() << endl;
    }
    catch (...) {
        cerr << "An unknown error occurred while removing a genre." << endl;
    }
}

string BookManager::getAuthorNameById(int authorId) const {
    for (const auto& a : authors) if (a.getId() == authorId) return a.getName(); return "N/A";
}
string BookManager::getPublisherNameById(int publisherId) const {
    for (const auto& p : publishers) if (p.getId() == publisherId) return p.getName(); return "N/A";
}
string BookManager::getGenreNameById(int genreId) const {
    for (const auto& g : genres) if (g.getId() == genreId) return g.getName(); return "N/A";
}
bool BookManager::authorExists(int authorId) const { for (const auto& a : authors) if (a.getId() == authorId) return true; return false; }
bool BookManager::publisherExists(int publisherId) const { for (const auto& p : publishers) if (p.getId() == publisherId) return true; return false; }
bool BookManager::genreExists(int genreId) const { for (const auto& g : genres) if (g.getId() == genreId) return true; return false; }


int BookManager::displayMainMenu() const {
    cout << "\n--- Book Catalog Management Menu ---"
        << "\n1. Manage Books"
        << "\n2. Manage Authors"
        << "\n3. Manage Publishers"
        << "\n4. Manage Genres"
        << "\n0. Return to Main Program Menu"
        << "\nYour choice: ";
    return getIntInput("", true);
}

void BookManager::run() {
    bool running = true;
    while (running) {
        try {
            int choice = displayMainMenu();
            int subChoice;

            switch (choice) {
            case 1:
                cout << "\n--- Book Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
                subChoice = getIntInput("", true);
                switch (subChoice) {
                case 1: addBook(); break;
                case 2: viewBooks(); break;
                case 3: modifyBook(); break;
                case 4: removeBook(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
                }
                break;
            case 2:
                cout << "\n--- Author Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
                subChoice = getIntInput("", true);
                switch (subChoice) {
                case 1: addAuthor(); break;
                case 2: viewAuthors(); break;
                case 3: modifyAuthor(); break;
                case 4: removeAuthor(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
                }
                break;
            case 3:
                cout << "\n--- Publisher Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
                subChoice = getIntInput("", true);
                switch (subChoice) {
                case 1: addPublisher(); break;
                case 2: viewPublishers(); break;
                case 3: modifyPublisher(); break;
                case 4: removePublisher(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
                }
                break;
            case 4:
                cout << "\n--- Genre Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
                subChoice = getIntInput("", true);
                switch (subChoice) {
                case 1: addGenre(); break;
                case 2: viewGenres(); break;
                case 3: modifyGenre(); break;
                case 4: removeGenre(); break;
                case 0: break;
                default: cout << "Invalid choice.\n";
                }
                break;
            case 0:
                running = false;
                cout << "Returning to previous menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }

            if (running && choice != 0) {
                cout << "\nPress Enter to continue...";
                string dummy;
                getline(cin, dummy);
            }

        }
        catch (const std::exception& e) {
            cerr << "An error occurred in BookManager menu: " << e.what() << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
        catch (...) {
            cerr << "An unknown error occurred in BookManager menu." << endl;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }
}

const vector<Book>& BookManager::getAllBooks() const {
    return books;
}