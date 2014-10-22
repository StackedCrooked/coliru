#include <iostream>
#include <climits>

struct A
{
    ~A(){ std::cout << "Non-trivial" << std::endl; }
};

int main()
{
    A a;
    new (&a) A; //UB?
}
    