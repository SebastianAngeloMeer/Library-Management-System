#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>
#include <string> // Added for std::string

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
 * Helper function to clear input buffer
 * Clears any error flags and removes remaining characters from the input stream
 */
void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

/**
 * Helper function to validate if a string contains only alphanumeric characters
 * Returns true if the string is alphanumeric, false otherwise
 */
bool isAlphanumeric(const char* str) {
    if (str == nullptr || strlen(str) == 0) {
        return false;
    }
    
    for (size_t i = 0; i < strlen(str); ++i) {
        if (!isalnum(str[i])) {
            return false;
        }
    }
    return true;
}

/**
 * LibraryItem abstract base class - demonstrates ABSTRACTION through virtual functions
 * Defines the interface for all library items
 */
class LibraryItem {
protected:
    // Protected data members accessible to derived classes
    char id[MAX_ID_LENGTH];
    char title[MAX_TITLE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];

public:
    // Constructor
    LibraryItem() {
        id[0] = '\0';
        title[0] = '\0';
        category[0] = '\0';
    }
    
    // Virtual destructor for proper cleanup in derived classes
    virtual ~LibraryItem() {}

    // Getters
    const char* getId() const { return id; }
    const char* getTitle() const { return title; }
    const char* getCategory() const { return category; }

    // Setters with validation
    bool setId(const char* newId) {
        // Validate ID is not null or empty
        if (newId == nullptr || strlen(newId) == 0) {
            return false;
        }
        
        // Validate ID length
        if (strlen(newId) > MAX_ID_LENGTH - 1) {
            return false;
        }
        
        // Check if ID contains only alphanumeric characters
        if (!isAlphanumeric(newId)) {
            return false;
        }
        
        // Copy ID with bounds checking
        strncpy(id, newId, MAX_ID_LENGTH - 1);
        id[MAX_ID_LENGTH - 1] = '\0';
        return true;
    }

    bool setTitle(const char* newTitle) {
        // Validate title is not null or empty
        if (newTitle == nullptr || strlen(newTitle) == 0) {
            return false;
        }
        
        // Validate title length
        if (strlen(newTitle) > MAX_TITLE_LENGTH - 1) {
            return false;
        }
        
        // Copy title with bounds checking
        strncpy(title, newTitle, MAX_TITLE_LENGTH - 1);
        title[MAX_TITLE_LENGTH - 1] = '\0';
        return true;
    }

    // Pure virtual functions - ABSTRACTION
    virtual bool setCategory(const char* newCategory) = 0;
    virtual void displayDetails() const = 0;
    virtual void displayInTable() const = 0;
};

/**
 * Book class - inherits from LibraryItem
 * Implements the abstract methods defined in the base class
 */
