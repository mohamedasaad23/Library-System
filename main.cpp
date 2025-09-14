#include <iostream>
#include "LibrarySystem.h"

int main() {
    LibrarySystem library;

    int choice, id;
    string title, author;

    do {
        cout << "\n=== Library System Menu ===" << endl;
        cout << "1. Display all books" << endl;
        cout << "2. Add a book" << endl;
        cout << "3. Search for a book by ID" << endl;
        cout << "4. Search for a book by title" << endl;
        cout << "5. Borrow a book by ID" << endl;
        cout << "6. Borrow a book by title" << endl;
        cout << "7. Return a book by ID" << endl;
        cout << "8. Return a book by title" << endl;
        cout << "9. Save database" << endl;
        cout << "10. Clear database" << endl;
        cout << "11. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.displayBooks();
                break;
            case 2:
                cout << "Enter book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter book title: ";
                getline(cin, title);
                cout << "Enter book author: ";
                getline(cin, author);
                library.addBook(id, title, author);
                break;
            case 3:
                cout << "Enter book ID to search: ";
                cin >> id;
                if (library.searchBookById(id)) {
                    cout << "Book found!" << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            case 4:
                cout << "Enter book title to search: ";
                cin.ignore();
                getline(cin, title);
                if (library.searchBookByTitle(title)) {
                    cout << "Book found!" << endl;
                } else {
                    cout << "Book not found." << endl;
                }
                break;
            case 5:
                cout << "Enter book ID to borrow: ";
                cin >> id;
                library.borrowBook(id);
                break;
            case 6:
                cout << "Enter book title to borrow: ";
                cin.ignore();
                getline(cin, title);
                library.borrowBookByTitle(title);
                break;
            case 7:
                cout << "Enter book ID to return: ";
                cin >> id;
                library.returnBook(id);
                break;
            case 8:
                cout << "Enter book title to return: ";
                cin.ignore();
                getline(cin, title);
                library.returnBookByTitle(title);
                break;
            case 9:
                library.saveToDatabase();
                break;
            case 10:
                cout << "Are you sure you want to clear the database? (1=Yes, 0=No): ";
                int confirm;
                cin >> confirm;
                if (confirm == 1) {
                    library.clearDatabase();
                }
                break;
            case 11:
                cout << "Exiting system. Data will be saved automatically." << endl;
                break;
            default:
                cout << "Invalid choice, try again." << endl;
        }

    } while (choice != 11);

    return 0;
}