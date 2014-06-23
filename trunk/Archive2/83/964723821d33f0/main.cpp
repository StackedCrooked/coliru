#include <boost/lambda/lambda.hpp>
#include <boost/lambda/if.hpp>
#include <iostream>
#include <vector>
#include <algorithm>
 
int main()
{
    std::vector<int> v;
    v.push_back(1);
    v.push_back(3);
    v.push_back(2);
 
    // boost::lambda::_1 substitutes the first argument
    // can't use std::endl instead of \n because of type issues (see boost c++ libraries page 27)
    std::for_each(v.begin(), v.end(), std::cout << boost::lambda::_1 << "\n");
 
    std::cout << std::endl;
 
    // also available: if_then_else, if_then_else_return
    std::for_each(v.begin(), v.end(),
        boost::lambda::if_then(boost::lambda::_1 > 1,
        std::cout << boost::lambda::_1 << "\n"));
 
    std::cout << std::endl;
 
    // Visual C++ 2010 version (no Boost.Lambda required - but not part of standard yet)
 
    std::for_each(v.begin(), v.end(),
        [] (int i) { if (i > 1) std::cout << i << std::endl; });
}