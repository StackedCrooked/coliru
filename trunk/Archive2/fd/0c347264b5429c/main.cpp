#include <iostream>

struct _005 {}; std::ostream& operator<<(std::ostream& os, _005) { return os << 0 << 0 << 5; }

int main()
{
    _005 variable = _005();
    
    std::cout << variable;
}