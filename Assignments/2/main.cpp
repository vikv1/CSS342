#include <cassert>
#include <iostream>

#include "polynomial.h"

int main() {
   vector<double> x = {0, 0, 0, 0, 2, 4, 600, 0, 10, 97, 9, 0, 2, 27, 3, 4, 0};
   vector<double> y = {0, 0, 0, 0, 0, 3, 4, 7, 0, 10, 97, 9, 0, 2, 27, 300};
   Polynomial p(x);
   Polynomial p2(y);

   Polynomial r = p + p2;

   // cout << r << endl;

   cout << p << endl;
   cout << p2 << endl;

   cout << ((p > p2) ? "t" : "f") << endl;

   return 0;
}