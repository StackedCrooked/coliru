#include <iostream>
#include <vector>
#include <string>
#include <memory>

void inc( int&& x )
{
    std::cout << "on entry to inc() -            address: "
              << std::addressof(x) << " value: " << x << '\n' ;
    ++x ;
    std::cout << "just before exiti from inc() - address: "
              << std::addressof(x) << " value: " << x << '\n' ;
}

int main()
{
    int&& ri = 23 ;
    std::string str = "abc" ;
    std::string&& rs = str + "efgh" ;

    std::cout << "address: " << std::addressof(ri) << " value: " << ri << '\n'
              << "address: " << std::addressof(rs) << " value: " << rs << '\n' ;

    ri += 65 ;
    rs += "ijklmnop" ;

    std::cout << "address: " << std::addressof(ri) << " value: " << ri << '\n'
              << "address: " << std::addressof(rs) << " value: " << rs << '\n' ;

    inc(99) ;
}
