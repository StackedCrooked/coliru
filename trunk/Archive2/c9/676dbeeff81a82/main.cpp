#include <iostream>
 
// simple non-type template parameter
template<class T, int N = 1>
struct S {
    T a[N];
};
 
 
int a[5];
int f(int n) { return n;}
int main()
{
    S<int> s; // s.a is an array of 10 int
    s.a[9] = 4;
 
 
    std::cout << s.a[9] << '\n' << a[4] << '\n';
}