#include <iostream>

using namespace std;

class Complex 
{
private: 
    double real;
    double imaginary;
public:
    Complex(double r = 0, double i = 0);
    
    friend Complex operator+(Complex const&, Complex const&);
    friend ostream& operator<<(ostream& out, Complex const& number);
};

Complex::Complex(double r, double i)
    : real(r)
    , imaginary(i)
{ }

Complex operator+(Complex const& lhs, Complex const& rhs)
{
    Complex temp;
    temp.real = lhs.real + rhs.real;
    temp.imaginary = lhs.imaginary + rhs.imaginary;
    return temp;
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