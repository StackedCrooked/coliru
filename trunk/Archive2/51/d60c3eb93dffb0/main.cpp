#include <iostream>
#include <boost/dynamic_bitset.hpp>

void ABC(boost::dynamic_bitset<> &a){
    // for (boost::dynamic_bitset<>::size_type i = 0; i < a.size(); ++i)
        // std::cout << a[i];
    // std::cout << "\n";
    std::cout << a << "\n";
}


int main()
{
    std::size_t size= 5;
    boost::dynamic_bitset<> x(size); // all 0's by default
    x[0] = 1;
    x[1] = 1;
    x[4] = 1;
    ABC( x );
    
    return 0;
}