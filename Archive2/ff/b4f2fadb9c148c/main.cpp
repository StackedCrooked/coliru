#include <iostream>
int main()
{
    int n = 1;
    int n2 = ++n;
    int n3 = ++ ++ ++n;
    int n4 = n++;
//    int n5 = n++ ++; // compile error
//    int n5 = n + ++n; // undefined behavior
    std::cout << "n = " << n << '\n'
              << "n2 = " << n2 << '\n'
              << "n3 = " << n3 << '\n'
              << "n4 = " << n4 << '\n';
}