#include "polynomial.h"

#include <algorithm>
#include <sstream>
#include <iostream>

using namespace std;

/**
 * Polynomial class implemention of the header file.
 *
 * Performs various operations on vectors in order
 * to perform arithmetic, comparisons, and input/output.
 */

/**
 * Constructor with vector of coefficients
 *
 * @param coefficients
 */

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

/**
 * Default constructor
 *
 */
Polynomial::Polynomial() {
   vector<double> coefficients = {0};
   coeffs = coefficients;
}

Polynomial::~Polynomial() {}

/**
 * Deletes leading zeroes from the vector in constructor
 *
 * @param v
 * @return vector<double>&
 */
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

/**
 * Returns the power of a number in the
 * vector representation of the polynomial.
 *
 * @param size
 * @param index
 * @return int
 */
int Polynomial::getPower(int size, int index) const {
   return size - index - 1;
}

/**
 * Returns highest power of the polynomial
 *
 * @return int
 */
int Polynomial::getDegree() const {
   return getPower(getSize(), 0);
}

/**
 * Size of underlying vector
 *
 * @return int
 */
int Polynomial::getSize() const {
   return coeffs.size();
}

/**
 * Gets an element at an index from the vector
 *
 * @param index
 * @return int
 */
int Polynomial::getElementAt(int index) const {
   return coeffs.at(index);
}

/**
 * Returns the vector.
 *
 * @return vector<double>
 */
vector<double> Polynomial::getVector() const {
   return coeffs;
}

/**
 * Inverses elements, used for subtraction
 *
 * @param v
 */
void Polynomial::inverse(vector<double>& v) const {
   for (int i = 0; i < v.size(); i++) {
      v[i] = -v[i];
   }
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

   // reverse because we were pushing_back smaller to bigger elements
   reverse(added.begin(), added.end());
}

/**
 * Adds or subtracts polynomials using the iterateAddSub method.
 *
 * Uses the merge function to merge the added/subtracted part
 * and the unadded/unsubtracted part.
 *
 * @param p
 * @param add
 * @return Polynomial
 */
