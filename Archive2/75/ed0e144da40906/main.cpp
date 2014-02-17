#include <iostream>
#include <vector>

namespace Truc
{
typedef std::vector< unsigned > Quantities;
std::ostream & operator<<(std::ostream & out, const Quantities & quantities)
{
    return out << "Q";
}
}

void dummx()
{
    Truc::Quantities q;
    std::cerr << q;
}
