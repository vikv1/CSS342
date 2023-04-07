/**
 * @file library.cpp
 * @author Vikrant Verma
 *
 * Implementation of the library.
 * Uses an array of strings to store books.
 * Implements the searching functions linearly.
 * @invariant numOfBooks >= 0 and is the immediate next available/empty index.
 */

#include "library.h"

#include <iostream>

/**
 * Construct a new Library object
 * Sets numOfBooks to 0
 * Sets name of the library to default name "Library"
 *
 */
Library::Library() : numOfBooks{0}, name{"Library"} {}

/**
 * Construct a new Library object
 * Sets numOfBooks to 0
 * Sets name of the library to the passed in constant reference
 *
 * @param Name
 */
Library::Library(const string& Name) : numOfBooks{0}, name{Name} {}

/**
 * Destroy the Library object
 * Heap unused, nothing to manually destroy
 *
 */
Library::~Library() {
   // destructor
}

/**
 * Adds a new book.
 *
 * If the number of books is equal to the maximum number of books,
 * notify the user and return false.
 *
 * If the book is already in the library, return false.
 *
 * Adds the book to the library by putting it at the next empty element,
 * which is at numOfBooks, and increment numOfBooks after. Return true.
 *
 * @param BookName
 * @return true
 * @return false
 */
bool Library::addBook(const string& BookName) {
   if (numOfBooks == 100) {
      cout << "Library is full, cannot add \"" << BookName << "\"" << endl;
      return false;
   }

   if (!isInLibrary(BookName)) {
      arr[numOfBooks++] = BookName;
      return true;
   }
   return false;
}

/**
 * Removes a book.
 *
 * Gets the index of a book in the library using the
 * private findBook function, which is linear. If the index is -1,
 * then the book is not in the library and false is returned.
 *
 * Otherwise, decrement numOfBooks by 1 and replace the element at the
 * index of the book to be removed with the last element in the scope of
 * numOfBooks,
 *
 * @param BookName
 * @return true
 * @return false
 */
bool Library::removeBook(const string& BookName) {
   int ind = findBook(BookName);  // index of book

   if (ind == -1) {
      return false;
   } else {
      arr[ind] = arr[--numOfBooks];

      return true;
   }
}

/**
 * Lists all the books in the library line by line by
 * linearly iterating through the private books array arr,
 * prints "no books" if numOfBooks is 0.
 *
 */
void Library::listAllBooks() const {
   if (numOfBooks == 0) {
      cout << "no books!" << endl;
   } else {
      for (int i = 0; i < numOfBooks; i++) {
         cout << arr[i] << endl;
      }
   }
}

/**
 * Private helper function that returns the index of a book in the library
 * if it exists, by iterating through the private array arr linearly.
 *
 * Returns -1 if not found, otherwise the index of the book
 *
 * @param name
 * @return int
 */
int Library::findBook(const string& name) const {
   for (int i = 0; i < arr->size(); i++) {
      if (arr[i] == name) {
         return i;
      }
   }

   return -1;
}

/**
 * Returns true if the book has a valid index in the array (is in lib),
 * false otherwise.
 *
 * Uses the findBook function to determine if the book to be found
 * has an entry in the array, findBook() returns -1 if not found.
 *
 * @param BookName
 * @return true
 * @return false
 */
bool Library::isInLibrary(const string& BookName) const {
   return findBook(BookName) != -1;
}

/**
 * Returns the current name of the library.
 *
 * @return string
 */
string Library::getName() const {
   return name;
}

/**
 * Sets the name of the library to the passed in name.
 *
 * @param name
 */

void Library::setName(const string& n) {
   this->name = n;
}

/**
 * Returns the number of books in the library.
 *
 * @return int
 */
int Library::getNumOfBooks() const {
   return numOfBooks;
}

/**
 * Overloads the << operator so the library can be printed using cout.
 *
 * @param Out
 * @param Lib
 * @return ostream&
 */
ostream& operator<<(ostream& Out, const Library& Lib) {
   string books = "";
   for (int i = 0; i < Lib.numOfBooks; i++) {
      if (i == Lib.numOfBooks - 1) {
         books += Lib.arr[i];
      } else {
         books += Lib.arr[i] + ",\n";
      }
   }

   return Out << books;
}