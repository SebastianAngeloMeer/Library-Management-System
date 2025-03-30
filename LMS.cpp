#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>

using namespace std;

// Constants for validation
const int MAX_ID_LENGTH = 20;
const int MAX_ISBN_LENGTH = 20;
const int MAX_TITLE_LENGTH = 100;
const int MAX_AUTHOR_LENGTH = 50;
const int MAX_EDITION_LENGTH = 20;
const int MAX_PUBLICATION_LENGTH = 50;
const int MAX_CATEGORY_LENGTH = 20;
const int DEFAULT_LIBRARY_CAPACITY = 100;

/**
 * Book class - demonstrates encapsulation by keeping data private
 * and providing controlled access through public methods
 */
class Book {
private:
    // Private data members - ENCAPSULATION
    char id[MAX_ID_LENGTH];
    char isbn[MAX_ISBN_LENGTH];
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char edition[MAX_EDITION_LENGTH];
    char publication[MAX_PUBLICATION_LENGTH];
    char category[MAX_CATEGORY_LENGTH];

public:
    // Constructor
    Book() {
        // Initialize all strings to empty
        id[0] = '\0';
        isbn[0] = '\0';
        title[0] = '\0';
        author[0] = '\0';
        edition[0] = '\0';
        publication[0] = '\0';
        category[0] = '\0';
    }

    // Getters - part of the public interface (ABSTRACTION)
    const char* getId() const { return id; }
    const char* getIsbn() const { return isbn; }
    const char* getTitle() const { return title; }
    const char* getAuthor() const { return author; }
    const char* getEdition() const { return edition; }
    const char* getPublication() const { return publication; }
    const char* getCategory() const { return category; }

    // Setters with validation - ENCAPSULATION (protecting data with validation)
    bool setId(const char* newId) {
        if (newId == nullptr || strlen(newId) == 0) {
            return false;
        }
        
        // Check if ID contains only alphanumeric characters
        for (size_t i = 0; i < strlen(newId); ++i) {
            if (!isalnum(newId[i])) {
                return false;
            }
        }
        
        strncpy(id, newId, MAX_ID_LENGTH - 1);
        id[MAX_ID_LENGTH - 1] = '\0';
        return true;
    }

    bool setIsbn(const char* newIsbn) {
        if (newIsbn == nullptr || strlen(newIsbn) == 0) {
            return false;
        }
        
        strncpy(isbn, newIsbn, MAX_ISBN_LENGTH - 1);
        isbn[MAX_ISBN_LENGTH - 1] = '\0';
        return true;
    }

    bool setTitle(const char* newTitle) {
        if (newTitle == nullptr || strlen(newTitle) == 0) {
            return false;
        }
        
        strncpy(title, newTitle, MAX_TITLE_LENGTH - 1);
        title[MAX_TITLE_LENGTH - 1] = '\0';
        return true;
    }

    bool setAuthor(const char* newAuthor) {
        if (newAuthor == nullptr || strlen(newAuthor) == 0) {
            return false;
        }
        
        strncpy(author, newAuthor, MAX_AUTHOR_LENGTH - 1);
        author[MAX_AUTHOR_LENGTH - 1] = '\0';
        return true;
    }

    bool setEdition(const char* newEdition) {
        if (newEdition == nullptr || strlen(newEdition) == 0) {
            return false;
        }
        
        strncpy(edition, newEdition, MAX_EDITION_LENGTH - 1);
        edition[MAX_EDITION_LENGTH - 1] = '\0';
        return true;
    }

    bool setPublication(const char* newPublication) {
        if (newPublication == nullptr || strlen(newPublication) == 0) {
            return false;
        }
        
        strncpy(publication, newPublication, MAX_PUBLICATION_LENGTH - 1);
        publication[MAX_PUBLICATION_LENGTH - 1] = '\0';
        return true;
    }

