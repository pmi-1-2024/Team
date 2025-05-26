#include "BookManager.h"
#include <algorithm> 
#include <fstream> 
#include <sstream>  
#include <limits>   
#include <cctype>   
#include <iostream> 
#include <vector>   
#include <string>  

namespace {
    template<typename T>
    void loadDataFromFileInternal(const std::string& filename, std::vector<T>& items) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            return;
        }
        T item;
        items.clear();
        while (file >> item) {
            items.push_back(item);
        }
        file.close();
    }

    template<typename T>
    void saveDataToFileInternal(const std::string& filename, const std::vector<T>& items) {
        std::ofstream file(filename, std::ios::trunc);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open " << filename << " for saving." << std::endl;
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
    std::cout << "BookManager data saved." << std::endl;
}

void BookManager::loadAllData() {
    loadDataFromFileInternal(BOOKS_FILE_BM, books);
    loadDataFromFileInternal(AUTHORS_FILE_BM, authors);
    loadDataFromFileInternal(PUBLISHERS_FILE_BM, publishers);
    loadDataFromFileInternal(GENRES_FILE_BM, genres);
    std::cout << "Book catalog data loaded." << std::endl;
}

void BookManager::saveAllData() const {
    saveBooks();
    saveAuthors();
    savePublishers();
    saveGenres();
}

void BookManager::saveBooks() const { saveDataToFileInternal(BOOKS_FILE_BM, books); }
void BookManager::saveAuthors() const { saveDataToFileInternal(AUTHORS_FILE_BM, authors); }
void BookManager::savePublishers() const { saveDataToFileInternal(PUBLISHERS_FILE_BM, publishers); }
void BookManager::saveGenres() const { saveDataToFileInternal(GENRES_FILE_BM, genres); }

int BookManager::getIntInput(const std::string& prompt, bool allowZero) const {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.good() && (allowZero || input != 0)) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        std::cout << "Input error. Please enter an integer" << (allowZero ? "" : " (non-zero)") << "." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

