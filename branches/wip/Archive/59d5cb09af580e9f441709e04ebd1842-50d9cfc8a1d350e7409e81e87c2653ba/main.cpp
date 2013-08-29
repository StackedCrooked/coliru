#include <iostream>

namespace math
{
    namespace fraction_impl
    {
        struct Fraction
        {
            int a,b;
        };
        
        std::string ToString(const Fraction& f)
        {
            return std::to_string(f.a) + "/" + std::to_string(f.b);
        }
    }
    
    using fraction_impl::Fraction; // export to Fraction to the math namespace 
        
    namespace complex_impl
    {
        struct Complex
        {
            int a,b;
        };
        
        std::string ToString(const Complex& f)
        {
            return std::to_string(f.a) + " + " + std::to_string(f.b) + "i";
        }
    }
    
    using complex_impl::Complex; // export to math namespace
}


int main()
{
    math::Fraction f{1, 2};
    std::cout << "Fraction: " << ToString(f) << std::endl;
    
    math::Complex c{3, 4};
    std::cout << "Complex: " << ToString(c) << std::endl;
}