#include <cassert>
#include <iostream>
#include <type_traits>

#include "polynomial.h"

int main() {
#if 0
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

#endif

   // Polynomial p;
   // cin >> p;
   // cout << p << endl;

   // vector<double> x = {0, 0, 0, -1, 2, -4, 600, 0, 0, 0, 0, 10, 97, 9, 0, 2,
   // 27, 3, 4, 0}; vector<double> y = {0, 0, 0, 0, 0, 3, 4, 7, 0, 10, 97, 9, 0,
   // 2, 27, 300};

   // Polynomial p1(x);
   // // Polynomial p2(y);

   // cout << p1 << endl;
   // // cout << p2 << endl;

   // cout << endl;

   vector<double> x = {0, 0, 0, -2, 2, -4, 600, 0, 0, 0, 0, 10, 97, 9, 0, 2, 27, 3, 4, 0};
   vector<double> y = {0, 0, 0, 0, 0, 3, 4, 7, 0, 10, 97, 9, 0, -3, 27, 300};

   // x = {2, 0, 1, 2};
   // y = {2, 3, 4};

   // Polynomial p1(x);
   // Polynomial p2(y);

   // Polynomial r = p2 - p1;

   // cout << p2 << endl;
   // cout << p1 << endl;
   // cout << endl;

   // p2 -= p1;

   // cout << p2 << endl;

   // cout << endl;

   // x = {2, 1};
   // y = {3, 2};

   // {2, 1} {3, 2}
   // 6x^2 + 4x + 3x + 2

   Polynomial p1(x);
   Polynomial p2(y);

   Polynomial r = p2 * p1;
   
   cout << p1 << endl;
   cout << p1.getDegree() << endl;
   cout << endl;

   cout << p2 << endl;
   cout << p2.getDegree() << endl;
   cout << endl;

   // p1 *= p2;
   cout << r << endl;
   p1 *= p2;

   assert(p1 == r);

   return 0;
}