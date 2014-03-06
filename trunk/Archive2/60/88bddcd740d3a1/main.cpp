#include <iostream>
#include <iterator>
#include <vector>
#include <boost/range/combine.hpp>

int main()
{
    std::vector<int> v1{ 1, 2, 3 }, v2{ 6, 4, 2 };

    for (auto&& t : boost::combine(v1, v2))
            std::cout << t.get<0>() << " " << t.get<1>() << "\n";    
}
