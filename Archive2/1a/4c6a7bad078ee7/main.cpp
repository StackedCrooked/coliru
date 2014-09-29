#include <iostream>
#include <type_traits>

struct SomeType
{
    SomeType(std::true_type)
    {
        std::cout << "Light side" << std::endl;
    }
    
    SomeType(std::false_type)
    {
        std::cout << "Dark side" << std::endl;
    }
    
    template <bool condition>
    static SomeType New()
    {
        return SomeType(std::integral_constant<bool, condition>{});
    }
};

int main()
{
    auto ls = SomeType::New<true>();
    auto ds = SomeType::New<false>();
    
    (void)ls;
    (void)ds;
}