    bool setCategory(const char* newCategory) {
        if (newCategory == nullptr) {
            return false;
        }
        
        // Convert to lowercase for case-insensitive comparison
        char lowerCategory[MAX_CATEGORY_LENGTH];
        strncpy(lowerCategory, newCategory, MAX_CATEGORY_LENGTH - 1);
        lowerCategory[MAX_CATEGORY_LENGTH - 1] = '\0';
        
        // Convert to lowercase
        for (size_t i = 0; i < strlen(lowerCategory); ++i) {
            lowerCategory[i] = tolower(lowerCategory[i]);
        }
        
        // Validate category is either "fiction" or "non-fiction" (case insensitive)
        if (strcmp(lowerCategory, "fiction") == 0) {
            strcpy(category, "Fiction");
            return true;
        } else if (strcmp(lowerCategory, "non-fiction") == 0) {
            strcpy(category, "Non-fiction");
            return true;
        }
        return false;
    }

    // Display book details - ABSTRACTION (hides implementation details)
    void displayDetails() const {
        cout << "ID: " << id << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Edition: " << edition << endl;
        cout << "Publication: " << publication << endl;
        cout << "Category: " << category << endl;
    }
    
    // Display book in table format - ABSTRACTION
    void displayInTable() const {
        printf("| %-6.6s | %-13.13s | %-30.30s | %-20.20s | %-8.8s | %-20.20s | %-11.11s |\n", 
               id, isbn, title, author, edition, publication, category);
    }
};

/**
 * Library class - manages a collection of books
 * Demonstrates abstraction by providing a clean interface for book operations
 */
class Library {
private:
    // Private data members - ENCAPSULATION
    Book* books;  // Dynamic array of books
    int capacity; // Maximum capacity
    int count;    // Current number of books

public:
    // Constructor
    Library(int initialCapacity = DEFAULT_LIBRARY_CAPACITY) {
        capacity = initialCapacity > 0 ? initialCapacity : DEFAULT_LIBRARY_CAPACITY;
        count = 0;
        books = new Book[capacity];
    }

    // Destructor to free memory
    ~Library() {
        delete[] books;
    }

