#include <iostream>
#include <type_traits>
 
void f(int (&&x)[2][3])
{
    std::cout << sizeof x << '\n';
}
 
struct X {
    int i[2][3];
} x;
 
template<typename T> using identity = T;
 
int main()
{
    std::cout << sizeof X().i << '\n'; // size of the array
    f(X().i); // OK, binds to rvalue
//  f(x.i);   // Error: cannot bind to lvalue
 
    f(identity<int[][3]>{{1,2,3},{4,5,6}}); // OK, binds to rvalue
}