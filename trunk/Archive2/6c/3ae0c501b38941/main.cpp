#include <algorithm>

#if 1
    //////////////////////////////////////////////////
    // now, let's poison `std` (illformed program)
    namespace std {
        int min(int const& a, int const& b) { 
            return a < b ? a : b; 
        }
    }
    //
    //////////////////////////////////////////////////
#endif

int foo()
{
    int a=3, b=2;
    int const& c = std::min(a,b);

    b = 42;
    return c; // returns 42 for stdlib, 2 if "poisoned"
}


#include <iostream>

int main()
{
    std::cout << "foo(): " << foo() << "\n";
}
