// Vikrant Verma
// Temuulen Amgalanbaatar

#include <iostream>

using namespace std;

class Square {
   friend ostream &operator<<(ostream &Out, const Square &Square) {
      return Out << Square.getLength() << endl;
   }

   public:
     explicit Square(int l = 0) {
      length = l;
     }

     ~Square() {

     }

     int getLength() const {
      return length;
     }

     void setLength(int l) {
      length = l;
     }

     Square operator+(const Square &s) const {
      Square sq(this->length + s.length);

      return sq;
     }

     Square &operator+=(const Square &s) {
      this->length = this->length + s.length;

      return *this;
     }


   private:
     int length;

};

int main() {

   Square S2(3);
   Square S3(3);

   Square S1 = S2 + S3;

   cout << S1 << endl;
   cout << (S1 + S2) << endl;

   return 0;
}