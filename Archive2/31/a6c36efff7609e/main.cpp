#include <boost/range/adaptor/transformed.hpp>
#include <iostream>
#include <vector>
struct double_int
{
    typedef int result_type;
    int operator()(int x) const { return 2 * x; }
};

boost::transformed_range<double_int, std::vector<int>> Fun(std::vector<int> &input)
{
    return input | boost::adaptors::transformed(double_int());
}

int main()
{
    
    std::vector<int> input {0, 1,2,3,4};
    for (auto elem : Fun(input))
        std::cout << elem;

    return 0;
}