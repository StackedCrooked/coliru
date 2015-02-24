#include <iostream>

template<int b>
constexpr void miami()
{
    std::cout << b;
}
    struct Wrap
    {
        int value;    
    
        constexpr Wrap& operator*=(Wrap const& rhs) 
        { value *= rhs.value; return *this; }
        
        constexpr void operator()(int const l)
        {
            miami<l>();
        }
    
        friend constexpr Wrap operator * (Wrap const& lhs, Wrap const& rhs)
        { return Wrap(lhs) *= rhs; }    
    };

constexpr Wrap factorial(int n)
{
    return n? factorial(n - 1) * Wrap { n } : Wrap { 1 };    
}

// want to be able to statically initialize these arrays
struct Hold
{
    static constexpr Wrap Int[] = { factorial(0), factorial(1), factorial(2), factorial(3) };
};

int main() 
{
    std::cout << Hold::Int[3].value << "\n"; // 6
    auto w = Wrap { 2 };
    w *= Wrap { 3 };
    std::cout << w.value << "\n"; // 6
}