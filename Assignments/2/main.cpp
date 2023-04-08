#include <cassert>
#include <iostream>

#include "polynomial.h"

int main() {
   vector<double> x = {0, 0, 0, 0, 2, -4, 600, 0, 10, 97, 9, 0, 2, 27, 3, 4, 0};
   vector<double> y = {0, 0, 0, 0, 0, 3, 4, 7, 0, 10, 97, 9, 0, 2, 27, 300};
   vector<double> z = {0, 10, 4, 3, 2, 0};
   vector<double> w =           {3, 4, 0};

   Polynomial p(x);
   Polynomial p2(y);
   Polynomial p3(z);
   Polynomial p4(w);

   p += p2;
   

   Polynomial in;

   // cout << r << endl;

   // cout << p << endl;
   // cout << p2 << endl;


   cout << p << endl;

   // cout << ((p > p2) ? "t" : "f") << endl;

   return 0;
}