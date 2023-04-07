//
// Created by Yusuf Pisan on 3/26/18.
//

/**
 * @file library.h
 * @author Vikrant Verma
 *
 * Header file for library class.
 *
 * Stores books and has functions to add,
 * remove, search, and list books.
 *
 */

#ifndef ASS1_LIBRARY_H
#define ASS1_LIBRARY_H

#include <string>

// Only for class code, OK to use namespace
using namespace std;

// Library holds books - can add, remove and list books
class Library {
   /**
    * Allows display of books using the << operator
    */
   friend ostream& operator<<(ostream& Out, const Library& Lib);

 public:
   /** 
   * constructor with default name 
   */
   explicit Library();

   /** 
   * constructor with passed name 
   */
   explicit Library(const string& Name);

   /**
    * Destructor
    */
   virtual ~Library();

   /**
    * Adds a new book to the library and returns true if successful
    */
   bool addBook(const string& BookName);

   /**
    * Removes a book from the library and returns true if successful
    */
   bool removeBook(const string& BookName);

   /**
    * List all books
    */
   void listAllBooks() const;

   /**
    * Checks if a book is in the library
    */
   bool isInLibrary(const string& BookName) const;

   /**
    * Returns the name of the library
    */
   string getName() const;

   /**
    * Returns the number of books in the library
    */
   int getNumOfBooks() const;

   /**
    * Sets a new library name
    */
   void setName(const string& n);

 private:
   /**
    * Max no. of books in the library
    */
   static const int MAX = 100;

   /**
    * Helper function to find index of a book
    */
   int findBook(const string& name) const;

   /**
    * Number of books in the library
    */
   int numOfBooks;

   /**
    * Holds books
    */
   string arr[MAX];

   /**
    * Name of the library
    */
   string name;
};

#endif  // ASS1_LIBRARY_H