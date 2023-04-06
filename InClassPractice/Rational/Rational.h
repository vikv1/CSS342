#include <iostream>


class Rational {

  public:
    Rational();
    Rational(int numerator = 1, int denominator = 1);
    ~Rational();

    friend std::ostream& operator<<(std::ostream& os, const Rational& rational);


    int getNumerator() const;
    int getDenominator() const;
    bool setValue(int numerator, int denominator);

    Rational operator==(const Rational& rational) const;
    Rational operator+(const Rational& rational) const;
    Rational operator-(const Rational& rational) const;
    Rational operator*(const Rational& rational) const;
    Rational operator/(const Rational& rational) const;


   


};
