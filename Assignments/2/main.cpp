#include <cassert>
#include <iostream>

#include "polynomial.h"

void arithmeticTests(Polynomial&, Polynomial&);
void equalityTests(Polynomial&, Polynomial&, Polynomial&, Polynomial&);

int main() {
   /**
    * Tests from assignment page
    */

   Polynomial t1({1, 2, 3});  // x^2 + 2x + 3
   cout << "t1: " << t1 << endl;

   Polynomial t2({4, 5, 6});  // 4x^2 + 5x + 6
   cout << "t2: " << t2 << endl;

   Polynomial t3 = t1 + t2;
   cout << "t3: " << t3 << endl;  // output: 5x^2 + 7x + 9

   Polynomial t4 = t1 * t2;       // (x^2 + 2x + 3) * (4x^2 + 5x + 6)
   cout << "t4: " << t4 << endl;  // output: 4x^4 + 13x^3 + 28x^2 + 27x + 18

   assert(t1.toString() == "[x^2 + 2x + 3]");
   assert(t2.toString() == "[4x^2 + 5x + 6]");
   assert(t3.toString() == "[5x^2 + 7x + 9]");
   assert(t4.toString() == "[4x^4 + 13x^3 + 28x^2 + 27x + 18]");

   cout << "end assignment tests" << endl;
   cout << "start big tests" << endl;
   cout << endl;
   cout << endl;

   vector<double> x = {
      0, 0, 0, -2, 2, -4, 600, 0, 0, 0, 0, 10, 97, 9, 0, 2, 27, 3, 4, 0};
   vector<double> y = {0, 0, 0, 0, 0, 3, 4, 7, 0, 10, 97, 9, 0, -3, 27, 300, 0};

   Polynomial p1(x);
   Polynomial p2(y);

   /** @attention ARITHMETIC TESTS */
   arithmeticTests(p1, p2);

   Polynomial p3({0, 2, 1, 3});
   Polynomial p4({0, 0, 0, 2, 1, 3});
   Polynomial p5({0, 0, 0, 2, 1, 3, 0});
   Polynomial p6({0, 0, 0, 2, 1, 3, 1});
   // p6 is biggest
   // p3 and p4 are equal

   /** @attention EQUALITY TESTS  */
   equalityTests(p3, p4, p5, p6);

   cout << endl;
   cout << "passed all tests" << endl;

   // Polynomial p;

   // cin >> p;

   // cout << p << endl;

   return 0;
}