class Book : public LibraryItem {
private:
    // Private data members - ENCAPSULATION
    char isbn[MAX_ISBN_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char edition[MAX_EDITION_LENGTH];
    char publication[MAX_PUBLICATION_LENGTH];

public:
    // Constructor
    Book() : LibraryItem() {
        isbn[0] = '\0';
        author[0] = '\0';
        edition[0] = '\0';
        publication[0] = '\0';
    }

    // Getters
    const char* getIsbn() const { return isbn; }
    const char* getAuthor() const { return author; }
    const char* getEdition() const { return edition; }
    const char* getPublication() const { return publication; }

    // Setters with validation
    bool setIsbn(const char* newIsbn) {
        // Validate ISBN is not null or empty
        if (newIsbn == nullptr || strlen(newIsbn) == 0) {
            return false;
        }
        
        // Validate ISBN length
        if (strlen(newIsbn) > MAX_ISBN_LENGTH - 1) {
            return false;
        }
        
        // Copy ISBN with bounds checking
        strncpy(isbn, newIsbn, MAX_ISBN_LENGTH - 1);
        isbn[MAX_ISBN_LENGTH - 1] = '\0';
        return true;
    }

    bool setAuthor(const char* newAuthor) {
        // Validate author is not null or empty
        if (newAuthor == nullptr || strlen(newAuthor) == 0) {
            return false;
        }
        
        // Validate author length
        if (strlen(newAuthor) > MAX_AUTHOR_LENGTH - 1) {
            return false;
        }
        
        // Copy author with bounds checking
        strncpy(author, newAuthor, MAX_AUTHOR_LENGTH - 1);
        author[MAX_AUTHOR_LENGTH - 1] = '\0';
        return true;
    }

    bool setEdition(const char* newEdition) {
        // Validate edition is not null or empty
        if (newEdition == nullptr || strlen(newEdition) == 0) {
            return false;
        }
        
        // Validate edition length
        if (strlen(newEdition) > MAX_EDITION_LENGTH - 1) {
            return false;
        }
        
        // Copy edition with bounds checking
        strncpy(edition, newEdition, MAX_EDITION_LENGTH - 1);
        edition[MAX_EDITION_LENGTH - 1] = '\0';
        return true;
    }

    bool setPublication(const char* newPublication) {
        // Validate publication is not null or empty
        if (newPublication == nullptr || strlen(newPublication) == 0) {
            return false;
        }
        
        // Validate publication length
        if (strlen(newPublication) > MAX_PUBLICATION_LENGTH - 1) {
            return false;
        }
        
        // Copy publication with bounds checking
        strncpy(publication, newPublication, MAX_PUBLICATION_LENGTH - 1);
        publication[MAX_PUBLICATION_LENGTH - 1] = '\0';
        return true;
    }

    // Implementation of virtual function - ABSTRACTION
    virtual bool setCategory(const char* newCategory) override {
        // Validate category is not null or empty
        if (newCategory == nullptr || strlen(newCategory) == 0) {
            return false;
        }
        
        // Validate category length
        if (strlen(newCategory) > MAX_CATEGORY_LENGTH - 1) {
            return false;
        }
        
        // Case-sensitive validation for category
        if (strcmp(newCategory, "Fiction") == 0 || strcmp(newCategory, "Non-fiction") == 0) {
            strncpy(category, newCategory, MAX_CATEGORY_LENGTH - 1);
            category[MAX_CATEGORY_LENGTH - 1] = '\0';
            return true;
        }
        return false;
    }

    // Implementation of virtual function - ABSTRACTION
    virtual void displayDetails() const override {
        cout << "ID: " << id << endl;
        cout << "ISBN: " << isbn << endl;
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Edition: " << edition << endl;
        cout << "Publication: " << publication << endl;
        cout << "Category: " << category << endl;
    }
    
    // Implementation of virtual function - ABSTRACTION
    virtual void displayInTable() const override {
        printf("| %-6.6s | %-13.13s | %-30.30s | %-20.20s | %-8.8s | %-20.20s | %-11.11s |\n", 
               id, isbn, title, author, edition, publication, category);
    }
};

/**
 * ItemManager abstract base class - demonstrates ABSTRACTION through virtual functions
 * Defines the interface for managing collections of items
 */
class ItemManager {
public:
    virtual ~ItemManager() {}
    
    // Pure virtual functions - ABSTRACTION
    virtual bool addItem(const LibraryItem& item) = 0;
    virtual bool deleteItem(const char* id) = 0;
    virtual bool displayItemById(const char* id) const = 0;
    virtual void displayAllItems() const = 0;
    virtual int getItemCount() const = 0;
};

/**
 * Library class - implements ItemManager
 * Manages a collection of books
 */
class Library : public ItemManager {
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
    virtual ~Library() override {
        delete[] books;
    }

    // Check if a book ID already exists - ENCAPSULATION
    bool isIdDuplicate(const char* id) const {
        // Validate ID is not null or empty
        if (id == nullptr || strlen(id) == 0) {
            return false;
        }
        
        for (int i = 0; i < count; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                return true;
            }
        }
        return false;
    }

    // Implementation of virtual function - ABSTRACTION
    virtual bool addItem(const LibraryItem& item) override {
        // Check if item is a Book
        const Book* bookItem = dynamic_cast<const Book*>(&item);
        if (!bookItem) {
            return false; // Not a Book
        }
        
        return addBook(*bookItem);
    }
    
    // Add a new book - specific implementation
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
        // Validate ID is not null or empty
        if (id == nullptr || strlen(id) == 0) {
            return -1;
        }
        
