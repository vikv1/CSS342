#include <cassert>
#include <iostream>

#include "library.h"

using namespace std;

void test1() {
   string name = "UWB";
   Library libs(name);
   libs.addBook("Don Quixote");
   libs.addBook("In Search of Lost Time");
   libs.addBook("Ulysses");
   libs.addBook("The Odyssey");
   libs.listAllBooks();

   cout << libs << endl;

   // should generate already in library message and return true
   bool result = libs.isInLibrary("The Odyssey");
   assert(result);

   // cannot add book twice, result should be false
   result = libs.addBook("The Odyssey");
   assert(!result);

   // test remove, result should be true
   result = libs.removeBook("The Odyssey");
   assert(result);

   result = libs.addBook("a");
   assert(result);

   result = libs.removeBook("In Search of Lost Time");
   assert(result);

   // not in library, result should be false
   result = libs.isInLibrary("The Odyssey");
   assert(!result);

   result = libs.isInLibrary("Don Quixote");
   assert(result);

   result = libs.isInLibrary("In Search of Lost Time");
   assert(!result);

   // cannot remove twice, result should be false
   result = libs.removeBook("The Odyssey");
   assert(!result);

   result = libs.removeBook("Don Quixote");
   assert(result);

   result = libs.removeBook("In Search of Lost Time");
   assert(!result);

   result = libs.removeBook("Ulysses");
   assert(result);

   result = libs.removeBook("a");
   assert(result);

   result = libs.removeBook("In Search of Lost Time");
   assert(!result);

   // removed all books ^

   for (int i = 0; i < 100; i++) {
      libs.addBook(to_string(i));
   }

   result = libs.addBook("a");
   assert(!result);  // should not be able to add more

   result = libs.isInLibrary("a");
   assert(!result);  // should not be in lib

   cout << "\n";
   cout << libs << endl;

   name = "hello";

   // library name should not be changed if variable has changed
   assert(libs.getName() == "UWB");
}

void testAll() {
   test1();
   cout << "Successfully completed all tests." << endl;
}

int main() {
   testAll();
   return 0;
}