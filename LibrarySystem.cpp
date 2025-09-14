#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "LibrarySystem.h"

using namespace std;

// Constructor - Load data on startup
LibrarySystem::LibrarySystem() {
    loadFromDatabase();
}

// Destructor - Save data on exit
LibrarySystem::~LibrarySystem() {
    saveToDatabase();
}

// Load data from file
void LibrarySystem::loadFromDatabase() {
    ifstream file(databaseFile);
    if (!file.is_open()) {
        cout << "No existing database found. Starting with empty library." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;
        
        while (getline(ss, token, '|')) {
            tokens.push_back(token);
        }
        
        if (tokens.size() == 4) {
            int id = stoi(tokens[0]);
            string title = tokens[1];
            string author = tokens[2];
            bool isAvailable = (tokens[3] == "1");
            
            books.insert(Book(id, title, author));
            bookTitleToId[title] = id;
            
            if (!isAvailable) {
                borrowedBooks[id] = true;
                // Update book status in the set
                auto it = books.find(Book(id, "", ""));
                if (it != books.end()) {
                    const_cast<Book&>(*it).isAvailable = false;
                }
            }
        }
    }
    file.close();
    cout << "Database loaded successfully!" << endl;
}

// Save data to file
void LibrarySystem::saveToDatabase() {
    ofstream file(databaseFile);
    if (!file.is_open()) {
        cout << "Error: Could not save database!" << endl;
        return;
    }

    for (const auto& book : books) {
        file << book.id << "|" 
             << book.title << "|" 
             << book.author << "|"
             << (book.isAvailable ? "1" : "0") << endl;
    }
    
    file.close();
    cout << "Database saved successfully!" << endl;
}

// Clear database (for testing purposes)
void LibrarySystem::clearDatabase() {
    ofstream file(databaseFile, ios::trunc);
    file.close();
    books.clear();
    bookTitleToId.clear();
    borrowedBooks.clear();
    cout << "Database cleared!" << endl;
}

// Add a book with validation for unique ID and title
void LibrarySystem::addBook(int id, string title, string author) {
    if (books.find(Book(id, "", "")) != books.end()) {
        cout << "Error: A book with ID " << id << " already exists." << endl;
        return;
    }

    if (bookTitleToId.find(title) != bookTitleToId.end()) {
        cout << "Error: A book with the title \"" << title << "\" already exists." << endl;
        return;
    }

    books.insert(Book(id, title, author));
    bookTitleToId[title] = id;
    saveToDatabase(); // Save changes
    cout << "Book added successfully!" << endl;
}

// Search for a book by ID
bool LibrarySystem::searchBookById(int id) {
    auto it = books.find(Book(id, "", ""));
    return it != books.end();
}

// Search for a book by title
bool LibrarySystem::searchBookByTitle(const string &title) {
    return bookTitleToId.find(title) != bookTitleToId.end();
}

// Display all books
void LibrarySystem::displayBooks() {
    if (books.empty()) {
        cout << "The library is empty." << endl;
        return;
    }

    for (auto book : books) {
        book.display();
    }
}

// Borrow a book by ID
bool LibrarySystem::borrowBook(int id) {
    auto it = books.find(Book(id, "", ""));
    if (it != books.end() && borrowedBooks.find(id) == borrowedBooks.end()) {
        borrowedBooks[id] = true;
        const_cast<Book&>(*it).isAvailable = false;
        saveToDatabase(); // Save changes
        cout << "Book borrowed successfully!" << endl;
        return true;
    }
    cout << "Book not available or already borrowed." << endl;
    return false;
}

// Borrow a book by title
bool LibrarySystem::borrowBookByTitle(const string &title) {
    if (searchBookByTitle(title)) {
        int id = bookTitleToId[title];
        return borrowBook(id);
    }
    cout << "Book not found by title." << endl;
    return false;
}

// Return a book by ID
bool LibrarySystem::returnBook(int id) {
    if (borrowedBooks.find(id) != borrowedBooks.end()) {
        borrowedBooks.erase(id);
        auto it = books.find(Book(id, "", ""));
        if (it != books.end()) {
            const_cast<Book&>(*it).isAvailable = true;
            saveToDatabase(); // Save changes
            cout << "Book returned successfully!" << endl;
            return true;
        }
    }
    cout << "Invalid book ID or not borrowed." << endl;
    return false;
}

// Return a book by title
bool LibrarySystem::returnBookByTitle(const string &title) {
    if (searchBookByTitle(title)) {
        int id = bookTitleToId[title];
        return returnBook(id);
    }
    cout << "Invalid book title or not borrowed." << endl;
    return false;
}