    // Check if a book ID already exists - ENCAPSULATION
    bool isIdDuplicate(const char* id) const {
        for (int i = 0; i < count; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                return true;
            }
        }
        return false;
    }

    // Add a new book - ABSTRACTION
    bool addBook(const Book& book) {
        // Check if library is full
        if (count >= capacity) {
            return false;
        }
        
        // Validate book ID is not empty and not duplicate
        if (strlen(book.getId()) == 0 || isIdDuplicate(book.getId())) {
            return false;
        }
        
        // Add the book to the array
        books[count++] = book;
        return true;
    }

    // Find a book by ID - ENCAPSULATION (internal helper method)
    int findBookById(const char* id) const {
        for (int i = 0; i < count; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                return i;
            }
        }
        return -1; // Book not found
    }

    // Edit a book - ABSTRACTION
    bool editBook(const char* id, const Book& updatedBook) {
        int index = findBookById(id);
        if (index != -1) {
            // Preserve the original ID
            char originalId[MAX_ID_LENGTH];
            strncpy(originalId, books[index].getId(), MAX_ID_LENGTH - 1);
            originalId[MAX_ID_LENGTH - 1] = '\0';
            
            // Update the book
            books[index] = updatedBook;
            
            // Restore the original ID
            books[index].setId(originalId);
            
            return true;
        }
        return false; // Book not found
    }

    // Delete a book - ABSTRACTION
    bool deleteBook(const char* id) {
        int index = findBookById(id);
        if (index != -1) {
            // Shift all books after the deleted one
            for (int i = index; i < count - 1; i++) {
                books[i] = books[i + 1];
            }
            count--;
            return true;
        }
        return false; // Book not found
    }

    // Get a book by ID - ABSTRACTION
    bool getBookById(const char* id, Book& bookOut) const {
        int index = findBookById(id);
        if (index != -1) {
            bookOut = books[index];
            return true;
        }
        return false; // Book not found
    }

    // Display all books - ABSTRACTION
    void displayAllBooks() const {
        if (count == 0) {
            cout << "No books available in the library." << endl;
            return;
        }

        displayBookHeader();
        for (int i = 0; i < count; i++) {
            books[i].displayInTable();
            displayTableSeparator();
        }
    }

    // Display books by category - ABSTRACTION
    void displayBooksByCategory(const char* category) const {
        bool found = false;
        
        // Convert to lowercase for case-insensitive comparison
        char lowerCategory[MAX_CATEGORY_LENGTH];
        strncpy(lowerCategory, category, MAX_CATEGORY_LENGTH - 1);
        lowerCategory[MAX_CATEGORY_LENGTH - 1] = '\0';
        
        // Convert to lowercase
        for (size_t i = 0; i < strlen(lowerCategory); ++i) {
            lowerCategory[i] = tolower(lowerCategory[i]);
        }
        
        // Standardize category format
        char standardCategory[MAX_CATEGORY_LENGTH];
        if (strcmp(lowerCategory, "fiction") == 0) {
            strcpy(standardCategory, "Fiction");
        } else if (strcmp(lowerCategory, "non-fiction") == 0) {
            strcpy(standardCategory, "Non-fiction");
        } else {
            cout << "Invalid category." << endl;
            return;
        }
        
        displayBookHeader();
        for (int i = 0; i < count; i++) {
            if (strcmp(books[i].getCategory(), standardCategory) == 0) {
                books[i].displayInTable();
                displayTableSeparator();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No books found in this category." << endl;
        }
    }

    // Display a specific book by ID - ABSTRACTION
    bool displayBookById(const char* id) const {
        int index = findBookById(id);
        if (index != -1) {
            books[index].displayDetails();
            return true;
        }
        return false;
    }

    // Get the number of books - ABSTRACTION
    int getCount() const {
        return count;
    }

private:
    // Helper method to display table header - ENCAPSULATION
    void displayBookHeader() const {
        cout << "+--------+---------------+--------------------------------+----------------------+----------+----------------------+-------------+" << endl;
        cout << "| ID     | ISBN          | Title                          | Author               | Edition  | Publication          | Category    |" << endl;
        cout << "+--------+---------------+--------------------------------+----------------------+----------+----------------------+-------------+" << endl;
    }

    // Helper method to display table separator - ENCAPSULATION
    void displayTableSeparator() const {
        cout << "+--------+---------------+--------------------------------+----------------------+----------+----------------------+-------------+" << endl;
    }
};

/**
 * Helper function to clear input buffer
 * Clears any error flags and removes remaining characters from the input stream
 */
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Helper function to pause and wait for user input
 * Displays a message and waits for the user to press Enter
 */