double BookManager::getDoubleInput(const std::string& prompt) const {
    double input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        std::cout << "Input error. Please enter a number (e.g., 123.45)." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

std::string BookManager::getStringLineInput(const std::string& prompt) const {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

char BookManager::getCharInput(const std::string& prompt, const std::string& validChars) const {
    char input_char_val;
    std::string line_input;
    while (true) {
        std::cout << prompt << " (" << validChars[0] << "/" << validChars[1] << "): ";
        std::getline(std::cin, line_input);
        if (line_input.length() == 1) {
            input_char_val = std::tolower(line_input[0]);
            if (validChars.find(input_char_val) != std::string::npos) {
                return input_char_val;
            }
        }
        std::cout << "Invalid input. Please enter '" << validChars[0] << "' or '" << validChars[1] << "'." << std::endl;
    }
}

void BookManager::addBook() {
    Book b;
    int id_val, authorId_val, publisherId_val, year_val;
    std::string title_val, format_val, genre_ids_str_val;
    double rating_val, paper_price_val, electronic_price_val;
    char available_char;
    bool available_bool;
    std::vector<int> genre_ids_vec_val;

    std::cout << "--- Adding a New Book ---" << std::endl;

    while (true) {
        id_val = getIntInput("Book ID (non-zero): ");
        if (!findBookById(id_val)) break;
        std::cout << "Book with this ID already exists. Try another ID." << std::endl;
    }
    b.setId(id_val);

    b.setTitle(getStringLineInput("Title: "));

    viewAuthors();
    while (true) {
        authorId_val = getIntInput("Author ID (from the list provided, non-zero): ");
        if (authorExists(authorId_val)) break;
        std::cout << "Author with this ID does not exist. Please select an ID from the list or add a new author first." << std::endl;
    }
    b.setAuthorId(authorId_val);

    viewPublishers();
    while (true) {
        publisherId_val = getIntInput("Publisher ID (from the list provided, non-zero): ");
        if (publisherExists(publisherId_val)) break;
        std::cout << "Publisher with this ID does not exist. Please select an ID from the list or add a new publisher first." << std::endl;
    }
    b.setPublisherId(publisherId_val);

    viewGenres();
    genre_ids_str_val = getStringLineInput("Genre IDs (e.g., 1;2;3 or empty, separated by ';'): ");
    if (!genre_ids_str_val.empty()) {
        std::stringstream ss_genres(genre_ids_str_val);
        std::string item_str;
        int item_int;
        while (std::getline(ss_genres, item_str, ';')) {
            if (!item_str.empty()) {
                std::stringstream converter(item_str);
                if (converter >> item_int && genreExists(item_int)) {
                    genre_ids_vec_val.push_back(item_int);
                }
                else {
                    std::cout << "Warning: Genre with ID " << item_str << " not found or entered incorrectly. It will not be added." << std::endl;
                }
            }
        }
    }
    b.setGenreIds(genre_ids_vec_val);

    rating_val = getDoubleInput("Rating (0.0 - 10.0): ");
    while (rating_val < 0.0 || rating_val > 10.0) {
        std::cout << "Rating must be between 0.0 - 10.0." << std::endl;
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
    std::cout << "Book added." << std::endl;
}

void BookManager::viewBooks() const {
    if (books.empty()) {
        std::cout << "No books in the catalog." << std::endl;
        return;
    }
    std::cout << "\n--- All Books in Catalog ---" << std::endl;
    for (const auto& book : books) {
        book.displayInfo(*this);
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
    int id_to_update = getIntInput("Enter ID of the book to update: ");
    Book* book_to_modify = findBookById(id_to_update);

    if (book_to_modify == nullptr) {
        std::cout << "Book with ID " << id_to_update << " not found." << std::endl;
        return;
    }

    std::cout << "Found book. Current data for \"" << book_to_modify->getTitle() << "\":" << std::endl;
    book_to_modify->displayInfo(*this);
    std::cout << "Enter new data (press Enter to keep current value. ID cannot be changed):\n";

    std::string temp_str; int temp_int; double temp_double; char temp_char;

    temp_str = getStringLineInput("New title (current: " + book_to_modify->getTitle() + "): ");
    if (!temp_str.empty()) book_to_modify->setTitle(temp_str);

    viewAuthors();
    temp_str = getStringLineInput("New Author ID (current: " + std::to_string(book_to_modify->getAuthorId()) + "): ");
    if (!temp_str.empty()) {
        std::stringstream converter(temp_str);
        if (converter >> temp_int && authorExists(temp_int)) book_to_modify->setAuthorId(temp_int);
        else std::cout << "Author ID not changed (invalid input or ID does not exist)." << std::endl;
    }

    viewPublishers();
    temp_str = getStringLineInput("New Publisher ID (current: " + std::to_string(book_to_modify->getPublisherId()) + "): ");
    if (!temp_str.empty()) {
        std::stringstream converter(temp_str);
        if (converter >> temp_int && publisherExists(temp_int)) book_to_modify->setPublisherId(temp_int);
        else std::cout << "Publisher ID not changed (invalid input or ID does not exist)." << std::endl;
    }

    viewGenres();
    temp_str = getStringLineInput("New Genre IDs (current: " + book_to_modify->getGenreIdCSV() + ", separated by ';'): ");
    if (!temp_str.empty()) {
        std::vector<int> new_genre_ids; std::stringstream ss(temp_str); std::string item_str; int item_int_val;
        while (std::getline(ss, item_str, ';')) {
            if (!item_str.empty()) {
                std::stringstream converter(item_str);
                if (converter >> item_int_val && genreExists(item_int_val)) new_genre_ids.push_back(item_int_val);
                else std::cout << "Warning: Genre ID " << item_str << " not found or invalid, will not be added." << std::endl;
            }
        }
        book_to_modify->setGenreIds(new_genre_ids);
    }

    temp_str = getStringLineInput("New rating (current: " + std::to_string(book_to_modify->getRating()) + "): ");
    if (!temp_str.empty()) {
        std::stringstream converter(temp_str);
        if (converter >> temp_double && temp_double >= 0.0 && temp_double <= 10.0) book_to_modify->setRating(temp_double);
        else std::cout << "Rating not changed (invalid input)." << std::endl;
    }

    temp_str = getStringLineInput("New format (current: " + book_to_modify->getFormat() + "): ");
    if (!temp_str.empty()) book_to_modify->setFormat(temp_str);

    temp_str = getStringLineInput("New year of publication (current: " + std::to_string(book_to_modify->getYear()) + "): ");
    if (!temp_str.empty()) { std::stringstream c(temp_str); if (c >> temp_int) book_to_modify->setYear(temp_int); }

    temp_str = getStringLineInput("New paper version price (current: " + std::to_string(book_to_modify->getPaperPrice()) + "): ");
    if (!temp_str.empty()) { std::stringstream c(temp_str); if (c >> temp_double) book_to_modify->setPaperPrice(temp_double < 0 ? 0 : temp_double); }

    temp_str = getStringLineInput("New electronic version price (current: " + std::to_string(book_to_modify->getElectronicPrice()) + "): ");
    if (!temp_str.empty()) { std::stringstream c(temp_str); if (c >> temp_double) book_to_modify->setElectronicPrice(temp_double < 0 ? 0 : temp_double); }

    temp_str = getStringLineInput("Available (y/n) (current: " + std::string(book_to_modify->isAvailable() ? "y" : "n") + "): ");
    if (!temp_str.empty()) {
        temp_char = std::tolower(temp_str[0]);
        if (temp_char == 'y' || temp_char == 'n') book_to_modify->setAvailable(temp_char == 'y');
        else std::cout << "Availability status not changed (invalid input)." << std::endl;
    }
    std::cout << "Book updated." << std::endl;
}

void BookManager::removeBook() {
    int id_to_delete = getIntInput("Enter ID of the book to delete: ");
    auto it = std::remove_if(books.begin(), books.end(),
        [id_to_delete](const Book& b) { return b.getId() == id_to_delete; });
    if (it != books.end()) {
        books.erase(it, books.end());
        std::cout << "Book deleted." << std::endl;
    }
    else {
        std::cout << "Book with ID " << id_to_delete << " not found." << std::endl;
    }
}

void BookManager::setBookAvailability(int bookId, bool available) {
    Book* book = findBookById(bookId);
    if (book) {
        book->setAvailable(available);
    }
    else {
        std::cerr << "Error (BookManager::setBookAvailability): Book with ID " << bookId << " not found." << std::endl;
    }
}

void BookManager::addAuthor() {
    int id_val; std::string name_val;
    std::cout << "--- Adding Author ---" << std::endl;
    while (true) {
        id_val = getIntInput("Author ID (non-zero): ");
        if (!authorExists(id_val)) break;
        std::cout << "Author with ID " << id_val << " already exists.\n";
    }
    name_val = getStringLineInput("Author Name: ");
    authors.emplace_back(id_val, name_val);
    std::cout << "Author added.\n";
}
void BookManager::viewAuthors() const {
    if (authors.empty()) { std::cout << "No authors found.\n"; return; }
    std::cout << "\n--- Authors ---\n";
    for (const auto& a : authors) std::cout << "ID: " << a.getId() << ", Name: " << a.getName() << std::endl;
}
void BookManager::modifyAuthor() {
    int id_val = getIntInput("Author ID to modify: ");
    for (auto& a : authors) {
        if (a.getId() == id_val) {
            std::string n_name = getStringLineInput("New name (current: " + a.getName() + "): ");
            if (!n_name.empty()) a.setName(n_name);
            std::cout << "Author updated.\n"; return;
        }
    }
    std::cout << "Author not found.\n";
}
void BookManager::removeAuthor() {
    int id_val = getIntInput("Author ID to delete: ");
    auto it = std::remove_if(authors.begin(), authors.end(), [id_val](const Author& a) { return a.getId() == id_val; });
    if (it != authors.end()) { authors.erase(it, authors.end()); std::cout << "Author deleted.\n"; }
    else { std::cout << "Author not found.\n"; }
}

void BookManager::addPublisher() {
    int id; std::string name;
    std::cout << "--- Adding Publisher ---\n";
    while (true) {
        id = getIntInput("Publisher ID (non-zero): ");
        if (!publisherExists(id))break;
        std::cout << "Publisher with ID " << id << " already exists.\n";
    }
    name = getStringLineInput("Name: ");
    publishers.emplace_back(id, name);
    std::cout << "Publisher added.\n";
}
void BookManager::viewPublishers() const {
    if (publishers.empty()) { std::cout << "No publishers found.\n"; return; }
    std::cout << "\n--- Publishers ---\n";
    for (const auto& p : publishers)std::cout << "ID: " << p.getId() << ", Name: " << p.getName() << std::endl;
}
void BookManager::modifyPublisher() {
    int id = getIntInput("Publisher ID to modify: ");
    for (auto& p : publishers) {
        if (p.getId() == id) {
            std::string n = getStringLineInput("New Name (current: " + p.getName() + "): ");
            if (!n.empty())p.setName(n);
            std::cout << "Publisher updated.\n"; return;
        }
    }
    std::cout << "Publisher not found.\n";
}
void BookManager::removePublisher() {
    int id = getIntInput("Publisher ID to delete: ");
    auto it = std::remove_if(publishers.begin(), publishers.end(), [id](const Publisher& p) {return p.getId() == id; });
    if (it != publishers.end()) { publishers.erase(it, publishers.end()); std::cout << "Publisher deleted.\n"; }
    else { std::cout << "Publisher not found.\n"; }
}

void BookManager::addGenre() {
    int id; std::string name;
    std::cout << "--- Adding Genre ---\n";
    while (true) {
        id = getIntInput("Genre ID (non-zero): ");
        if (!genreExists(id))break;
        std::cout << "Genre with ID " << id << " already exists.\n";
    }
    name = getStringLineInput("Name: ");
    genres.emplace_back(id, name);
    std::cout << "Genre added.\n";
}
void BookManager::viewGenres() const {
    if (genres.empty()) { std::cout << "No genres found.\n"; return; }
    std::cout << "\n--- Genres ---\n";
    for (const auto& g : genres)std::cout << "ID: " << g.getId() << ", Name: " << g.getName() << std::endl;
}
void BookManager::modifyGenre() {
    int id = getIntInput("Genre ID to modify: ");
    for (auto& g : genres) {
        if (g.getId() == id) {
            std::string n = getStringLineInput("New Name (current: " + g.getName() + "): ");
            if (!n.empty())g.setName(n);
            std::cout << "Genre updated.\n"; return;
        }
    }
    std::cout << "Genre not found.\n";
}
void BookManager::removeGenre() {
    int id = getIntInput("Genre ID to delete: ");
    auto it = std::remove_if(genres.begin(), genres.end(), [id](const Genre& g) {return g.getId() == id; });
    if (it != genres.end()) { genres.erase(it, genres.end()); std::cout << "Genre deleted.\n"; }
    else { std::cout << "Genre not found.\n"; }
}

std::string BookManager::getAuthorNameById(int authorId) const {
    for (const auto& a : authors) if (a.getId() == authorId) return a.getName(); return "N/A";
}
std::string BookManager::getPublisherNameById(int publisherId) const {
    for (const auto& p : publishers) if (p.getId() == publisherId) return p.getName(); return "N/A";
}
std::string BookManager::getGenreNameById(int genreId) const {
    for (const auto& g : genres) if (g.getId() == genreId) return g.getName(); return "N/A";
}
bool BookManager::authorExists(int authorId) const { for (const auto& a : authors) if (a.getId() == authorId) return true; return false; }
bool BookManager::publisherExists(int publisherId) const { for (const auto& p : publishers) if (p.getId() == publisherId) return true; return false; }
bool BookManager::genreExists(int genreId) const { for (const auto& g : genres) if (g.getId() == genreId) return true; return false; }

void BookManager::exportToCSV(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Cannot open " << filename << " for CSV export." << std::endl;
        return;
    }
    file << "ID,Title,AuthorID,PublisherID,GenreIDs_CSV,Rating,Format,Year,PaperPrice,ElectronicPrice,Available\n";
    for (const auto& book : books) {
        file << book.getId() << ",\"" << book.getTitle() << "\","
            << book.getAuthorId() << "," << book.getPublisherId() << ",\""
            << book.getGenreIdCSV() << "\"," << book.getRating() << ",\""
            << book.getFormat() << "\"," << book.getYear() << ","
            << book.getPaperPrice() << "," << book.getElectronicPrice() << ","
            << (book.isAvailable() ? "true" : "false") << "\n";
    }
    file.close();
    std::cout << "Books exported to " << filename << "." << std::endl;
}

int BookManager::displayMainMenu() const {
    std::cout << "\n--- Book Catalog Management Menu ---"
        << "\n1. Manage Books"
        << "\n2. Manage Authors"
        << "\n3. Manage Publishers"
        << "\n4. Manage Genres"
        << "\n5. Export Books to CSV"
        << "\n0. Return to Main Program Menu"
        << "\nYour choice: ";
    return getIntInput("", true);
}

void BookManager::run() {
    bool running = true;
    while (running) {
        int choice = displayMainMenu();
        int subChoice;

        switch (choice) {
        case 1:
            std::cout << "\n--- Book Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
            subChoice = getIntInput("", true);
            switch (subChoice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: modifyBook(); break;
            case 4: removeBook(); break;
            case 0: break;
            default: std::cout << "Invalid choice.\n";
            }
            break;
        case 2:
            std::cout << "\n--- Author Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
            subChoice = getIntInput("", true);
            switch (subChoice) {
            case 1: addAuthor(); break;
            case 2: viewAuthors(); break;
            case 3: modifyAuthor(); break;
            case 4: removeAuthor(); break;
            case 0: break;
            default: std::cout << "Invalid choice.\n";
            }
            break;
        case 3:
            std::cout << "\n--- Publisher Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
            subChoice = getIntInput("", true);
            switch (subChoice) {
            case 1: addPublisher(); break;
            case 2: viewPublishers(); break;
            case 3: modifyPublisher(); break;
            case 4: removePublisher(); break;
            case 0: break;
            default: std::cout << "Invalid choice.\n";
            }
            break;
        case 4:
            std::cout << "\n--- Genre Menu ---\n1. Add\n2. View All\n3. Update\n4. Delete\n0. Back\nYour choice: ";
            subChoice = getIntInput("", true);
            switch (subChoice) {
            case 1: addGenre(); break;
            case 2: viewGenres(); break;
            case 3: modifyGenre(); break;
            case 4: removeGenre(); break;
            case 0: break;
            default: std::cout << "Invalid choice.\n";
            }
            break;
        case 5: exportToCSV("library_catalog_export.csv"); break;
        case 0: running = false; std::cout << "Returning to previous menu..." << std::endl; break;
        default: std::cout << "Invalid choice. Please try again." << std::endl; break;
        }
        if (running && choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::string dummy; std::getline(std::cin, dummy);
        }
    }
}

const std::vector<Book>& BookManager::getAllBooks() const {
    return books;
}