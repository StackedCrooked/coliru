#include <iostream>
#include <array>

int main()
{
    struct S { int a, b; };
    
    S c_arr[] = {{1, 2}, {3, 4}};  // OK
    std::array<S, 2> std_arr {1, 2, 3, 4};  // Error: too many initializers
}
