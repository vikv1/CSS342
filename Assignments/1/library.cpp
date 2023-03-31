#include "library.h"
#include <iostream>


// constructor with default name
Library::Library(const string &Name) { 
  numOfBooks = 0;
  this->name = Name;
}

// destructor
// nothing on heap
Library::~Library() {
  // destructor
}

// true if book found in library
bool Library::isInLibrary(const string &BookName) const {

  return findBook(BookName) !=
         -1; // reuse findbook function because it would be the exact same loop
}

// add a new book
// return true if successful, false if
// book already in library
bool Library::addBook(const string &BookName) {
  if (!isInLibrary(BookName)) {
    arr[numOfBooks++] = BookName;
    return true;
  }
  return false;
}

// remove a book
// return true if successfully removed
// false if book not in library
bool Library::removeBook(const string &BookName) {
  int ind = findBook(BookName); //index of book

  if (ind == -1) {
    return false;
  } else {
    arr[ind] = arr[--numOfBooks];

    return true;
  }
}

// list all books
void Library::listAllBooks() const {
  if (numOfBooks == 0) {
    cout << "no books!"
         << "\n";
  } else {
    for (int i = 0; i < numOfBooks; i++) {
       cout << arr[i] << endl;
    }
  }
  
}

int Library::findBook(const string &name) const {
  for (int i = 0; i < arr->size(); i++) {
    if (arr[i].compare(name) == 0) {
      return i;
    }
  }

  return -1;
}

string Library::getName() {
   return name;
}

void Library::setName(string& name) {
   this->name = name;
}

ostream &operator<<(ostream &Out, const Library &Lib) { return Out; }