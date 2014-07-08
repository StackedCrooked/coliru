#include <iostream>

int f(int ) { return 1; } // a)

template<typename T> int f(T x) { return 2; } // b)

template<typename Func, typename T> void print_result(Func f, T arg) 
{ 
   std::cout << f(arg) << std::endl; 
}

int main()
{
    print_result(f, 1);
}