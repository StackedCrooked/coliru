#include <iostream>
 
struct A {
   double x;
};
const A* a = new A{0};
 
decltype( a->x ) x3;       // type of x3 is double (declared type)
decltype((a->x)) x4 = x3;  // type of x4 is const double& (lvalue expression)
 
template <class T, class U>
auto add(T t, U u) -> decltype(t + u); // return type depends on template parameters
 
int main() 
{
std::cout << "Sasai pindosy!\n";
}