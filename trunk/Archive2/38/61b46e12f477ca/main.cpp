#ifndef FRACTIONTYPE_H_INCLUDED
#define FRACTIONTYPE_H_INCLUDED
#include <iostream>
using namespace std;

class fractionType
{
    friend ostream& operator << (ostream&, const fractionType&);
    friend istream& operator >> (istream&, fractionType&);

    public:
    //overloading operators
    const fractionType& operator=(const fractionType&);

    //constructors
    fractionType();
    fractionType(const fractionType&);
    fractionType(const int&, const int&);

    //destructor
    ~fractionType();

    bool operator == (const fractionType&) const;
    bool operator != (const fractionType&) const;
    bool operator <= (const fractionType&) const;
    bool operator < (const fractionType&) const;
    bool operator >= (const fractionType&) const;
    bool operator > (const fractionType&) const;

    fractionType operator +(const fractionType&);
    fractionType operator -(const fractionType&);
    fractionType operator *(const fractionType&);
    fractionType operator /(const fractionType&);

private:
    int a;
    int b;
};

#endif // FRACTIONTYPE_H_INCLUDED

#include <iostream>
#include <iomanip>
//#include "fractionType.h"
using namespace std;

//constructors
fractionType::fractionType(const int& nu, const int& de)
{
    a = nu;
    if (de==0)
    {
        cout <<"\n\tInvalid denominator."
             <<"default value considered for denominator.";
        b = 1;
    }
    else
        b = de;
}
//default Constructor
fractionType::fractionType()
{
    a = 0;
    b = 1;
}
//copy Constructor
fractionType::fractionType(const fractionType& rightFraction)
{
    a = rightFraction.a;
    b = rightFraction.b;
}
//destructor
fractionType::~fractionType()
{
}
//overloading relational operators
bool fractionType::operator == (const fractionType& rightFraction) const
{
    return (( a == rightFraction.a)&& (b == rightFraction.b));
}

bool fractionType::operator != (const fractionType& rightFraction) const
{
    return (( a != rightFraction.a)|| (b != rightFraction.b));
}

bool fractionType::operator < (const fractionType& rightFraction) const
{
    return (a * rightFraction.b < b * rightFraction.a);
}

bool fractionType::operator <= (const fractionType& rightFraction) const
{
    return ( a * rightFraction.b <= b* rightFraction.a);
}

bool fractionType::operator > (const fractionType& rightFraction) const
{
    return ( a * rightFraction.b > b* rightFraction.a);
}

bool fractionType::operator >= (const fractionType& rightFraction) const
{
    return ( a * rightFraction.b >= b* rightFraction.a);
}

bool fractionType fractionType::operator + (const fractionType& rightFraction);
{
    fractionType temp;

    temp.a = (a* rightFraction.b)+(b* rightFraction.a)
    temp.b = b * rightFraction.b;
    return temp;
}

bool fractionType fractionType::operator - (const fractionType& rightFraction);
{
    fractionType temp;

    temp.a = (a* rightFraction.b)-(b* rightFraction.a)
    temp.b = b * rightFraction.b;
    return temp;
}

bool fractionType fractionType::operator * (const fractionType& rightFraction);
{
    fractionType temp;

    temp.a = a * rightFraction.a;
    temp.b = b * rightFraction.b;
    return temp;
}

bool fractionType fractionType::operator / (const fractionType& rightFraction);
{
    fractionType temp;
    //Checking to see if division is legal
    if ((rightFraction.a == 0)|| (rightFraction.b==0))
    {
        temp.a=0;
        temp.b=1;
        cout << "\n|tInvalid to perform division.";
    }
    else
    {
        temp.a = a * rightFraction.b;
        temp.b = b * rightFractin.a;
    }
    return temp;
}

ostream& operator << (ostream& osObject, const fractionType& myFraction)
{
    osObject << myFraction.a << "/" << myFraction.b;
    return osObject;
}

istream& operator >> (istream& isObject, const fractionType& myFraction)
{
    char ch;
    isObject >> myFraction.a >> ch >> myFraction.b;
    return isObject;
}

#include <iostream>
#include <iomanip>
//#include "fractionType.h"
using namespace std;

int main()
{
    fractionType num1(5, 6);
    fractionType num2();
    fractionType num3();

    cout << fixed;
    cout << showpoint;
    cout << setprecision(2);

    cout << "Line 7: Num1 = " << num1 << endl;
    cout << "Line 8: Num2 = " << num2 << endl;

    cout << "Line 9: Enter the fraction "
         << "in the form a / b:   ";
    cin >> num2;
    cout << endl;

    cout << "Line 12: New value of num2 = "
         << num2 << endl;

    num3 = num1 + num2;

    cout << "Line 14: Num3 = " << num3 << endl;
    cout << "Line 15: " << num1 << " + " << num2
         << " = " << num1 + num2 << endl;
    cout << "Line 16: " << num1 << " * " << num2
         << " = " << num1 * num2 << endl;

    num3 = num1 - num2;

    cout << "Line 18: Num3 = " << num3 << endl;
    cout << "Line 19: " << num1 << " - " << num2
         << " = " << num1 - num2 << endl;
    cout << "Line 20: (" << num1 << ") / (" << num2
         << ") = " << num1 / num2 << endl;

    return 0;
}