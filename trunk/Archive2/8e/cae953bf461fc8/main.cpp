//#include "Rational.H"
#include <iostream>
using namespace std;
struct Rational {
    Rational();
    Rational(int numerator, int denominator);
    Rational(const Rational &r);
    const Rational& operator = (const Rational &rhs);
    int numerator(int a) const;
    int denominator(int b) const;
    void reduce();
private:
    int myNumerator;
    int myDenominator;
};
Rational operator + (const Rational &lhs, const Rational &rhs);
Rational operator - (const Rational &lhs, const Rational &rhs);
Rational operator * (const Rational &lhs, const Rational &rhs);
Rational operator / (const Rational &lhs, const Rational &rhs);
ostream& operator << (ostream & os, const Rational &r);
istream& operator >> (istream &is, Rational &r);

//#include "GCD.h"
int GCD(int numerator, int denominator) {return numerator;}

//cppfile
#include <iostream>
#include <string>

#include <assert.h>

using namespace std;

Rational:: Rational()
{
    myNumerator = 1;
    myDenominator = 1;
}

Rational:: Rational(int numerator, int denominator)
{
    assert(denominator != 0);
    myNumerator = numerator;
    myDenominator = denominator;
    reduce();
}

Rational:: Rational(const Rational &r)
{
    myNumerator = r.myNumerator;
    myDenominator = r.myDenominator;
}
const Rational& Rational :: operator = (const Rational &rhs)
{
    if (this != &rhs)
    {
        myNumerator = rhs.myNumerator;
        myDenominator = rhs.myDenominator;
        return rhs;
    }
}

int Rational:: numerator(int a) const
{
    myNumerator = a;
    return myNumerator;
}
int Rational:: denominator(int b) const
{
    myNumerator = b;
    return myDenominator;
}
void Rational:: reduce()
{

    int commonDivisor = GCD(myNumerator, myDenominator);
    myNumerator = myNumerator / commonDivisor;
    myDenominator = myDenominator / commonDivisor;
}

Rational operator + (const Rational &lhs, const Rational &rhs)
{
    int numerator = lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator();
    int denominator = lhs.denominator() * rhs.denominator();
    Rational sum(numerator, denominator);
    return sum;
}

Rational operator - (const Rational &lhs, const Rational &rhs)
{
    int numerator = lhs.numerator() * rhs.denominator() + rhs.numerator() * lhs.denominator();
    int denominator = lhs.denominator() * rhs.denominator();
    Rational difference(numerator, denominator);
    return difference;
}
Rational operator * (const Rational &lhs, const Rational &rhs)
{
    int numerator = lhs.numerator() * rhs.numerator();
    int denominator = lhs.denominator() * rhs.denominator();
    Rational product(numerator, denominator);
    return product;
}
Rational operator / (const Rational &lhs, const Rational &rhs)
{
    int numerator = lhs.numerator() * rhs.denominator();
    int denominator = lhs.denominator() * rhs.numerator();
    Rational product(numerator, denominator);
    return product;
}


ostream& operator << (ostream & os, const Rational &r)
{
    os << r.numerator() << "/" << r.denominator();
    return os;
}

istream& operator >> (istream &is, Rational &r)
{
    char divisionSymbol;
    int numerator = 0, denominator = 0;

    is >> numerator >> divisionSymbol >> denominator;
    assert(divisionSymbol == '/');
    assert(denominator != 0);
    Rational number(numerator, denominator);
    r = number;
    return is;
}

    #include <iostream>
#include "Rational.h"

using namespace std;

int main()
{
    Rational first(), second(75, 350), third(13, 55);
    Rational fourth(second);
    cout << first << endl << second << endl << third << endl << fourth <<endl;

    first.numerator(3)const;
    first.denominator(5)const;

    cout << first;
}