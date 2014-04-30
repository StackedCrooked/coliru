#include <iostream>

namespace N
{

template< typename ...types >
struct X;

template< typename ...types >
std::ostream &
operator << (std::ostream & out, X< types... > const &)
{
    return out << "sad but true";
}

} // namespace N

int main()
{
    using namespace N;
    extern X< float >& x;
    std::cout << x << std::endl;
    return 0;
}