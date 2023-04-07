#include <iostream>
#include "polynomial.h"

int main() {
   vector<double> x =       {2, 4, 5};
   vector<double> y = {1, 2, 3, 4, 5};
   Polynomial p(x);
   Polynomial p2(y);

   Polynomial r = p + p2;

   cout << r << endl;


   return 0;





}