void arithmeticTests(Polynomial& p1, Polynomial& p2) {
   cout << p1 << endl;
   cout << p2 << endl;
   cout << "Doing arithmetic tests on the above polynomials" << endl;
   cout << "Answers cross-checked with Wolfram Alpha" << endl;

   cout << endl;

   /**  @attention OPERATOR TESTS  */
   // ANSWERS FROM WOLFRAM ALPHA

   ////////////////////////////////////////////////
   /////       + OF POLYNOMIALS              /////
   //////////////////////////////////////////////
   Polynomial res = p1 + p2;

   assert(res.toString() ==
          "[-2x^16 + 2x^15 - 4x^14 + 600x^13 + 3x^11 + 4x^10 + 7x^9 + 10x^8 + "
          "107x^7 + 106x^6 + 9x^5 + 2x^4 + 24x^3 + 30x^2 + 304x]");

   res = p2 + p1;

   assert(res.toString() ==
          "[-2x^16 + 2x^15 - 4x^14 + 600x^13 + 3x^11 + 4x^10 + 7x^9 + 10x^8 + "
          "107x^7 + 106x^6 + 9x^5 + 2x^4 + 24x^3 + 30x^2 + 304x]");

   ////////////////////////////////////////////////
   /////       += OF POLYNOMIALS             /////
   //////////////////////////////////////////////

   Polynomial t = p1;
   p1 += p2;

   assert(p1.toString() ==
          "[-2x^16 + 2x^15 - 4x^14 + 600x^13 + 3x^11 + 4x^10 + 7x^9 + 10x^8 + "
          "107x^7 + 106x^6 + 9x^5 + 2x^4 + 24x^3 + 30x^2 + 304x]");

   p1 = t;

   t = p2;
   p2 += p1;

   assert(p2.toString() ==
          "[-2x^16 + 2x^15 - 4x^14 + 600x^13 + 3x^11 + 4x^10 + 7x^9 + 10x^8 + "
          "107x^7 + 106x^6 + 9x^5 + 2x^4 + 24x^3 + 30x^2 + 304x]");
   p2 = t;

   ////////////////////////////////////////////////
   /////       - OF POLYNOMIALS              /////
   //////////////////////////////////////////////

   res = p2 - p1;

   assert(res.toString() ==
          "[2x^16 - 2x^15 + 4x^14 - 600x^13 + 3x^11 + 4x^10 + 7x^9 - 10x^8 - "
          "87x^7 + 88x^6 + 9x^5 - 2x^4 - 30x^3 + 24x^2 + 296x]");

   res = p1 - p2;

   assert(res.toString() ==
          "[-2x^16 + 2x^15 - 4x^14 + 600x^13 - 3x^11 - 4x^10 - 7x^9 + 10x^8 + "
          "87x^7 - 88x^6 - 9x^5 + 2x^4 + 30x^3 - 24x^2 - 296x]");

   ////////////////////////////////////////////////
   /////       -= OF POLYNOMIALS             /////
   //////////////////////////////////////////////

   t = p1;
   p1 -= p2;

   assert(p1.toString() ==
          "[-2x^16 + 2x^15 - 4x^14 + 600x^13 - 3x^11 - 4x^10 - 7x^9 + 10x^8 + "
          "87x^7 - 88x^6 - 9x^5 + 2x^4 + 30x^3 - 24x^2 - 296x]");

   p1 = t;

   t = p2;
   p2 -= p1;

   assert(p2.toString() ==
          "[2x^16 - 2x^15 + 4x^14 - 600x^13 + 3x^11 + 4x^10 + 7x^9 - 10x^8 - "
          "87x^7 + 88x^6 + 9x^5 - 2x^4 - 30x^3 + 24x^2 + 296x]");
   p2 = t;

   ////////////////////////////////////////////////
   /////       * OF POLYNOMIALS              /////
   //////////////////////////////////////////////
   res = p1 * p2;

   assert(res.toString() ==
          "[-6x^27 - 2x^26 - 18x^25 + 1798x^24 + 2352x^23 + 4026x^22 + 136x^21 "
          "+ 5630x^20 + 58200x^19 + 5671x^18 - 49x^17 - 593x^16 + 15169x^15 + "
          "182029x^14 + 9720x^13 + 1959x^12 + 108x^11 + 471x^10 + 8259x^9 + "
          "29917x^8 + 3109x^7 + 9x^6 + 1320x^5 + 8169x^4 + 1008x^3 + 1200x^2]");

   res = p2 * p1;

   assert(res.toString() ==
          "[-6x^27 - 2x^26 - 18x^25 + 1798x^24 + 2352x^23 + 4026x^22 + 136x^21 "
          "+ 5630x^20 + 58200x^19 + 5671x^18 - 49x^17 - 593x^16 + 15169x^15 + "
          "182029x^14 + 9720x^13 + 1959x^12 + 108x^11 + 471x^10 + 8259x^9 + "
          "29917x^8 + 3109x^7 + 9x^6 + 1320x^5 + 8169x^4 + 1008x^3 + 1200x^2]");

   ////////////////////////////////////////////////
   /////       *= OF POLYNOMIALS             /////
   //////////////////////////////////////////////
   t = p1;
   p1 *= p2;

   assert(p1.toString() ==
          "[-6x^27 - 2x^26 - 18x^25 + 1798x^24 + 2352x^23 + 4026x^22 + 136x^21 "
          "+ 5630x^20 + 58200x^19 + 5671x^18 - 49x^17 - 593x^16 + 15169x^15 + "
          "182029x^14 + 9720x^13 + 1959x^12 + 108x^11 + 471x^10 + 8259x^9 + "
          "29917x^8 + 3109x^7 + 9x^6 + 1320x^5 + 8169x^4 + 1008x^3 + 1200x^2]");

   p1 = t;

   t = p2;
   p2 *= p1;

   assert(p2.toString() ==
          "[-6x^27 - 2x^26 - 18x^25 + 1798x^24 + 2352x^23 + 4026x^22 + 136x^21 "
          "+ 5630x^20 + 58200x^19 + 5671x^18 - 49x^17 - 593x^16 + 15169x^15 + "
          "182029x^14 + 9720x^13 + 1959x^12 + 108x^11 + 471x^10 + 8259x^9 + "
          "29917x^8 + 3109x^7 + 9x^6 + 1320x^5 + 8169x^4 + 1008x^3 + 1200x^2]");

   p2 = t;

   cout << "Passed all arithmetic tests" << endl;
   cout << "Tested: +, +=, -, -=, *, *=\n" << endl;
}

void equalityTests(Polynomial& p3, Polynomial& p4, Polynomial& p5,
                   Polynomial& p6) {
   cout << p3 << endl;
   cout << p4 << endl;
   cout << p5 << endl;
   cout << p6 << endl;
   cout << "doing equality tests on the above polynomials" << endl;
   cout << endl;

   /** == */
   assert(p3 == p4);
   assert(p4 == p3);

   assert(!(p3 == p5));
   assert(!(p5 == p3));

   assert(!(p4 == p5));
   assert(!(p5 == p4));

   /** != */
   assert(p3 != p5);
   assert(p5 != p3);

   assert(p4 != p5);
   assert(p5 != p4);

   assert(!(p3 != p4));
   assert(!(p4 != p3));

   /** > */
   assert(!(p3 > p4));
   assert(!(p4 > p3));

   assert(p5 > p3);
   assert(p5 > p4);
   assert(p6 > p5);

   /** >= */
   assert((p3 >= p4));
   assert((p4 >= p3));

   assert(p5 >= p3);
   assert(p5 >= p4);
   assert(p6 >= p5);

   /** < */
   assert(!(p3 < p4));
   assert(!(p4 < p3));

   assert(!(p5 < p3));
   assert(!(p5 < p4));

   assert((p3 < p5));
   assert((p4 < p5));

   assert(p5 < p6);

   /** <= */
   assert((p3 <= p4));
   assert((p4 <= p3));

   assert(!(p5 <= p3));
   assert(!(p5 <= p4));

   assert((p3 <= p5));
   assert((p4 <= p5));

   assert(p5 <= p6);

   cout << "Passed all equality tests" << endl;
   cout << "Tested: >, >=, <, <=, ==, !=" << endl;
}