        for (int i = 0; i < count; i++) {
            if (strcmp(books[i].getId(), id) == 0) {
                return i;
            }
        }
        return -1; // Book not found
    }

    // Edit a book
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

    // Implementation of virtual function - ABSTRACTION
    virtual bool deleteItem(const char* id) override {
        return deleteBook(id);
    }
    
    // Delete a book - specific implementation
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

    // Get a book by ID
    bool getBookById(const char* id, Book& bookOut) const {
        int index = findBookById(id);
        if (index != -1) {
            bookOut = books[index];
            return true;
        }
        return false; // Book not found
    }

    // Implementation of virtual function - ABSTRACTION
    virtual void displayAllItems() const override {
        displayAllBooks();
    }
    
    // Display all books - specific implementation
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

    // Display books by category
    void displayBooksByCategory(const char* category) const {
        // Validate category is not null or empty
        if (category == nullptr || strlen(category) == 0) {
            cout << "Invalid category." << endl;
            return;
        }
        
        bool found = false;
        
        // Case-sensitive category comparison
        displayBookHeader();
        for (int i = 0; i < count; i++) {
            if (strcmp(books[i].getCategory(), category) == 0) {
                books[i].displayInTable();
                displayTableSeparator();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No books found in this category." << endl;
        }
    }

    // Implementation of virtual function - ABSTRACTION
    virtual bool displayItemById(const char* id) const override {
        return displayBookById(id);
    }
    
    // Display a specific book by ID - specific implementation
    bool displayBookById(const char* id) const {
        int index = findBookById(id);
        if (index != -1) {
            books[index].displayDetails();
            return true;
        }
        return false;
    }

    // Implementation of virtual function - ABSTRACTION
    virtual int getItemCount() const override {
        return getCount();
    }
    
    // Get the number of books - specific implementation
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
 * Helper function to get a valid string input
 * Ensures the input is not empty and fits within the specified buffer size
 * Returns true if valid input was received, false otherwise
 */
bool getValidString(char* buffer, size_t bufferSize, const string& prompt, bool allowEmpty = false) {
    if (buffer == nullptr || bufferSize == 0) {
        return false;
    }
    
    bool isValid = false;
    while (!isValid) {
        cout << prompt;
        cin.getline(buffer, bufferSize);
        
        // Check for input errors
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input error. Please try again." << endl;
            continue;
        }
        
        // Check if input is empty
        if (strlen(buffer) == 0 && !allowEmpty) {
            cout << "Input cannot be empty. Please try again." << endl;
            continue;
        }
        
        isValid = true;
    }
    
    return true;
}

/**
 * Helper function to validate category input
 * Ensures the category is either "Fiction" or "Non-fiction" (case-sensitive)
 * Returns true if valid category was received, false otherwise
 */
bool getValidCategory(char* buffer, size_t bufferSize, const string& prompt) {
    if (buffer == nullptr || bufferSize == 0) {
        return false;
    }
    
    bool isValid = false;
    while (!isValid) {
        if (!getValidString(buffer, bufferSize, prompt)) {
            return false;
        }
        
        // Case-sensitive validation
        if (strcmp(buffer, "Fiction") == 0 || strcmp(buffer, "Non-fiction") == 0) {
            isValid = true;
        } else {
            cout << "Category must be exactly 'Fiction' or 'Non-fiction' (case-sensitive)." << endl;
        }
    }
    
    return true;
}

/**
 * Helper function to validate ID input
 * Ensures the ID contains only alphanumeric characters
 * Returns true if valid ID was received, false otherwise
 */
bool getValidId(char* buffer, size_t bufferSize, const string& prompt, const Library& library, bool checkDuplicate = true) {
    if (buffer == nullptr || bufferSize == 0) {
        return false;
    }
    
    bool isValid = false;
    while (!isValid) {
        if (!getValidString(buffer, bufferSize, prompt)) {
            return false;
        }
        
        // Check if ID contains only alphanumeric characters
        bool alphanumeric = true;
        for (size_t i = 0; i < strlen(buffer); ++i) {
            if (!isalnum(buffer[i])) {
                alphanumeric = false;
                break;
            }
        }
        
        if (!alphanumeric) {
            cout << "ID must contain only alphanumeric characters." << endl;
            continue;
        }
        
        // Check for duplicate ID if required
        if (checkDuplicate && library.isIdDuplicate(buffer)) {
            cout << "Duplicate ID! Please enter a unique ID." << endl;
            continue;
        }
        
        isValid = true;
    }
    
    return true;
}

/**
 * Main function - entry point of the program
 * Implements the main menu and user interaction loop
 */
