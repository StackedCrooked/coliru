#include <iostream>

struct A;   // Forward declaration of A.

class A   // Define A.
{
public:
   int i;
};

int main()
{
    A a;
    std::cout<< "Hi";
}
