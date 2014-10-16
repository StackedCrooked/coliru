#include <iostream>
#include <string>
#include <vector>

struct Explicit
{
    Explicit(){}
    explicit Explicit(const Explicit&){}
};



int main()
{
   std::cout << "name is the same " << std::endl;
}
