#ifndef FRACTION_H
#define FRACTION_H
#include <iostream>
#include <string>
#include <stdexcept>
#include <limits>

class Fraction {

    private:
        int numer;
        int denom;
        // static int gcd(int, int);
    public:
        void reduce();
        int getNum() const;
        int getDen() const;
        Fraction(int num = 0, int den = 1);
        Fraction(std::string const& s);  // take string parameter of the form of "numerator/defnominator
        Fraction(Fraction const& other);  // copy constructor
        Fraction& operator=(Fraction const& rhs);
        // overloading arithematic operation
        Fraction  operator+  (Fraction const& rhs) const;
        Fraction  operator-  (Fraction const& rhs) const;
        Fraction  operator*  (Fraction const& rhs) const;
        Fraction  operator/  (Fraction const& rhs) const;
        bool      operator>  (Fraction const& rhs) const;
        bool      operator>= (Fraction const& rhs) const;
        bool      operator== (Fraction const& rhs) const;
        bool      operator<  (Fraction const& rhs) const;
        bool      operator<= (Fraction const& rhs) const;
        bool      operator!= (Fraction const& rhs) const;
        Fraction& operator++ ();
        Fraction& operator-- ();
        Fraction  operator++ (int);
        Fraction  operator-- (int);

        Fraction& operator+=(Fraction const& rhs);
        Fraction& operator-=(Fraction const& rhs);
        Fraction& operator*=(Fraction const& rhs);
        Fraction& operator/=(Fraction const& rhs);

        // Exponentiation
        Fraction operator^(unsigned n) const;
        Fraction& operator^=(unsigned n);

        bool isZero()     const;
        bool isProper()   const; // a fracton is proper if abs(numerator) < (denominator)
        bool isNegative() const;
        bool isPositive() const;

        operator std::string() const;
        operator double() const;

        std::string toString() const;
        std::string toProperString() const; // properString format of 15/4   is  3 3/4

        friend std::ostream& operator<< (std::ostream& out, Fraction const& rhs);
        friend std::istream& operator>> (std::istream& in, Fraction& rhs);
};

#endif

// for the Fraction.cpp file:

#include <iostream>
#include<cmath>
#include <cassert>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <sstream>

int Fraction::getNum() const
{
    return numer;
}

int Fraction::getDen() const
{
    return denom;
}

static int gcd(int n, int d)      //moving sign to numerator
{
    if(n<0)
        n=-n;
    if(d<0)
        d=-d;
    if(n<d)
        return gcd(d,n);
    if(d==0)
        return n;
    return gcd(d,n%d);
}

Fraction::Fraction(int numerator, int den) : numer(numerator), denom(den)
{
    assert(denom != 0);
    reduce();
}

void Fraction::reduce()
{
    int sign = 1;
    if (numer < 0)
    {
        sign = -1;
        numer = -numer;
    }
    if (numer< 0)
    {
        sign = -1;
        denom = -denom;
    }
    assert(denom != 0);
    int d = 1;
    if (numer>0)
    {
        d     = gcd(numer, denom);
        numer = sign*(numer / d);
        denom = denom / d;
    }
}

Fraction::Fraction(std::string const& s)
    : Fraction()
{
    std::istringstream iss(s);

    char delimiter = 0;

    if (
            (iss >> numer)
         && (iss >> delimiter)
         && (delimiter == '/')
         && (iss >> denom))
    {
        assert(denom != 0);
        reduce();
    } else
    {
        throw std::runtime_error("invalid conversion to Fraction");
    }
}

Fraction::Fraction(Fraction const& other)
    : numer(other.numer), denom(other.denom)
{
}

Fraction& Fraction::operator=(Fraction const& rhs)
{
    if (this != &rhs)
    {
        numer = rhs.numer;
        denom = rhs.denom;
    }
    return *this;
}

Fraction Fraction::operator+ (Fraction const& rhs) const
{
    return Fraction(numer*rhs.denom + denom*rhs.numer, denom*rhs.denom);
}

Fraction Fraction::operator- (Fraction const& rhs) const
{
    return Fraction(numer*rhs.denom - denom*rhs.numer, denom*rhs.denom);
}

Fraction Fraction::operator*(Fraction const& rhs) const
{
    return Fraction(numer*rhs.numer, denom*rhs.denom);
}

Fraction Fraction::operator/(Fraction const& rhs) const
{
    return Fraction(numer*rhs.denom, denom*rhs.numer);
}

bool Fraction::operator > (Fraction const& rhs) const
{
    return static_cast<double>(*this) > rhs;
}

bool Fraction::operator >= (Fraction const& rhs) const
{
    return (*this == rhs) || static_cast<double>(*this) >= rhs;
}

bool Fraction::operator == (Fraction const& rhs) const
{
    return (1l*numer*rhs.denom == 1l*denom*rhs.numer);
}

bool Fraction::operator < (Fraction const& rhs) const
{
    return static_cast<double>(*this) < rhs;
}

bool Fraction::operator <= (Fraction const& rhs) const
{
    return (*this == rhs) || static_cast<double>(*this) < rhs;
}

bool Fraction::operator!=(Fraction const& rhs) const
{
    return !(*this == rhs);
}

Fraction& Fraction::operator++()  //pre fix
{
    numer += denom;
    reduce();
    return *this;
}

Fraction Fraction::operator++(int) //post fix
{
    Fraction temp = *this;
    numer += denom;
    reduce();
    return temp;
}

Fraction& Fraction::operator--()
{
    numer -= denom;
    reduce();
    return *this;
}

