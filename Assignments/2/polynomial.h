#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <iostream>
#include <vector>

using namespace std;

/**
 * Header file for the Polynomial class
 * Contains methods to add, subtract, and multiply polynomials.
 * Can also take in a polynomial given a string, as well as output it.
 */
class Polynomial {
   /**
    * << operator overload
    */
   friend ostream& operator<<(ostream& out, const Polynomial& other);

   /**
    * >> operator overload, takes a string form polynomial
    * where the left most number is the highest power
    */
   friend istream& operator>>(istream& in, Polynomial& other);

 private:
   /**
    * coefficients of the polynomial
    */
   vector<double> coeffs;

   /**
    * returns the power of an element given the vector size and ele index
    */
   int getPower(int size, int index) const;

   /**
    * deletes the useless zeroes
    */
   vector<double>& removeZeroes(vector<double>& v);

   /**
    * returns element at a position
    */
   int getElementAt(int index) const;

   /**
    * inverses all elements in a vector
    */
   void inverse(vector<double>& v) const;

   /**
    * adds/subtracts the like terms
    */
   void iterateAddSub(int size, const Polynomial& b, vector<double>& added,
                      bool add) const;

   /**
    * method for adding and subtracting
    */
   Polynomial addSub(const Polynomial& other, bool add) const;

   /**
    * returns vector of coefficients of the polynomial
    */
   vector<double> getVector() const;

   /**
    * merges unlike terms with added/substrated like terms from iterateAddSub
    */
   vector<double> merge(const vector<double>& p,
                        vector<double>& processed) const;

 public:
   /**
    * constructor that takes a vector of coefficients
    */
   explicit Polynomial(const vector<double>& c);

   /**
    * Default constructor
    *
    */
   Polynomial();

   /**
    * Gets the degree of the polynomial
    */
   int getDegree() const;

   /**
    * Destructor
    */
   ~Polynomial();

   /**
    * addition
    */
   Polynomial operator+(const Polynomial& other) const;

   /**
    * addition assignment operator
    */
   Polynomial& operator+=(const Polynomial& other);

   /**
    * subtraction operator
    */
   Polynomial operator-(const Polynomial& other) const;

   /**
    * subtraction assignment operator
    */
   Polynomial& operator-=(const Polynomial& other);

   /**
    * multiplication operator
    */
   Polynomial operator*(const Polynomial& other) const;

   /**
    * multiplication assignment operator
    */
   Polynomial& operator*=(const Polynomial& other);

   /**
    * Check if equal
    */
   bool operator==(const Polynomial& other) const;

   /**
    * Check if not equal
    */
   bool operator!=(const Polynomial& other) const;

   /**
    * Check if less than
    */
   bool operator<(const Polynomial& other) const;

   /**
    * Check if less than or equal
    */
   bool operator<=(const Polynomial& other) const;

   /**
    * Check if greater than
    */
   bool operator>(const Polynomial& other) const;

   /**
    * Check if greater than or equal
    */
   bool operator>=(const Polynomial& other) const;

   /**
    * Gets a string representation of the polynomial
    */
   string toString() const;

   /**
    * Gets the length of the polynomial
    */
   int getSize() const;
};

#endif