#include <iostream>
#include <sstream>
#include<iomanip>
struct mystream 
{
     mystream (std::ostream& os) : os(os) {}
     std::ostream&   os;
};

template <class T> 
mystream& operator<< (mystream& con, const T& x) 
{ 
     con.os << x << " "; // add extra delimeter
     return con; 
}


int main() 
{
    std::ostringstream foo;
    mystream c(foo) ;

    c << 1 << 1.2 << "bar" ;
    
    std::cout << foo.str() ;
 c<<std::setw(10)   <<std::setprecision(3)<<3.14159;
    std::cout << "Ends!";
}