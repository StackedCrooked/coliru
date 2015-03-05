#include <cassert>
#include <vector>
#include <iostream>
#include <set>
#include <iterator>

namespace onhands
{
    template <typename T>
    std::vector<T> unique(std::vector<T> const& first, std::vector<T> const& second)
    {
        std::set<T> test;
        test.insert(first.begin(), first.end());
        test.insert(second.begin(), second.end());
    // TODO: This function should join input vectors and return only unique elements.
    // Important: STL algorithms cannot be used!
        return std::vector<T>(test.begin(), test.end());
    }
} // namespace onhands

int main(int, char**)
{
    using std::vector;
    vector<double> d1 = {1.1, 2.1, 3.1, 1.0, 1.1, 0.56, 0.44, 4.445, 0.001, 9.996, 0.001};
    vector<double> d2 = {0.001, 0.002, 0.0003, 1.1, 0.44, 0.99, 0.996, 3.1, 3.12};

    vector<double> result = onhands::unique(d1, d2);
    
    std::copy(result.begin(), result.end(), std::ostream_iterator<double>(std::cout,", "));;
}

