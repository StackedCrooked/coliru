#include <iostream>
#include <vector>


// Trying out template varargs.
template<typename T, T... args>
struct Test
{
    // Using constexpr
    // I had assumed that with this I did not need to
    // explicitly create an object `values`
    // that the compiler will work this out at compile time.
    static constexpr T              values[] = {args...};
};

// Explicitly instantiate
// the template to force it to generate the appropriate code. 
template struct Test<int, 1, 2, 3>;


typedef Test<int, 1, 2, 3>  TestInt;

int main()
{
    // Silly test to see if it worked.
    std::cout << TestInt::values[0] << "\n";
}