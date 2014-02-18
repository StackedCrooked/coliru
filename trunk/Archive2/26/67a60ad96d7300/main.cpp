#include <utility>
#include <iostream>
#include <vector>

class complex {             // very simplified complex

     double re, im;

public:

     complex(double r, double i) :re{r}, im{i} { }

     complex operator+(complex);

     complex operator*(complex);

};


int main()
{
    complex a(0, 0);
    complex b(0, 0);
    
	a = {1,2};          // OK: right hand side of assignment

     //a += {1,2};         // OK: right hand side of assignment

     b = a+{1,2};        // syntax error

     b = a+complex{1,2}; // OK

     {a,b} = {b,a};      // syntax error


}