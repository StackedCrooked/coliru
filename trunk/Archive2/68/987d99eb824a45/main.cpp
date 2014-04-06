#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Rational
{
public:
    explicit Rational(int = 0, int = 1);
    double getRationalAsDouble() const;
private:
    int numerator;
    int denominator;
};

Rational::Rational(int numerator, int denominator)
{
    if (denominator == 0)
        this->denominator = 1;
    else
        this->denominator = denominator;
    this->numerator = numerator;
}

// *******  Problem Function *********
double Rational::getRationalAsDouble() const
{
    double a = 0.0, b = 0.0;
    a = static_cast<double>(numerator);
    b = static_cast<double>(denominator);
    cout << endl << "a = " << a;
    cout << endl << "b = " << b;
    cout << endl << "a/b = " << (a/b);
}
// ******** End Problem Function ********

int main()
{

    { //Create a new Scope so that I can view Destructor Message, not used here

        Rational c(2, 6);
        int data = 10;

        cout << c.getRationalAsDouble(); // prints rational object c as double, but not really
        cout << "\n\n";
    } // End of Scope
    return 0;
} // end main