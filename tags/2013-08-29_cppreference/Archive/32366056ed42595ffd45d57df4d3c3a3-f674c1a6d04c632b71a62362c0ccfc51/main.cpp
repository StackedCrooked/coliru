#include <boost/algorithm/clamp.hpp>
#include <iostream>


using boost::algorithm::clamp;


int main()
{
    for (int i = 0; i != 5; ++i)
    {
        std::cout << i << " => " << clamp(i, 1, 3) << std::endl;
    }
}

