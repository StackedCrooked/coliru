#include <iostream>
 
class Fraction
{
   
    int n, d;
 public:
    Fraction(int n, int d) 
    {
        this->n = n;
        this->d = 5;
    }
    int operator*(const Fraction rhs);  
};


int Fraction::operator*(const Fraction rhs)
{
    return this->n * rhs.n;
}
 
int main()
{
   Fraction f1(3,8), f2(5,2), f3(10,2);
   std::cout<<"The result is: "<<f1*f3<<"\n";
}