int main() {
    // Create a library with capacity for 100 books
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
                
                // Get and validate category (case-sensitive)
                if (!getValidCategory(category, MAX_CATEGORY_LENGTH, "Enter Category (Fiction/Non-fiction): ")) {
                    cout << "Failed to get valid category. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                if (!newBook.setCategory(category)) {
                    cout << "Failed to set category. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                // Get and validate ID
                char id[MAX_ID_LENGTH];
                if (!getValidId(id, MAX_ID_LENGTH, "Enter ID (alphanumeric only): ", library)) {
                    cout << "Failed to get valid ID. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                if (!newBook.setId(id)) {
                    cout << "Failed to set ID. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                // Get other book details
                char isbn[MAX_ISBN_LENGTH];
                char title[MAX_TITLE_LENGTH];
                char author[MAX_AUTHOR_LENGTH];
                char edition[MAX_EDITION_LENGTH];
                char publication[MAX_PUBLICATION_LENGTH];
                
                if (!getValidString(isbn, MAX_ISBN_LENGTH, "Enter ISBN: ")) {
                    cout << "Failed to get valid ISBN. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                newBook.setIsbn(isbn);
                
                if (!getValidString(title, MAX_TITLE_LENGTH, "Enter Title: ")) {
                    cout << "Failed to get valid title. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                newBook.setTitle(title);
                
                if (!getValidString(author, MAX_AUTHOR_LENGTH, "Enter Author: ")) {
                    cout << "Failed to get valid author. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                newBook.setAuthor(author);
                
                if (!getValidString(edition, MAX_EDITION_LENGTH, "Enter Edition: ")) {
                    cout << "Failed to get valid edition. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                newBook.setEdition(edition);
                
                if (!getValidString(publication, MAX_PUBLICATION_LENGTH, "Enter Publication: ")) {
                    cout << "Failed to get valid publication. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                newBook.setPublication(publication);
                
                // Add the book to the library
                if (library.addBook(newBook)) {
                    cout << "Book added successfully!" << endl;
                } else {
                    cout << "Failed to add book. Library might be full." << endl;
                }
                
                pauseExecution();
                break;
            }
            
            case 2: { // Edit Book
                clearScreen();
                cout << "\n===== EDIT BOOK =====\n";
                
                char id[MAX_ID_LENGTH];
                if (!getValidId(id, MAX_ID_LENGTH, "Enter the ID of the book to edit: ", library, false)) {
                    cout << "Failed to get valid ID. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                Book bookToEdit;
                if (library.getBookById(id, bookToEdit)) {
                    cout << "\nCurrent Book Details:\n";
                    bookToEdit.displayDetails();
                    cout << "\nEnter new details (leave blank to keep current value):\n";
                    
                    Book updatedBook;
                    updatedBook.setId(id); // Keep the same ID
                    
                    char input[MAX_TITLE_LENGTH]; // Using the largest buffer size for all inputs
                    
                    // Category (case-sensitive)
                    string categoryPrompt = "Enter Category (Fiction/Non-fiction) [" + string(bookToEdit.getCategory()) + "]: ";
                    cout << categoryPrompt;
                    cin.getline(input, MAX_CATEGORY_LENGTH);
                    
                    if (strlen(input) == 0) {
                        // Keep the current value
                        updatedBook.setCategory(bookToEdit.getCategory());
                    } else {
                        // Case-sensitive validation
                        if (strcmp(input, "Fiction") == 0 || strcmp(input, "Non-fiction") == 0) {
                            updatedBook.setCategory(input);
                        } else {
                            cout << "Invalid category. Must be exactly 'Fiction' or 'Non-fiction'." << endl;
                            cout << "Keeping current category: " << bookToEdit.getCategory() << endl;
                            updatedBook.setCategory(bookToEdit.getCategory());
                        }
                    }
                    
                    // ISBN
                    string isbnPrompt = "Enter ISBN [" + string(bookToEdit.getIsbn()) + "]: ";
                    if (!getValidString(input, MAX_ISBN_LENGTH, isbnPrompt, true)) {
                        cout << "Failed to get valid ISBN. Returning to main menu." << endl;
                        pauseExecution();
                        break;
                    }
                    
                    if (strlen(input) == 0) {
                        updatedBook.setIsbn(bookToEdit.getIsbn());
                    } else {
                        updatedBook.setIsbn(input);
                    }
                    
                    // Title
                    string titlePrompt = "Enter Title [" + string(bookToEdit.getTitle()) + "]: ";
                    if (!getValidString(input, MAX_TITLE_LENGTH, titlePrompt, true)) {
                        cout << "Failed to get valid title. Returning to main menu." << endl;
                        pauseExecution();
                        break;
                    }
                    
                    if (strlen(input) == 0) {
                        updatedBook.setTitle(bookToEdit.getTitle());
                    } else {
                        updatedBook.setTitle(input);
                    }
                    
                    // Author
                    string authorPrompt = "Enter Author [" + string(bookToEdit.getAuthor()) + "]: ";
                    if (!getValidString(input, MAX_AUTHOR_LENGTH, authorPrompt, true)) {
                        cout << "Failed to get valid author. Returning to main menu." << endl;
                        pauseExecution();
                        break;
                    }
                    
                    if (strlen(input) == 0) {
                        updatedBook.setAuthor(bookToEdit.getAuthor());
                    } else {
                        updatedBook.setAuthor(input);
                    }
                    
                    // Edition
                    string editionPrompt = "Enter Edition [" + string(bookToEdit.getEdition()) + "]: ";
                    if (!getValidString(input, MAX_EDITION_LENGTH, editionPrompt, true)) {
                        cout << "Failed to get valid edition. Returning to main menu." << endl;
                        pauseExecution();
                        break;
                    }
                    
                    if (strlen(input) == 0) {
                        updatedBook.setEdition(bookToEdit.getEdition());
                    } else {
                        updatedBook.setEdition(input);
                    }
                    
                    // Publication
                    string publicationPrompt = "Enter Publication [" + string(bookToEdit.getPublication()) + "]: ";
                    if (!getValidString(input, MAX_PUBLICATION_LENGTH, publicationPrompt, true)) {
                        cout << "Failed to get valid publication. Returning to main menu." << endl;
                        pauseExecution();
                        break;
                    }
                    
                    if (strlen(input) == 0) {
                        updatedBook.setPublication(bookToEdit.getPublication());
                    } else {
                        updatedBook.setPublication(input);
                    }
                    
                    // Update the book
                    if (library.editBook(id, updatedBook)) {
                        cout << "Book edited successfully!" << endl;
                    } else {
                        cout << "Failed to edit book." << endl;
                    }
                } else {
                    cout << "Book not found!" << endl;
                }
                
                pauseExecution();
                break;
            }
            
            case 3: { // Search Book
                clearScreen();
                cout << "\n===== SEARCH BOOK =====\n";
                
                char id[MAX_ID_LENGTH];
                if (!getValidId(id, MAX_ID_LENGTH, "Enter the ID of the book to search: ", library, false)) {
                    cout << "Failed to get valid ID. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                // Using the virtual function through the ItemManager interface - ABSTRACTION
                if (!library.displayItemById(id)) {
                    cout << "Book not found!" << endl;
                }
                
                pauseExecution();
                break;
            }
            
            case 4: { // Delete Book
                clearScreen();
                cout << "\n===== DELETE BOOK =====\n";
                
                char id[MAX_ID_LENGTH];
                if (!getValidId(id, MAX_ID_LENGTH, "Enter the ID of the book to delete: ", library, false)) {
                    cout << "Failed to get valid ID. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
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
                            // Case-sensitive comparison
                            if (confirm == 'y' || confirm == 'Y' || confirm == 'n' || confirm == 'N') {
                                validConfirm = true;
                            } else {
                                cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                            }
                        } else {
                            cout << "Invalid input. Please enter 'y' or 'n'." << endl;
                            clearInputBuffer();
                        }
                    }
                    
                    clearInputBuffer(); // Clear the newline character
                    
                    if (confirm == 'y' || confirm == 'Y') {
                        // Using the virtual function through the ItemManager interface - ABSTRACTION
                        if (library.deleteItem(id)) {
                            cout << "Book deleted successfully!" << endl;
                        } else {
                            cout << "Failed to delete book." << endl;
                        }
                    } else {
                        cout << "Deletion cancelled." << endl;
                    }
                } else {
                    cout << "Book not found!" << endl;
                }
                
                pauseExecution();
                break;
            }
            
            case 5: { // View Books by Category
                clearScreen();
                cout << "\n===== VIEW BOOKS BY CATEGORY =====\n";
                
                char category[MAX_CATEGORY_LENGTH];
                if (!getValidCategory(category, MAX_CATEGORY_LENGTH, "Enter Category (Fiction/Non-fiction): ")) {
                    cout << "Failed to get valid category. Returning to main menu." << endl;
                    pauseExecution();
                    break;
                }
                
                cout << "\nBooks in category '" << category << "':\n";
                library.displayBooksByCategory(category);
                
                pauseExecution();
                break;
            }
            
            case 6: { // View All Books
                clearScreen();
                cout << "\n===== VIEW ALL BOOKS =====\n";
                
                // Using the virtual function through the ItemManager interface - ABSTRACTION
                if (library.getItemCount() > 0) {
                    cout << "Total Books: " << library.getItemCount() << "\n\n";
                    library.displayAllItems();
                } else {
                    cout << "No books available in the library." << endl;
                }
                
                pauseExecution();
                break;
            }
            
            case 7: // Exit
                cout << "Exiting the Library Management System. Goodbye!" << endl;
                exitProgram = true;
                break;
        }
    }
    
    return 0;
}