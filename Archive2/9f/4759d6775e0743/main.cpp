#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>


#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <memory>

int main()
{
    int b = 10l;
    auto&& a = b;
    a = 75;
    b = 3;
    std::cout << a << std::endl;
}


