#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

using namespace std;

class Polynomial {
   friend ostream& operator<<(ostream& out, const Polynomial& other);

 private:
   std::vector<double> coeffs;  // coefficients of the polynomial

   int getPower(int size, int index) const;

   int getElementAt(int index) const;

   void iterateAddSub(int size, const Polynomial& b, std::vector<double>& added, bool add) const;

   Polynomial startAddSub(const Polynomial& other, bool add) const;

   vector<double> getVector() const;

   vector<double> merge(const vector<double>& p, vector<double>& added) const;


 public:
   // constructor that takes a vector of coefficients
   Polynomial(const std::vector<double>& c);

   ~Polynomial();

   // addition operator
   Polynomial operator+(const Polynomial& other) const;

   // subtraction operator
   Polynomial operator-(const Polynomial& other) const;

   // multiplication operator
   Polynomial operator*(const Polynomial& other) const;

   // check equality
   bool operator==(const Polynomial& other) const;

   // check if not equal
   bool operator!=(const Polynomial& other) const;

   // gets size of the polynomial
   int getSize() const;

   // print function
};

#endif