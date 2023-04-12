#include <iostream>
#include "LinkedBag.h"

int main() {
   Node n(1);
   Node n2(2, n);

   cout << n2.data << endl;

   Node n3(5);

   LinkedBag b(5);
   b.insert(n3);

   b.print();

   return 0;


}