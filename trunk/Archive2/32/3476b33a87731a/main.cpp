struct tribool_pod {
    unsigned char value; // can be private in C++11
    
    tribool_pod() = default;
    constexpr explicit tribool_pod(unsigned char p) noexcept : value(p) {}
    
    tribool_pod& operator=(unsigned char v) { value = v; return *this; }
    constexpr operator unsigned char() const { return value; }
    tribool_pod& operator=(bool v) { value = v ? 1 : 0; return *this; }
    constexpr operator bool() const { return value == 1; }
};

#include <type_traits>
int main()
{
    constexpr tribool_pod x{42};
    static_assert(std::is_pod<tribool_pod>{}, "not a POD");
}