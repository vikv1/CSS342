#include "polynomial.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

Polynomial::Polynomial(const vector<double>& coefficients) {
   coeffs = coefficients;
   removeZeroes(coeffs);
   /* Example: {0, 2, 0}
    * == 0x^2 + 2x + 0
    * which is just 2x + 0.
    *
    * Only delete leading zeroes
    * because the zeroes in between
    * and to the right of the vector
    * are used to determine the powers.
    */
}

Polynomial::Polynomial() {
   vector<double> coefficients = {0};
   coeffs = coefficients;
}

Polynomial::~Polynomial() {}

vector<double>& Polynomial::removeZeroes(vector<double>& v) {
   int index = 0;
   for (int i = 0; i < v.size(); i++) {
      if (v[i] != 0) {
         index = i;
         break;
      }
   }

   v.erase(v.begin(), v.begin() + index);

   return v;
}

int Polynomial::getPower(int size, int index) const {
   return size - index - 1;
}

int Polynomial::getDegree() const {
   return getPower(getSize(), 0);
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

void Polynomial::inverse(vector<double>& v) const {
   for (int i = 0; i < v.size(); i++) {
      v[i] = -v[i];
   }
}

bool Polynomial::isEmpty() const {
   return (getElementAt(0) == 0);
}

int Polynomial::getLead() const {
   return (getElementAt(0));
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
      vector<double> temp = getVector();
      merge(temp, result);
   } else {
      iterateAddSub(thisSize, p, result, add);
      vector<double> temp = p.getVector();
      if (!add) {
         inverse(temp);
      }
      merge(temp, result);
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
 * @param processed - The result of operating on what was possible
 * @return vector<double>
 */
vector<double> Polynomial::merge(const vector<double>& p,
                                 vector<double>& processed) const {
   // use temp because there is no push_front() for vectors
   vector<double> temp;
   int addedSize = processed.size();

   // overall size - added size gives bound of unprocessed parts of the vector
   for (int i = 0; i < (p.size() - addedSize); i++) {  // append unadded powers
      temp.push_back(p.at(i));
   }

   for (int i = 0; i < addedSize; i++) {  // append added powers
      temp.push_back(processed.at(i));
   }

   processed = temp;

   return processed;
}

Polynomial Polynomial::operator+(const Polynomial& p) const {
   return addSub(p, true);
}

Polynomial& Polynomial::operator+=(const Polynomial& other) {
   *this = *this + other;

   return *this;
}

Polynomial Polynomial::operator-(const Polynomial& p) const {
   return addSub(p, false);
}

Polynomial& Polynomial::operator-=(const Polynomial& other) {
   *this = *this - other;

   return *this;
}

Polynomial Polynomial::operator*(const Polynomial& p) const {
   Polynomial result;
   int newDegree = getDegree() + p.getDegree();
   double arr[newDegree + 1];

   // for each element, multiply by every other element in
   // other polynomial
   // is basically FOIL method but in order
   for (int i = 0; i < getSize(); i++) {
      for (int j = 0; j < p.getSize(); j++) {
         int thisPower = getPower(getSize(), i);
         int otherPower = p.getPower(p.getSize(), j);

         // powers added when multiplied
         int degree = thisPower + otherPower;

         // add onto existing element to avoid overwriting previous element
         arr[newDegree - degree] =
            arr[newDegree - degree] + (getElementAt(i) * p.getElementAt(j));
      }
   }

   vector<double> v(arr, arr + newDegree + 1);

   result = Polynomial(v);

   return result;
}

Polynomial& Polynomial::operator*=(const Polynomial& other) {
   *this = *this * other;

   return *this;
}

/**
 * Helper function for the == operator.
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
      // sizes are guaranteed to be equal if degrees are same
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

string Polynomial::toString(Polynomial& other) const {
   string s = "[";
   int size = other.getSize();

   // if polynomial degree is 0
   if (size == 1) {
      s += to_string(other.getElementAt(0)) + "]";
      return s;
   }

   for (int i = -1; i < size; i++) {
      if (i == -1) {
         if (other.getElementAt(0) < 0) {
            s += "-";
         }
         continue;
      }

      int curr = other.getElementAt(i);

      // if current element is 0 and not last
      if (curr == 0 && i != size - 1) {
         // if string already has a number in it and next isnt 0, add a + to get
         // ready for next element
         if (other.getElementAt(i + 1) != 0 && s.length() > 1) {
            if (other.getElementAt(i + 1) < 0) {
               s += " - ";
            } else {
               s += " + ";
            }
         }

         continue;
      }

      if (i == -1) {
         if (other.getElementAt(i + 1) < 0) {
            s += "-";
         }
         continue;
      }

      // using absolute values because minus signs are pre appended before
      // actually reaching the negative element

      // size - 2 because size - 1 would be x^1 which can
      // be written as x

      if (i < size - 2) {
         // if next ele is 0, dont add operator + or - yet
         if (other.getElementAt(i + 1) == 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(other.getPower(size, i));
         } else if (other.getElementAt(i + 1) < 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(other.getPower(size, i)) + " - ";
         } else {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(other.getPower(size, i)) + " + ";
         }
      } else if (i == size - 2) {
         // size - 2 is x^1

         if (other.getElementAt(i + 1) == 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x";
         } else if (other.getElementAt(i + 1) < 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x - ";
         } else {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x + ";
         }
      } else {
         // last element, x^0
         // if last is 0, just add the closing bracket
         if (curr == 0) {
            s += "]";
         } else {  // add value and closing bracket
            s += to_string(abs(curr)) + "]";
         }
      }
   }

   return s;
}

ostream& operator<<(ostream& out, const Polynomial& other) {
   string s = "[";
   int size = other.getSize();

   // if polynomial degree is 0
   if (size == 1) {
      s += to_string(other.getElementAt(0)) + "]";
      return out << s;
   }

   for (int i = -1; i < size; i++) {
      if (i == -1) {
         if (other.getElementAt(0) < 0) {
            s += "-";
         }
         continue;
      }

      int curr = other.getElementAt(i);

      // if current element is 0 and not last
      if (curr == 0 && i != size - 1) {
         // if string already has a number in it and next isnt 0, add a + to get
         // ready for next element
         if (other.getElementAt(i + 1) != 0 && s.length() > 1) {
            if (other.getElementAt(i + 1) < 0) {
               s += " - ";
            } else {
               s += " + ";
            }
         }

         continue;
      }

      if (i == -1) {
         if (other.getElementAt(i + 1) < 0) {
            s += "-";
         }
         continue;
      }

      // using absolute values because minus signs are pre appended before
      // actually reaching the negative element

      // size - 2 because size - 1 would be x^1 which can
      // be written as x

      if (i < size - 2) {
         // if next ele is 0, dont add operator + or - yet
         if (other.getElementAt(i + 1) == 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(other.getPower(size, i));
         } else if (other.getElementAt(i + 1) < 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(other.getPower(size, i)) + " - ";
         } else {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(other.getPower(size, i)) + " + ";
         }
      } else if (i == size - 2) {
         // size - 2 is x^1

         if (other.getElementAt(i + 1) == 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x";
         } else if (other.getElementAt(i + 1) < 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x - ";
         } else {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x + ";
         }
      } else {
         // last element, x^0
         // if last is 0, just add the closing bracket
         if (curr == 0) {
            s += "]";
         } else {  // add value and closing bracket
            s += to_string(abs(curr)) + "]";
         }
      }
   }

   return out << s;
}

istream& operator>>(istream& in, Polynomial& other) {
   vector<double> v;
   int input;
   while ((in >> input)) {
      v.push_back(input);
   }

   other = Polynomial(v);

   return in;
}