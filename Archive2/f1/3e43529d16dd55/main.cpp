#include <type_traits>

struct C 
{
    C() = default;    
    int value = 0;
};

int main()
{
    static_assert(std::has_trivial_copy_constructor<C>::value, "");
    static_assert(std::has_trivial_default_constructor<C>::value, "");    
    static_assert(std::is_trivial<C>::value, ""); 
    static_assert(std::is_standard_layout<C>::value, "");
    static_assert(std::is_pod<C>::value, "");
}
