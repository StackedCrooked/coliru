#include <iostream>

namespace N
{

template< typename ...types >
struct X
{
    static_assert((sizeof...(types) != 0), "zero length");
    X() = default;
    X(X const &) = default;
    X(X &&) = default;
    template< typename ...args >
    explicit // does not matter
    X(args &&...) { ; }
    int value = 10;
};

template< typename ...types >
std::ostream &
operator << (std::ostream & out, X< types... > const & x)
{
    return out << x.value;
}

} // namespace N

int main()
{
    using namespace N; // commenting this line makes sense
    N::X< float > /*const*/ x; // `const` does not matter
    std::cout << x << std::endl;
    return 0;
}