Fraction Fraction::operator--(int)
{
    Fraction temp = *this;
    numer -= denom;
    reduce();
    return temp;
}

Fraction& Fraction::operator+=(Fraction const& rhs)
{
    return *this = (*this + rhs);
}

Fraction& Fraction::operator-=(Fraction const& rhs)
{
    return *this = (*this - rhs);
}

Fraction& Fraction::operator*=(Fraction const& rhs)
{
    return *this = (*this * rhs);
}

Fraction& Fraction::operator/=(Fraction const& rhs)
{
    return *this = (*this / rhs);
}

// utility
template <typename T>
T int_pow(T x, unsigned exponent)
{
    static_assert(std::is_integral<T>(), "only supports integral types");

    intmax_t base = x, result = 1;

    while (exponent != 0)
    {
        // TODO protect against overflows
        if (exponent % 2)
            result *= base;

        exponent /= 2;
        base *= base;
    }

    assert(result <= std::numeric_limits<T>::max()); // value too large to be represented
    assert(result >= std::numeric_limits<T>::min()); // value too small to be represented
    return static_cast<T>(result);
}

Fraction Fraction::operator^(unsigned n) const
{
    return Fraction(int_pow(numer, n), int_pow(denom, n));
}

Fraction& Fraction::operator^=(unsigned n)
{
    return *this = (*this ^ n);
}

bool Fraction::isZero() const
{
    return numer == 0;
}

bool Fraction::isProper() const
{
    return abs(numer)<abs(denom);
}

bool Fraction::isNegative() const
{
    return numer<0;
}

bool Fraction::isPositive() const
{
    return numer>0;
}

Fraction::operator std::string() const
{
    return toString();
}

Fraction::operator double() const
{
    return (static_cast<double>(numer) / denom);
}

std::string Fraction::toString() const
{
    return std::to_string(numer) + '/' + std::to_string(denom);
}

std::string Fraction::toProperString() const
{
    int a   = numer / denom;
    int num = numer % denom;

    std::ostringstream ostr;
    ostr << a << " " << Fraction(num, denom);
    return ostr.str();
}

std::ostream& operator <<  (std::ostream& out, Fraction const& rhs)
{
    if(rhs.denom!=1)
        return out << rhs.getNum() << "/" << rhs.denom;
    else
        return out << rhs.getNum();
}

std::istream& operator >> (std::istream& in, Fraction& rhs)
{
    int n, d = 1;
    char c;

    if (in >> n >> c)
    {
        if (c == '/')
        {
            in >> d;
        }
        else
        {
            in.putback(c);
        }
        rhs = Fraction(n, d);
    }
    return in;
}

// And here's the main program

int main()
{
    Fraction a1;
    Fraction a(1,2);
    Fraction b(4,5);
    Fraction c(6,8);
    Fraction d(b);
    Fraction g(-4,8);
    Fraction g1(4,-10);
    Fraction z(7,5);

    std::cout << "a1: " << a1 << "\n";
    std::cout << "a : " << a  << "\n";
    std::cout << "b : " << b  << "\n";
    std::cout << "c : " << c  << "\n";
    std::cout << "d : " << d  << "\n";
    std::cout << "g : " << g  << "\n";
    std::cout << "g1: " << g1 << "\n";

    std::string s  = "3/4";
    std::string s1 = "2/-3";
    Fraction b1(s);
    Fraction b2(s1);

    std::cout << "b1: " << b1 << "\n";
    std::cout << "b2: " << b2 << "\n";

    a1 = b + c; std::cout << "a1 = b + c; // " << a1 << "\n";
    a1 = b-c  ; std::cout << "a1 = b-c  ; // " << a1 << "\n";
    a1 = b*c  ; std::cout << "a1 = b*c  ; // " << a1 << "\n";
    a1 = b / c; std::cout << "a1 = b / c; // " << a1 << "\n";

    b += a;     std::cout << "b += a; // "     << b  << "\n";
    b -= a;     std::cout << "b -= a; // "     << b  << "\n";
    b /= a;     std::cout << "b /= a; // "     << b  << "\n";
    b++   ;     std::cout << "b++   ; // "     << b  << "\n";
    ++b   ;     std::cout << "++b   ; // "     << b  << "\n";
    b--   ;     std::cout << "b--   ; // "     << b  << "\n";
    --b   ;     std::cout << "--b   ; // "     << b  << "\n";
    b /= a;     std::cout << "b /= a; // "     << b  << "\n";
    b *= a;     std::cout << "b *= a; // "     << b  << "\n";
    b ^= 2u;    std::cout << "b ^= 2; // "     << b  << "\n";

    std::cout << a.toString()       << "\n";
    std::cout << z.toProperString() << "\n";

    Fraction f1(-4,5);
    Fraction f2(0,1);
    std::cout << "is f1 negative? "            << std::boolalpha << f1.isNegative() << "\n";
    std::cout << "is f2 zero? "                << std::boolalpha << f2.isZero()     << "\n";
    std::cout << "is f1 a proper fraction? "   << std::boolalpha << f1.isProper()   << "\n";
    std::cout << "is f1 a positive fraction? " << std::boolalpha << f1.isPositive() << "\n";

    a = Fraction(9, 8);
    b = Fraction(7, 8);

    if (a < b)
        std::cout << "a is smaller than b"     << "\n";
    else
        std::cout << "a is not smaller than b" << "\n";

    if(a==b)
        std::cout << "a is equal to b"         << "\n";
    else
        std::cout << "a is not equal to b"     << "\n";
}

