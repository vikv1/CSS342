#include "library.h"
#include <iostream>


// constructor with default name
Library::Library(const string &Name) {
   numOfBooks = 0;
}

// destructor
// nothing on heap
Library::~Library() {
  // destructor
}

// true if book found in library
bool Library::isInLibrary(const string &BookName) const {
   for(int i = 0; i < arr->size(); i++) {
      if(arr[i].compare(BookName) == 0) {
         return true;
      }
   }

  return false;
}

// add a new book
// return true if successful, false if
// book already in library
bool Library::addBook(const string &BookName) {
  if(!isInLibrary(BookName)) {
    arr[numOfBooks++] = BookName;
    return true;
  } 
  return false;
}

// remove a book
// return true if successfully removed
// false if book not in library
bool Library::removeBook(const string &BookName) {
  int ind = findBook(BookName);
  
  if(ind == -1) {
    return false;
  } else {
   
    arr[ind] = arr[--numOfBooks];

    return true;
  }

}

// list all books
void Library::listAllBooks() const {
   if(numOfBooks == 0) {
      cout << "no books!" << "\n";
   }
   for(int i = 0; i < numOfBooks; i++) {
      if(arr[i].compare("") != 0) //if current element is not empty
        cout << arr[i] << endl;
   }

}


int Library::findBook(const string& name) const {
   for(int i = 0; i < arr->size(); i++) {
      if(arr[i].compare(name) == 0) {
         return i;
      }
   }

   return -1;
}




ostream &operator<<(ostream &Out, const Library &Lib) {
  return Out;
}