#include <iostream>
#include <string>
#include <vector>

struct Point {
    Point () = default;
    Point ( int ix, int iy ) : x(ix), y(iy) {}
    
    // the & means that it is allowed only on lvalue references, it is the c++11 replacement for all the crappy return by const value 
    Point& operator= ( Point const & ) & = default; 
    
    Point& Translate( Point const & t ) {
        x+= t.x;
        y+= t.y;
        return *this;
    }
    
    int x;
    int y;
};
inline Point operator+( Point const & a, Point const & b ) {
    return { a.x+b.x, a.y+b.y };
}

std::ostream& operator<<(std::ostream& os, Point const & p )
{
    os << "( " << p.x <<", " << p.y << " )";
    return os;
}

int main()
{
    Point a { 1, 2 }, b { 2, 3 };
    auto c = a + b;
    std::cout << c << std::endl;
    std::cout << c + Point { 2, 0 } << std::endl; // with inline operators and constructors, the 0 will be optimize out
    std::cout << c.Translate( { 2, 0 } ) << std::endl; // with inline operators and constructors, the 0 will be optimize out
    // a + b = c; // provoquerait une erreur
}
