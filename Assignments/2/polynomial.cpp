#include "polynomial.h"

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

Polynomial::Polynomial(const vector<double>& coefficients) {
   coeffs = coefficients;
   coeffs = removeZeroes(coeffs);
}

Polynomial::~Polynomial() {}

vector<double> Polynomial::removeZeroes(vector<double>& v) {
   for(int i = 0; i < v.size(); i++) {
      if(v[i] == 0) {
         v.erase(v.begin() + i);
      }

      if(v[i] != 0) {
         break;
      }
   }

   return v;
}

int Polynomial::getPower(int size, int index) const {
   return size - index - 1;
}

int Polynomial::getDegree() const {
   for (int i = 0; i < getSize(); i++) {
      if (coeffs[i] > 0) {
         return getPower(getSize(), i);
      }
   }

   return 0;
}

int Polynomial::getSize() const {
   return coeffs.size();
}

int Polynomial::getElementAt(int index) const {
   return coeffs.at(index);
}

vector<double> Polynomial::getVector() const {
   return coeffs;
}

/**
 * Helper function to add or subtract polynomials.
 *
 *
 * Iterate backwards through both vectors until count is equal
 * to the smaller size of the two vectors.
 *
 * @param smallerSize
 * @param b
 * @param added
 * @param add - if true, add the polynomials, else subtract
 */
void Polynomial::iterateAddSub(int smallerSize, const Polynomial& b,
                               vector<double>& added, bool add) const {
   int thisSize = getSize();
   int bSize = b.getSize();

   int count = 0;
   int margin = 1;

   // iterating backwards until end of the shorter vector ensures that the
   // powers match
   while (count != smallerSize) {
      if (add) {
         added.push_back(getElementAt(thisSize - margin) +
                         b.getElementAt(bSize - margin));
      } else {
         added.push_back(getElementAt(thisSize - margin) -
                         b.getElementAt(bSize - margin));
      }

      count++;
      margin++;
   }

   reverse(added.begin(), added.end());
}

/**
 * Reusable code that adds or
 * subtracts two polynomials.
 *
 * @param p
 * @param add
 * @return Polynomial
 */
Polynomial Polynomial::addSub(const Polynomial& p, bool add) const {
   vector<double> result;
   int thisSize = getSize();
   int otherSize = p.getSize();

   if (thisSize >= otherSize) {
      iterateAddSub(otherSize, p, result, add);
      merge(getVector(), result);
   } else {
      iterateAddSub(thisSize, p, result, add);
      merge(p.getVector(), result);
   }

   return Polynomial(result);
}

/**
 * Merges two polynomials.
 *
 * Iterates through the bigger polynomial's unadded parts
 * and adds it to the temp vector.
 *
 * Then iterate through the added part and append it onto the temp vector.
 *
 * Example: merge {1, 2, 3, 4} and {1, 2} = {1, 2, 1, 2}
 * The second vector in this case is the result of adding
 * the like powers from the first vector and some other polynomial P,
 * so we just have to first append the unadded higher powers and then append the
 * added lower ones.
 *
 *
 * @param p - The bigger of the two initial polynomials
 * @param added - The result of adding what was possible
 * @return vector<double>
 */
vector<double> Polynomial::merge(const vector<double>& p,
                                 vector<double>& added) const {
   // use temp because there is no push_front() for vectors
   vector<double> temp;
   int addedSize = added.size();

   for (int i = 0; i < addedSize - 1; i++) {  // append unadded powers
      temp.push_back(p.at(i));
   }

   for (int i = 0; i < addedSize; i++) {  // append added powers
      temp.push_back(added.at(i));
   }

   added = temp;

   return added;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
   // vector<double> added;
   // int thisSize = getSize();
   // int otherSize = p.getSize();

   // if(thisSize >= otherSize) {
   //    iterateAddSub(otherSize, p, added, true);
   //    merge(getVector(), added);
   // } else {
   //    iterateAddSub(thisSize, p, added, true);
   //    merge(p.getVector(), added);
   // }

   return addSub(p, true);
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
   // vector<double> subbed;
   // int thisSize = getSize();
   // int otherSize = p.getSize();

   // if(thisSize >= otherSize) {
   //    iterateAddSub(otherSize, p, subbed, false);
   //    merge(getVector(), subbed);
   // } else {
   //    iterateAddSub(thisSize, p, subbed, false);
   //    merge(p.getVector(), subbed);
   // }

   // Polynomial(subbed);

   return addSub(p, false);
}

/**
 * Helper function for the == and != operators.
 * Returns true if the two polynomials are equal, false otherwise.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::isEqual(const Polynomial& p) const {
   int degree = getDegree();

   if (degree != p.getDegree()) {
      return false;
   } else {
      for (int i = 0; i < getSize(); i++) {
         if (getElementAt(i) != p.getElementAt(i)) {
            return false;
         }
      }
   }

   return true;
}

bool Polynomial::operator==(const Polynomial& p) const {
   return isEqual(p);
}

bool Polynomial::operator!=(const Polynomial& p) const {
   return !(*this == p);
}

bool Polynomial::operator<(const Polynomial& p) const {
   bool isLess = false;

   if (isEqual(p)) {
      return false;
   } else {
      int thisPower = getDegree();
      int otherPower = p.getDegree();

      if (thisPower != otherPower) {
         return thisPower < otherPower;
      }


      for (int i = 0; i < getSize(); i++) {
         if (getElementAt(i) < p.getElementAt(i)) {
            isLess = true;
            break;
         }
      }
   }

   return isLess;
}

bool Polynomial::operator<=(const Polynomial& p) const {
   return *this == p || *this < p;
}

bool Polynomial::operator>(const Polynomial& p) const {
   return !(*this <= p);
}

bool Polynomial::operator>=(const Polynomial& p) const {
   return !(*this < p);
}






ostream& operator<<(ostream& out, const Polynomial& other) {
   string s = "[";
   int size = other.getSize();

   for (int i = 0; i < size; i++) {
      int curr = other.getElementAt(i);

      if (i == 0 && curr == 0) {
         continue;
      }

      if (curr == 0 && i != size - 1) {
         // if string already has a number in it and next isnt 0
         if (other.getElementAt(i + 1) != 0 && s.length() > 1) {
            s += " + ";
         }

         continue;
      }
      if (i == size - 1) {
         if (curr == 0) {
            s += "]";
         } else {
            s += to_string(curr) + "]";
         }

         continue;
      }

      if (i < size - 2) {  // size - 2 because size - 1 would be x^1 which can
                           // be written as x
         if (other.getElementAt(i + 1) == 0) {
            s += to_string(curr) + "x^" + to_string(other.getPower(size, i));
         } else {
            s += to_string(curr) + "x^" + to_string(other.getPower(size, i)) +
                 " + ";
         }

      } else if (i == size - 2) {
         if (other.getElementAt(i + 1) == 0) {
            s += to_string(curr) + "x";
         } else {
            s += to_string(curr) + "x + ";
         }
      }
   }

   return out << s;
}