#include <iostream>

namespace math
{
    namespace fraction_impl_v1
    {
        struct Fraction
        {
            int a,b;
        };
        
        std::string ToString(const Fraction&)
        {
            return "v1";
        }
    }
    namespace fraction_impl_v2
    {
        struct Fraction
        {
            long a,b; // long is better
        };
        
        std::string ToString(const Fraction&)
        {
            return "v2";
        }
    }
    
    using namespace fraction_impl_v2;
}


//
// user code
//
namespace math
{
    using fraction_impl_v1::Fraction; // I want the old fraction!
}


int main()
{
    math::Fraction f{1, 2};
    std::cout << "Fraction: " << ToString(f) << std::endl;
    
}