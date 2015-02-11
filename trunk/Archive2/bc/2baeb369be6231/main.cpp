#include <iostream>
using namespace std;
 
class complex {
    double re, im;
public:
    complex(double r, double i) : re{ r }, im{ i } {}
    complex& operator+=(const complex& other) { re += other.re; im += other.im; return *this; }
};
 
inline complex operator+(complex lhs, const complex& rhs)
{
    lhs += rhs;
    return lhs;
}
 
int main()
{
    complex a{ 1, 1 };
    complex b{ 2, -3 };
    a += {1, 3};
    a = b + (complex){1, 2};
}