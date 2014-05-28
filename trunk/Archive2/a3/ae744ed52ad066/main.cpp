#include <iostream>

struct T
{
    T() = default;
    T(const T&) { std::cout << "copy ctor\n"; }
    T(T&&) { std::cout << "move ctor\n"; }
};

int main()
{
    T a;
    T b = std::move(a);   // "move ctor"
    
    const T c;
    T d = std::move(c);   // "copy ctor" - `const T&&` only matches copy ctor
    
    
    
    // (shut up GCC)
    (void) b;
    (void) d;
}
