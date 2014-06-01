#include <iostream>
#include <iomanip>

struct space
{
    constexpr space( int n ) : value(n) {}
    const int value ;
};

std::ostream& operator<< ( std::ostream& stm, space s )
{ return stm << std::left << std::setw(s.value) << ' ' ; }

int main()
{
    std::cout << "...............\n"
              << space(15) << "hello world\n"
              << space(15) << "the value is: " << std::fixed << 6.7 << '\n' ;
}
