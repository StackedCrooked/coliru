#include <iostream>
#include <vector>

namespace Truc
{
    struct Quantity { unsigned i; };
    
typedef std::vector< Quantity > Quantities;
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

int main() { dummx(); }