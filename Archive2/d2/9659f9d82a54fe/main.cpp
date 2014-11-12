template <typename T>
T foobar (T a, T b)
{
    auto max = [] (T a, T b) {return (a > b? a : b);};
    auto min = [] (T a, T b) {return (b < a? b : a);}; // Preserve strict ordering!

    return max(a,b)+min(a,b);
}

#include <iostream>

int main()
{
    std::cout << foobar(4, 5);
}