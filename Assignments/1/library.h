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
   // display all books in library
   friend ostream& operator<<(ostream& Out, const Library& Lib);

 public:
   // constructor with default name
   explicit Library();

   // constructor with passed name
   explicit Library(const string& Name);

   // destructor
   virtual ~Library();

   // add a new book
   // return true if successful, false if
   // book already in library
   bool addBook(const string& BookName);

   // remove a book
   // return true if successfully removed
   // false if book not in library
   bool removeBook(const string& BookName);

   // list all books
   void listAllBooks() const;

   // true if book found in library
   bool isInLibrary(const string& BookName) const;

   // return current library name
   string getName() const;

   // return number of books in library
   int getNumOfBooks() const;

   // set new library name
   void setName(string name);

 private:
   // max number of books in library
   static const int MAX = 100;

   // private helper function, finds the index of a book in library
   int findBook(const string& name) const;

   // number of current books in library
   int numOfBooks;

   // array to hold books set to size 100
   string arr[MAX];

   // library name
   string name;
};

#endif  // ASS1_LIBRARY_H