Polynomial Polynomial::addSub(const Polynomial& p, bool add) const {
   vector<double> result;
   int thisSize = getSize();
   int otherSize = p.getSize();

   // use shorter of the two sizes to add/sub only common powers
   if (thisSize >= otherSize) {
      iterateAddSub(otherSize, p, result, add);
      vector<double> temp = getVector();
      merge(temp, result);
   } else {
      iterateAddSub(thisSize, p, result, add);
      vector<double> temp = p.getVector();
      if (!add) {
         // if this is smaller and we are subtracting,
         // the other polynomial will be inversed
         // e.g  1 - 2 == 1 + (-2)
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
 * The second vector in this case is the result of adding/subbing
 * the like powers from two polynomials, so we just have to first append
 * the unadded higher powers and then append the added lower ones.
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
   for (int i = 0; i < (p.size() - addedSize); i++) {  // append unprocessed
      temp.push_back(p.at(i));
   }

   for (int i = 0; i < addedSize; i++) {  // append processed
      temp.push_back(processed.at(i));
   }

   processed = temp;

   return processed;
}

/**
 * Adds two polynomials using +.
 *
 * @param p
 * @return Polynomial
 */
Polynomial Polynomial::operator+(const Polynomial& p) const {
   return addSub(p, true);
}

/**
 * Adds two polynomials using + and assigns it
 * to the left hand side.
 * p1 += 2
 * is just p1 = p1 + p2
 *
 * @param p
 * @return Polynomial
 */
Polynomial& Polynomial::operator+=(const Polynomial& other) {
   *this = *this + other;

   return *this;
}

/**
 * Subtracts two polynomials using -.
 *
 * @param p
 * @return Polynomial
 */
Polynomial Polynomial::operator-(const Polynomial& p) const {
   return addSub(p, false);
}

/**
 * Subtracts two polynomials using - and assigns it
 * to the left hand side.
 * p1 -= 2
 * is just p1 = p1 - p2
 *
 * @param p
 * @return Polynomial
 */
Polynomial& Polynomial::operator-=(const Polynomial& other) {
   *this = *this - other;

   return *this;
}

/**
 * Multiplies all terms in the left hand polynomial
 * by all terms in the right hand polynomial.
 *
 * Stores in a vector where the size is the new degree + 1.
 *
 * @param p
 * @return Polynomial
 */
Polynomial Polynomial::operator*(const Polynomial& p) const {
   Polynomial result;
   int newDegree = getDegree() + p.getDegree();
   vector<double> v(newDegree + 1);

   // for each element, multiply by every other element in
   // other polynomial
   // is basically FOIL method but left to right
   for (int i = 0; i < getSize(); i++) {
      for (int j = 0; j < p.getSize(); j++) {
         int thisPower = getPower(getSize(), i);
         int otherPower = p.getPower(p.getSize(), j);

         // powers added when multiplied
         int degree = thisPower + otherPower;

         // add onto existing element to avoid overwriting previous element
         v[newDegree - degree] += (getElementAt(i) * p.getElementAt(j));
      }
   }

   result = Polynomial(v);

   return result;
}

/**
 * Multiplies two polynomials using * and assigns it
 * to the left hand side.
 * p1 *= 2
 * is just p1 = p1 * p2
 *
 * @param p
 * @return Polynomial
 */
Polynomial& Polynomial::operator*=(const Polynomial& other) {
   *this = *this * other;

   return *this;
}

/**
 * Divides a bigger polynomial by a smaller one.
 * Returns the quotient of the two polynomials.
 * Or returns this if the divisor is bigger or 0.

 * @param other 
 * @return Polynomial 
 */
Polynomial Polynomial::operator/(const Polynomial& other) const {
   if(other > *this || other.getElementAt(0) == 0) {
      return *this;
   } else if(other == *this) {
      Polynomial r({1});
      return r;
   }

   int newDegree = getDegree() - other.getDegree();
   vector<double> v(newDegree + 1);

   
   int otherPow = other.getPower(other.getSize(), 0);

   for (int i = 0; i < getSize(); i++) {
      int thisPow = getPower(getSize(), i);
      // check if divisor leading element can go into current dividen element
      if(thisPow >= otherPow) { 
         double div = getElementAt(i) / other.getElementAt(0);
         int newPow = thisPow - otherPow;
         v[newDegree - newPow] += div;
      }
   }

   Polynomial result = Polynomial(v);

   return result;
}

/**
 * Divides two polynomials using * and assigns it
 * to the left hand side.
 * p1 /= 2
 * is just p1 = p1 / p2
 *
 * @param p
 * @return Polynomial
 */
Polynomial& Polynomial::operator/=(const Polynomial& other) {
   *this = *this / other;

   return *this;
}

/**
 * Returns true if the two polynomials are equal, false otherwise.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::operator==(const Polynomial& p) const {
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

/**
 * Returns true if the two polynomials are not equal, false otherwise.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::operator!=(const Polynomial& p) const {
   return !(*this == p);
}

/**
 * Returns true if the left hand polynomial is less than the right hand.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::operator<(const Polynomial& p) const {
   bool isLess = false;

   if (*this == p) {
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

/**
 * Returns true if the left hand polynomial
 * is less than or equal to the right hand.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::operator<=(const Polynomial& p) const {
   return *this == p || *this < p;
}

/**
 * Returns true if the left hand polynomial is greater than the right hand.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::operator>(const Polynomial& p) const {
   return !(*this <= p);
}

/**
 * Returns true if the left hand polynomial
 * is greater than or equal to the right hand.
 *
 * @param p
 * @return true
 * @return false
 */
bool Polynomial::operator>=(const Polynomial& p) const {
   return !(*this < p);
}

/**
 * Returns a string representation of the polynomial.
 *
 * @return string
 */
string Polynomial::toString() const {
   string s = "[";
   int size = getSize();

   // if polynomial degree is 0
   if (size == 1) {
      s += to_string(getElementAt(0)) + "]";
      return s;
   }

   for (int i = -1; i < size; i++) {
      // pre append negative sign if first ele is negative
      if (i == -1) {
         if (getElementAt(0) < 0) {
            s += "-";
         }
         continue;
      }

      int curr = getElementAt(i);

      // if current element is 0 and not last
      if (curr == 0 && i != size - 1) {
         // if string already has a number in it and next isnt 0, add a + to get
         // ready for next element
         if (getElementAt(i + 1) != 0 && s.length() > 1) {
            if (getElementAt(i + 1) < 0) {
               s += " - ";
            } else {
               s += " + ";
            }
         }

         continue;
      }

      if (i == -1) {
         if (getElementAt(i + 1) < 0) {
            s += "-";
         }
         continue;
      }

      // using absolute values because minus signs are pre appended before
      // actually reaching the negative element

      // size - 2 because size - 1 would be x^1 which can
      // be written as x

      // The ternary statements below say not to add a number before x
      // if its just a 1

      if (i < size - 2) {
         // if next ele is 0, dont add operator + or - yet
         if (getElementAt(i + 1) == 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(getPower(size, i));
         } else if (getElementAt(i + 1) < 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(getPower(size, i)) + " - ";
         } else {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x^" +
                 to_string(getPower(size, i)) + " + ";
         }
      } else if (i == size - 2) {
         // size - 2 is x^1

         if (getElementAt(i + 1) == 0) {
            s += ((abs(curr) == 1) ? "" : to_string(abs(curr))) + "x";
         } else if (getElementAt(i + 1) < 0) {
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

/**
 * Overloaded << operator
 * Reuses toString() function for
 * string representation
 *
 * @param out
 * @param other
 * @return ostream&
 */
ostream& operator<<(ostream& out, const Polynomial& other) {
   string s = other.toString();

   return out << s;
}

/**
 * Overloaded >> operator to take in
 * a polynomial in the form of a string
 * Left hand side should be highest power.
 * Takes in polynomials the same way as they are output
 * Input can have square brackets around it
 * Negative terms marked by - x instead of
 * + -x.
 *
 *
 * e.g: "x^3 + x^2 + x + 1"
 *
 * @param in
 * @param other
 * @return istream&
 */
istream& operator>>(istream& in, Polynomial& other) {
   vector<double> v;

   string input;
   getline(cin, input);

   istringstream s(input);

   bool firstIteration = true;
   string degree;
   bool isNegative = false;

   string temp;
   while (s >> temp) {
      // store end bracket in variable so we dont have to
      // search for it again when modifying temp
      int endBrackPos = temp.find("]");

      if (temp.find("[") != string::npos) {
         temp = temp.substr(1);
      } else if (endBrackPos != string::npos) {
         temp = temp.substr(0, endBrackPos);
      }
      // is negative will be true if previous operator was a '-'
      if (isNegative) {
         temp = "-" + temp;
         isNegative = false;
      }

      if (temp == "-") {
         isNegative = true;
      } else if (temp == "+") {
         isNegative = false;
      }

      if (temp == "-" || temp == "+") {
         continue;
         // skip iteration, cant do anything more with + and -
      }

      int expInd = temp.find("^");
      int xInd = temp.find("x");

      // separate checks at iteration 0
      // in case polynomial is one element
      // also for determining vector size
      if (firstIteration) {
         // if ^ not in string
         if (expInd == string::npos) {
            // if no x and no ^ present, then only one constant element
            if (xInd == string::npos) {
               v.push_back(stoi(temp));
               Polynomial p(v);
               other = p;
               return in;
            } else {        // if x present and not ^
               degree = 1;  // e.g.  x == x^1
            }
         } else {
            for (int i = expInd + 1; i < temp.length(); i++) {
               degree += temp[i];
            }
         }
         v.resize(stoi(degree) + 1, 0);
         firstIteration = false;
      }

      string coeff;
      string pow;
      // if x index doesnt exist, then ^ isnt there either
      // must be a constant then
      if (xInd == string::npos) {
         coeff = temp;
         pow = "0";
      } else if (xInd != string::npos) {
         for (int i = 0; i < xInd; i++) {
            coeff += temp[i];
         }
         if (expInd != string::npos) {
            for (int i = expInd + 1; i < temp.length(); i++) {
               pow += temp[i];
            }
         } else {
            // power == 1 if x is present and no ^
            pow = "1";
         }
      }

      // if the length of coeff is 0,
      // then there is an implied 1 in front of x
      // e.g.    x^2     <-   doesnt have a coefficient
      if (coeff.length() == 0) {
         coeff = "1";
      }

      int p = stoi(pow);
      int co = stoi(coeff);

      v.at(v.size() - p - 1) += co;
   }

   other = Polynomial(v);

   return in;
}
