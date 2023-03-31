#include "library.h"

#include <cassert>
#include <iostream>

using namespace std;

void test1() {
  Library Libs("UWB");
  Libs.addBook("Don Quixote");
  Libs.addBook("In Search of Lost Time");
  Libs.addBook("Ulysses");
  Libs.addBook("The Odyssey");
  Libs.listAllBooks();

  // should generate already in library message and return true
  bool Result = Libs.isInLibrary("The Odyssey");
  assert(Result);

  // cannot add book twice, result should be false
  Result = Libs.addBook("The Odyssey");
  assert(!Result);

  // test remove, result should be true
  Result = Libs.removeBook("The Odyssey");
  assert(Result);

  Result = Libs.addBook("a");
  assert(Result);

  Result = Libs.removeBook("In Search of Lost Time");
  assert(Result);

  // not in library, result should be false
  Result = Libs.isInLibrary("The Odyssey");
  assert(!Result);

  Result = Libs.isInLibrary("Don Quixote");
  assert(Result);

  Result = Libs.isInLibrary("In Search of Lost Time");
  assert(!Result);

  // cannot remove twice, result should be false
  Result = Libs.removeBook("The Odyssey");
  assert(!Result);

  Result = Libs.removeBook("Don Quixote");
  assert(Result);

  Result = Libs.removeBook("In Search of Lost Time");
  assert(!Result);

  Result = Libs.removeBook("Ulysses");
  assert(Result);

  Result = Libs.removeBook("a");
  assert(Result);

  // removed all books ^

  cout << "\n";
  Libs.listAllBooks();
}

void testAll() {
  test1();
  cout << "Successfully completed all tests." << endl;
}

int main() {
  testAll();
  return 0;
}