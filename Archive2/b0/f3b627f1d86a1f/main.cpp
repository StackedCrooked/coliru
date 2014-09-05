#include <iostream>

struct A
{
   A();
   A(int first, int second) { std::cout << "works fine?\n"; }
};
int main()
{
   new A[1] {{1, 2}};
}