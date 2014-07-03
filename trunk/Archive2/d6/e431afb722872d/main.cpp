#include <boost/optional.hpp>
#include <limits>
#include <iostream>
#include <string>
#include <vector>


#define TEST(cmd) \
    std::cout << std::boolalpha << "(" << #cmd << ") => " << (cmd) << std::endl


int main()
{
    boost::optional<int> one = 1;
    boost::optional<int> two = 2;
    
    // optionals implement comparison
    TEST(one == 1);
    TEST(one > two);
    TEST(one > 0);
    TEST(one > 2);
        
        
    // empty optionals will always compare less than non-empty optionals
    boost::optional<int> nothing = boost::none;
    TEST(nothing < std::numeric_limits<int>::min());
}

