#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

using namespace std;

class Polynomial {
   friend ostream& operator<<(ostream& out, const Polynomial& other);
   friend istream& operator>>(istream& in, Polynomial& other);

 private:
   std::vector<double> coeffs;  // coefficients of the polynomial

   int getPower(int size, int index) const;

   bool isEmpty() const;

   int getLead() const;

   vector<double>& removeZeroes(vector<double>& v);

   int getElementAt(int index) const;

   void inverse(vector<double>& v) const;

   void iterateAddSub(int size, const Polynomial& b, std::vector<double>& added,
                      bool add) const;

   Polynomial addSub(const Polynomial& other, bool add) const;

   bool isEqual(const Polynomial& other) const;

   vector<double> getVector() const;

   vector<double> merge(const vector<double>& p, vector<double>& added) const;

 public:
   // constructor that takes a vector of coefficients
   explicit Polynomial(const std::vector<double>& c);

   Polynomial();

   int getDegree() const;

   ~Polynomial();

   // addition operator
   Polynomial operator+(const Polynomial& other) const;

   Polynomial& operator+=(const Polynomial& other);

   // subtraction operator
   Polynomial operator-(const Polynomial& other) const;

   Polynomial& operator-=(const Polynomial& other);

   // multiplication operator
   Polynomial operator*(const Polynomial& other) const;

   Polynomial& operator*=(const Polynomial& other);

   // check equality
   bool operator==(const Polynomial& other) const;

   // check if not equal
   bool operator!=(const Polynomial& other) const;

   bool operator<(const Polynomial& other) const;

   bool operator<=(const Polynomial& other) const;

   bool operator>(const Polynomial& other) const;

   bool operator>=(const Polynomial& other) const;

   string toString(Polynomial& other) const;

   // gets size of the polynomial
   int getSize() const;

   // print function
};

#endif