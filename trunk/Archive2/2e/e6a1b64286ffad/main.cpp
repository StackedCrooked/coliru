#include <iostream>
#include <iomanip> 
#include <boost/cstdint.hpp>

int main()
{
    boost::int64_t k, m, g, t, p;
    k = 1024;
    m = k * k;
    g = m * k;
    t = g * k;
    p = t * k;
    double dbl = p;
    std::cout << std::setprecision(20);
    std::cout<< "pb.int64  = " << p << std::endl;
    std::cout<< "pb.double = " << dbl << std::endl;
    std::cout<< "pb.int64  8p -1 = " << p * 8-1 << std::endl;
    std::cout<< "pb.double 8p -1 = " << dbl * 8-1 << std::endl;
    std::cout<< "pb.double 8p    = " << dbl * 8 << std::endl;
    std::cout<< "pb.int64  9p -1 = " << p * 9-1 << std::endl;
    std::cout<< "pb.double 9p -1 = " << dbl * 9-1 << std::endl;
    std::cout<< "pb.double 9p    = " << dbl * 9 << std::endl;
    std::cout<< "size of double = " << sizeof(dbl) << std::endl;
    std::cout<< "size of long double = " << sizeof(long double) << std::endl;
    
    std::cout << std::setprecision(2);
    std::cout<< "value = " << 0.12345 << std::endl;
    
    return 0;
}
