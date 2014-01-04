#include <iostream>
#include <string>
#include <bitset>
#include <vector>
#include <iterator>

int main()
{
    
    std::bitset<16> foo (std::string("1001100110011001"));
    std::bitset<16> bar (std::string("0011001100110011"));
    
    std::vector<std::bitset<16> > one;
    one.push_back(foo);
    one.push_back(foo);
    one.push_back(foo);
    
    std::vector<std::bitset<16> > two;
    two.push_back(bar);
    two.push_back(bar);
    two.push_back(bar);
    

    std::bitset<16> foobar = (foo^=bar);
    
    std::cout << (foo^=bar) << '\n';
    std::cout << "Count: " << foobar.count() << "\n";
    
    
    for( std::vector<std::bitset<16> >::const_iterator i = one.begin(); i != one.end(); ++i)
        std::cout << *i << '\n';
    
}