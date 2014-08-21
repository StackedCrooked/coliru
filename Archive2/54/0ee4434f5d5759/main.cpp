#include <boost/range/adaptor/transformed.hpp>
#include <iostream>
#include <vector>
struct double_int
{
    typedef int result_type;
    int operator()(int x) const { return x; }
};

boost::transformed_range<double_int, std::vector<int>> Fun(std::vector<int> input)
{
    return input | boost::adaptors::transformed(double_int());
}

int main()
{
    

    for (auto elem : Fun({4,3,2,1}))
        std::cout << elem;

    return 0;
}