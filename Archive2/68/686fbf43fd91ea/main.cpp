#include <iostream>

using namespace std;

class Complex 
{
private: 
    double real;
    double imaginary;
public:
    Complex(double r = 0, double i = 0);
    Complex& operator+=(Complex const&);
    friend Complex operator+(Complex, Complex const&);
    friend ostream& operator<<(ostream& out, Complex const& number);
};

Complex::Complex(double r, double i)
    : real(r)
    , imaginary(i)
{ }

Complex& Complex::operator+=(Complex const& rhs)
{
    real += rhs.real;
    imaginary += rhs.imaginary;
    return *this;
}

Complex operator+(Complex c1, Complex const& c2) 
{
    return c1 += c2;
}

ostream& operator<<(ostream& out, Complex const& number)
{
    return out << number.real << "+" << number.imaginary << endl;
}

int main() {
    Complex y(2, 4), z(3, 0);;
    Complex sum;

    cout << "y is: " << y << endl;
    cout << "z is: " << z << endl;

    sum = y+z;

    cout << "The sum (y+z) is: " << sum << endl;
}