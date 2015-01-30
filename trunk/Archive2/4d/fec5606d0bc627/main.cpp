#include <iostream>
#include <iomanip>

int main()
{
    fixed(std::cout) ; // fine: function call, koenig lookup applies
    std::cout << fixed << 2.7 << '\n' ; // *** error: fixed is not not a function call 
    std::cout << setprecision(2) << 2.7 << '\n' ; // *** error: setprecision(int), int is not a member of std
}