void pauseExecution() {
    cout << "Press Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Helper function to clear the screen
 * Uses platform-specific commands to clear the console
 */
void clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

/**
 * Main function - entry point of the program
 * Implements the main menu and user interaction loop
 */
int main() {
    // Create a library with capacity for () books
    Library library(100);
    int choice = 0;
    bool exitProgram = false;
    
    // Main program loop - continues until user chooses to exit
    while (!exitProgram) {
        clearScreen();
        cout << "\n===== LIBRARY MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Book\n";
        cout << "2. Edit Book\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "5. View Books by Category\n";
        cout << "6. View All Books\n";
        cout << "7. Exit\n";
        cout << "Enter your choice (1-7): ";
        
        // Get valid menu choice - loop until valid input is received
        bool validChoice = false;
        while (!validChoice) {
            if (cin >> choice) {
                if (choice >= 1 && choice <= 7) {
                    validChoice = true;
                } else {
                    cout << "Invalid choice. Please enter a number between 1 and 7: ";
                }
            } else {
                cout << "Invalid input. Please enter a number: ";
                clearInputBuffer();
            }
        }
        
        clearInputBuffer(); // Clear the newline character from the input buffer
        
        // Process user choice
        switch (choice) {
            case 1: { // Add Book
                clearScreen();
                cout << "\n===== ADD NEW BOOK =====\n";
                
                Book newBook;
                char category[MAX_CATEGORY_LENGTH];
                bool validCategory = false;
                
                // Get and validate category first - loop until valid input
                while (!validCategory) {
                    cout << "Enter Category (Fiction/Non-fiction): ";
                    cin.getline(category, MAX_CATEGORY_LENGTH);
                    
                    // Convert to lowercase for case-insensitive comparison
                    char lowerCategory[MAX_CATEGORY_LENGTH];
                    strncpy(lowerCategory, category, MAX_CATEGORY_LENGTH - 1);
                    lowerCategory[MAX_CATEGORY_LENGTH - 1] = '\0';
                    
                    for (size_t i = 0; i < strlen(lowerCategory); ++i) {
                        lowerCategory[i] = tolower(lowerCategory[i]);
                    }
                    
                    if (strcmp(lowerCategory, "fiction") == 0 || strcmp(lowerCategory, "non-fiction") == 0) {
                        newBook.setCategory(category);
                        validCategory = true;
                    } else {
                        cout << "Category not found! Please enter either 'Fiction' or 'Non-fiction'.\n";
                    }
                }
                
                // Get and validate ID - loop until valid input
                char id[MAX_ID_LENGTH];
                bool validId = false;
                
                while (!validId) {
                    cout << "Enter ID (alphanumeric only): ";
                    cin.getline(id, MAX_ID_LENGTH);
                    
                    if (strlen(id) == 0) {
                        cout << "ID cannot be empty. Please enter a valid ID.\n";
                        continue;
                    }
                    
                    // Check if ID contains only alphanumeric characters
                    bool alphanumeric = true;
                    for (size_t i = 0; i < strlen(id); ++i) {
                        if (!isalnum(id[i])) {
                            alphanumeric = false;
                            break;
                        }
                    }
                    
                    if (!alphanumeric) {
                        cout << "ID must contain only alphanumeric characters.\n";
                        continue;
                    }
                    
                    if (library.isIdDuplicate(id)) {
                        cout << "Duplicate ID! Please enter a unique ID.\n";
                    } else if (newBook.setId(id)) {
                        validId = true;
                    } else {
                        cout << "Invalid ID format. Please try again.\n";
                    }
                }
                
                // Get other book details
                char isbn[MAX_ISBN_LENGTH];
                char title[MAX_TITLE_LENGTH];
                char author[MAX_AUTHOR_LENGTH];
                char edition[MAX_EDITION_LENGTH];
                char publication[MAX_PUBLICATION_LENGTH];
                
                cout << "Enter ISBN: ";
                cin.getline(isbn, MAX_ISBN_LENGTH);
                newBook.setIsbn(isbn);
                
                cout << "Enter Title: ";
                cin.getline(title, MAX_TITLE_LENGTH);
                newBook.setTitle(title);
                
                cout << "Enter Author: ";
                cin.getline(author, MAX_AUTHOR_LENGTH);
                newBook.setAuthor(author);
                
                cout << "Enter Edition: ";
                cin.getline(edition, MAX_EDITION_LENGTH);
                newBook.setEdition(edition);
                
                cout << "Enter Publication: ";
                cin.getline(publication, MAX_PUBLICATION_LENGTH);
                newBook.setPublication(publication);
                
                // Add the book to the library
                if (library.addBook(newBook)) {
                    cout << "Book added successfully!\n";
                } else {
                    cout << "Failed to add book. Library might be full.\n";
                }
                
                pauseExecution();
                break;
            }
            
            case 2: { // Edit Book
                clearScreen();
                cout << "\n===== EDIT BOOK =====\n";
                
                char id[MAX_ID_LENGTH];
                cout << "Enter the ID of the book to edit: ";
                cin.getline(id, MAX_ID_LENGTH);
                
                Book bookToEdit;
                if (library.getBookById(id, bookToEdit)) {
                    cout << "\nCurrent Book Details:\n";
                    bookToEdit.displayDetails();
                    cout << "\nEnter new details (leave blank to keep current value):\n";
                    
                    Book updatedBook;
                    updatedBook.setId(id); // Keep the same ID
                    
                    char input[MAX_TITLE_LENGTH]; // Using the largest buffer size for all inputs
                    
                    // Category - loop until valid input or empty (keep current)
                    bool validCategory = false;
                    while (!validCategory) {
                        cout << "Enter Category (Fiction/Non-fiction) [" << bookToEdit.getCategory() << "]: ";
                        cin.getline(input, MAX_CATEGORY_LENGTH);
                        
                        if (strlen(input) == 0) {
                            // Keep the current value
                            updatedBook.setCategory(bookToEdit.getCategory());
                            validCategory = true;
                        } else {
                            // Convert to lowercase for case-insensitive comparison
                            char lowerInput[MAX_CATEGORY_LENGTH];
                            strncpy(lowerInput, input, MAX_CATEGORY_LENGTH - 1);
                            lowerInput[MAX_CATEGORY_LENGTH - 1] = '\0';
                            
                            for (size_t i = 0; i < strlen(lowerInput); ++i) {
                                lowerInput[i] = tolower(lowerInput[i]);
                            }
                            
                            if (strcmp(lowerInput, "fiction") == 0 || strcmp(lowerInput, "non-fiction") == 0) {
                                updatedBook.setCategory(input);
                                validCategory = true;
                            } else {
                                cout << "Category not found! Please enter either 'Fiction' or 'Non-fiction'.\n";
                            }
                        }
                    }
                    
                    // ISBN
                    cout << "Enter ISBN [" << bookToEdit.getIsbn() << "]: ";
                    cin.getline(input, MAX_ISBN_LENGTH);
                    if (strlen(input) == 0) {
                        updatedBook.setIsbn(bookToEdit.getIsbn());
                    } else {
                        updatedBook.setIsbn(input);
                    }
                    
                    // Title
                    cout << "Enter Title [" << bookToEdit.getTitle() << "]: ";
                    cin.getline(input, MAX_TITLE_LENGTH);
                    if (strlen(input) == 0) {
                        updatedBook.setTitle(bookToEdit.getTitle());
                    } else {
                        updatedBook.setTitle(input);
                    }
                    
                    // Author
                    cout << "Enter Author [" << bookToEdit.getAuthor() << "]: ";
                    cin.getline(input, MAX_AUTHOR_LENGTH);
                    if (strlen(input) == 0) {
                        updatedBook.setAuthor(bookToEdit.getAuthor());
                    } else {
                        updatedBook.setAuthor(input);
                    }
                    
                    // Edition
                    cout << "Enter Edition [" << bookToEdit.getEdition() << "]: ";
                    cin.getline(input, MAX_EDITION_LENGTH);
                    if (strlen(input) == 0) {
                        updatedBook.setEdition(bookToEdit.getEdition());
                    } else {
                        updatedBook.setEdition(input);
                    }
                    
                    // Publication
                    cout << "Enter Publication [" << bookToEdit.getPublication() << "]: ";
                    cin.getline(input, MAX_PUBLICATION_LENGTH);
                    if (strlen(input) == 0) {
                        updatedBook.setPublication(bookToEdit.getPublication());
                    } else {
                        updatedBook.setPublication(input);
                    }
                    
                    // Update the book
                    if (library.editBook(id, updatedBook)) {
                        cout << "Book edited successfully!\n";
                    } else {
                        cout << "Failed to edit book.\n";
                    }
                } else {
                    cout << "Book not found!\n";
                }
                
                pauseExecution();
                break;
            }
            
            case 3: { // Search Book
                clearScreen();
                cout << "\n===== SEARCH BOOK =====\n";
                
                char id[MAX_ID_LENGTH];
                cout << "Enter the ID of the book to search: ";
                cin.getline(id, MAX_ID_LENGTH);
                
                if (!library.displayBookById(id)) {
                    cout << "Book not found!\n";
                }
                
                pauseExecution();
                break;
            }
            
            case 4: { // Delete Book
                clearScreen();
                cout << "\n===== DELETE BOOK =====\n";
                
                char id[MAX_ID_LENGTH];
                cout << "Enter the ID of the book to delete: ";
                cin.getline(id, MAX_ID_LENGTH);
                
                Book bookToDelete;
                if (library.getBookById(id, bookToDelete)) {
                    cout << "\nBook Details:\n";
                    bookToDelete.displayDetails();
                    
                    char confirm;
                    bool validConfirm = false;
                    
                    // Get confirmation - loop until valid input
                    while (!validConfirm) {
                        cout << "\nDo you want to delete this book? (y/n): ";
                        
                        if (cin >> confirm) {
                            confirm = tolower(confirm); // Convert to lowercase for case-insensitive comparison
                            
                            if (confirm == 'y' || confirm == 'n') {
                                validConfirm = true;
                            } else {
                                cout << "Invalid input. Please enter 'y' or 'n'.\n";
                            }
                        } else {
                            cout << "Invalid input. Please enter 'y' or 'n'.\n";
                            clearInputBuffer();
                        }
                    }
                    
                    clearInputBuffer(); // Clear the newline character
                    
                    if (confirm == 'y') {
                        if (library.deleteBook(id)) {
                            cout << "Book deleted successfully!\n";
                        } else {
                            cout << "Failed to delete book.\n";
                        }
                    } else {
                        cout << "Deletion cancelled.\n";
                    }
                } else {
                    cout << "Book not found!\n";
                }
                
                pauseExecution();
                break;
            }
            
            case 5: { // View Books by Category
                clearScreen();
                cout << "\n===== VIEW BOOKS BY CATEGORY =====\n";
                
                char category[MAX_CATEGORY_LENGTH];
                bool validCategory = false;
                
                // Get and validate category - loop until valid input
                while (!validCategory) {
                    cout << "Enter Category (Fiction/Non-fiction): ";
                    cin.getline(category, MAX_CATEGORY_LENGTH);
                    
                    // Convert to lowercase for case-insensitive comparison
                    char lowerCategory[MAX_CATEGORY_LENGTH];
                    strncpy(lowerCategory, category, MAX_CATEGORY_LENGTH - 1);
                    lowerCategory[MAX_CATEGORY_LENGTH - 1] = '\0';
                    
                    for (size_t i = 0; i < strlen(lowerCategory); ++i) {
                        lowerCategory[i] = tolower(lowerCategory[i]);
                    }
                    
                    if (strcmp(lowerCategory, "fiction") == 0 || strcmp(lowerCategory, "non-fiction") == 0) {
                        validCategory = true;
                        cout << "\nBooks in category '" << category << "':\n";
                        library.displayBooksByCategory(category);
                    } else {
                        cout << "Category not found! Please enter either 'Fiction' or 'Non-fiction'.\n";
                    }
                }
                
                pauseExecution();
                break;
            }
            
            case 6: { // View All Books
                clearScreen();
                cout << "\n===== VIEW ALL BOOKS =====\n";
                
                if (library.getCount() > 0) {
                    cout << "Total Books: " << library.getCount() << "\n\n";
                    library.displayAllBooks();
                } else {
                    cout << "No books available in the library.\n";
                }
                
                pauseExecution();
                break;
            }
            
            case 7: // Exit
                cout << "Exiting the Library Management System. Goodbye!\n";
                exitProgram = true;
                break;
        }
    }
    
    return 0;
}