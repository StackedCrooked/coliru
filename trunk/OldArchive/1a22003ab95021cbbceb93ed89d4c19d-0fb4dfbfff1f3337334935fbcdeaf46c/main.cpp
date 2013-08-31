#include <cstdint>

constexpr uint32_t prime_limit = 1e9 + 9;
constexpr uint32_t numberOfPrimes_upperBound = 50847536 + 1; // from wolframalpha, or estimate using e.g. the prime number theorem
constexpr unsigned recursion_limit = 900;

// as we cannot *modify* in constant expressions yet (=> C++1y), we'll have to
// split the work in chunks
// Note: you can "modify" (in C++11) a constexpr array by expanding it, but
//       this is (most probably) run into the similar problems

#include <iostream>
#include <cstdio>
#include <cstddef>

template < int... ii >
struct foo
{
    void print()
    {
        std::cout << "    " << sizeof...(ii) << std::endl;
    }
};

template < unsigned count, bool even, int... ii >
struct build_foo_helper
{
    using type = typename build_foo_helper<count-1, true, ii..., 1> :: type;
};
    template < unsigned count, int... ii >
    struct build_foo_helper<count, true, ii...>
    {
        using type = typename build_foo_helper<count/2, (count/2%2 == 0), ii..., ii...> :: type;
    };
    
    template < int... ii >
    struct build_foo_helper<0, true, ii...>
    {
        using type = foo<ii...>;
    };
    
template < unsigned count >
using build_foo = typename build_foo_helper<count-1, ((count-1)%2 == 0), 1> :: type;



int main()
{
    auto f = build_foo<50000>{};
    f.print();
}
